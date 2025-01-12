
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TIME_SPACING 1

#define MS_PER_LETTER 45
#define MS_PER_PERIOD 650
#define MS_PER_COMMA 250
#define MS_PER_QUOTE 250
#define MS_PER_QUESTION 500
#define MS_PER_ELLIPSIS 600

#define MS_PER_OR 600
#define MS_PER_AND 600


void writeTimeline(FILE* writeFile, char *timeLine, int* msElapsedPrev, int* msElapsed, int* writeTimePos, char c);
void getTimeLine(char *timeLine, int msElapsedPrev, int msElapsed);
void checkFileStatus(FILE * read, FILE* write);
int processPeriods(FILE* readFile, FILE* writeFile, char* c);
int processTime(char c);
int processJunctionWords(FILE* readFile, FILE* writeFile, char* c);
int isEllipsis(char *letter);



int main()
{
    FILE* readFile = fopen("read.txt", "r");
    FILE* writeFile = fopen("subtitles.srt", "w");
    checkFileStatus(readFile, writeFile);
    char timeLine[] = "00:00:00,000 --> 00:00:00,000";

    char  c, prev = 0;
    int msElapsedPrev = 0;
    int msElapsed = 0;

    int writeTimePos = 0;
    
    fprintf(writeFile, "1\n%s\n", timeLine);
    while ((c = fgetc(readFile)) != EOF) {
        if (c == '\n') continue;
        else if (c == '.') {
            msElapsed += processPeriods(readFile, writeFile, &c);
            writeTimeline(writeFile, timeLine, &msElapsedPrev, &msElapsed, &writeTimePos, c);
            prev = c;
            continue;
        } else if (prev == ' ' && (c == 'o' || c == 'a')) {
            processJunctionWords(readFile, writeFile, &c);
        } else {
            msElapsed += processTime(c);
        }
        
        fprintf(writeFile, "%c", c);
        prev = c;
    }

    fcloseall();
    return 0;
}

//function definitions

int processJunctionWords(FILE* readFile, FILE* writeFile, char* c) {
    fprintf(writeFile, "%c", *c);

    int ms = 0, i;
    char buffer[4] = {0};
    buffer[0] = tolower(*c);
    for (i = 2; i < 5; i++) {
        if ((*c = fgetc(readFile)) == EOF) return i*MS_PER_LETTER;
        fprintf(writeFile, "%c", *c);
        buffer[i-1] = tolower(*c);
        if (*c == ' ') break;
    }

    if (buffer[0] == 'o' && buffer[1] == 'r' && buffer[2] == ' ') {
        return MS_PER_OR;
    } else if (buffer[0] == 'a' && buffer[1] == 'n' && buffer[2] == 'd' && buffer[3] == ' ') {
        return MS_PER_AND;
    }
    return i*MS_PER_LETTER;
}

int processTime(char c) {
    static float comma = 1;
    static int quote = 0;
    if (ispunct(c)) {
        if (c == ',') comma++;
        else comma = 1;
        if (c == '"') quote++;
    }
    if (c == ',') return (int) comma * MS_PER_COMMA;
    if (c == '\"' && (quote%2 == 0)) return MS_PER_QUOTE;
    if (c == '?') return MS_PER_QUESTION;
    return MS_PER_LETTER;

}

int processPeriods(FILE* readFile, FILE* writeFile, char* c) {
    fprintf(writeFile, "%c", *c);
    for (int i = 0; i < 2; i++) {
        if ((*c = fgetc(readFile)) == EOF) return MS_PER_PERIOD;
        fprintf(writeFile, "%c", *c);
        if (*c != '.') {
            return MS_PER_PERIOD;
        };
    }
    return MS_PER_ELLIPSIS;
}

void writeTimeline(FILE* writeFile, char *timeLine, int* msElapsedPrev, int* msElapsed, int* writeTimePos, char c) {
    static int numSubtitles = 0;
    numSubtitles++;
    fseek(writeFile, *writeTimePos, SEEK_SET);
    getTimeLine(timeLine, *msElapsedPrev, *msElapsed);        
    fprintf(writeFile, "%d\n%s", numSubtitles, timeLine);
    
    *msElapsedPrev = *msElapsed + TIME_SPACING;
    

    fseek(writeFile, 0, SEEK_END);
    fprintf(writeFile, "\n\n");
    *writeTimePos = ftell(writeFile);

    if (c != EOF) {
        fprintf(writeFile, "%d\n%s\n", numSubtitles+1, timeLine);
    }
    
}

void getTimeLine(char *timeLine, int msElapsedPrev, int msElapsed) {
    int hrPrev, minPrev, secPrev, hr, min, sec;
    hrPrev = msElapsedPrev/3600000;
    msElapsedPrev -= hrPrev*3600000;
    minPrev = msElapsedPrev/60000;
    msElapsedPrev -= minPrev*60000;
    secPrev = msElapsedPrev/1000;
    msElapsedPrev -= secPrev*1000;

    hr = msElapsed/3600000;
    msElapsed -= hr*3600000;
    min = msElapsed/60000;
    msElapsed -= min*60000;
    sec = msElapsed/1000;
    msElapsed -= sec*1000;
    
    snprintf(timeLine, 30, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d",hrPrev, minPrev, secPrev, msElapsedPrev, hr, min, sec, msElapsed);
}

void checkFileStatus(FILE * read, FILE* write) {
    if (read == NULL || write == NULL) {
        fprintf(stderr, "Unable to open file!\n");
        fcloseall();
    }
}

int isEllipsis(char *letter) {
    if (letter[0] == '.' &&  letter[1] == '.' && letter[2] == '.') return 3;
    return 0;
}
