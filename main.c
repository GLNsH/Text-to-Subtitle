
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TIME_SPACING 1
#define MS_OFFSET 200

#define MS_PER_LETTER 60
#define MS_PER_WORD 0
#define MS_PER_PERIOD 0
#define MS_PER_COMMA 0
#define MS_PER_QUOTE 0
#define MS_PER_QUESTION 0
#define MS_PER_ELLIPSIS 0
#define MS_PER_EXCAMATION 0
#define MS_PER_DEFAULT 0

#define MS_PER_OR 0
#define MS_PER_AND 0

#define lineBufferSize 500
#define wordBufferSize 100
#define symBufferSize 10

void checkFileStatus(FILE ** files, int size);
int getWord(char* buffer, int size, FILE* readFile, char* c);
int getSymbol(char* buffer, int size, FILE* readFile, char* c);
void initSubtitleFile(FILE* writeFile);
void newSubtitleLine(FILE* writeFile, char* c);
void getTimeLine(char *buffer, int ms0, int ms1);

static char timeLine[54] = "00:00:00,000 --> 00:00:00,000";
static int msElapsed = 0;
static int msElapsedPrev = 0;
static int numSubtitle = 0;
static int writeTimeLineCursor = 0;

int main()
{
    // FILE* config = fopen("config.ini","r");
    FILE* readFile = fopen("read.txt", "r");
    FILE* writeFile = fopen("subtitles.srt", "w");
    FILE* files[] = {readFile, writeFile};
    checkFileStatus(files, sizeof(files)/sizeof(files[0]));

    
    char lineBuffer[lineBufferSize];
    char wordBuffer[wordBufferSize];
    char symBuffer[symBufferSize];

    char c;
    int wordLen, symLen, curLen = 0;
    
    
    initSubtitleFile(writeFile);
    do {
        wordLen = getWord(wordBuffer, wordBufferSize, readFile, &c);
        symLen = getSymbol(symBuffer, symBufferSize, readFile, &c);

        if (curLen + wordLen + symLen > lineBufferSize) {
            fprintf(writeFile, lineBuffer);
            newSubtitleLine(writeFile, &c);
            lineBuffer[0] = '\0';
            curLen = 0;
        }
        strcat(lineBuffer, wordBuffer);
        strcat(lineBuffer, symBuffer);
        curLen += wordLen + symLen;

    } while (c != EOF);

    fprintf(writeFile, lineBuffer);
    newSubtitleLine(writeFile, &c);

    fcloseall();
    return 0;
}


int getWord(char* buffer, int size, FILE* readFile, char* c) {
    int i = 0;
    char letter;
    while ((letter = *c = fgetc(readFile)) != EOF && i < size) {
        if (!(isalpha(letter) || isdigit(letter))) {
            ungetc(*c, readFile);
            break;
        };
        buffer[i++] = letter;
    }
    buffer[i++] = '\0';

    //TIMING
    msElapsed += MS_PER_WORD + i*MS_PER_LETTER;

    return strlen(buffer);
}

int getSymbol(char* buffer, int size, FILE* readFile, char* c) {
    int i = 0;
    char letter, prev = 0;
    while ((letter = *c = fgetc(readFile)) != EOF && i < size) {
        if (letter == '\n') { 
            prev = letter;
            continue;
        }

        if (isalpha(letter) || isdigit(letter)) {
            if (prev == '\n' && !isdigit(letter)) {
                buffer[i++] = ' ';
            };
            ungetc(*c, readFile);
            break;
        };
        buffer[i++] = letter;
        prev = letter;
    }
    buffer[i++] = '\0';

    //TIMING
    if (buffer[0] == '.') {
        if (buffer[1] == '.') msElapsed += MS_PER_ELLIPSIS;
        else msElapsed += MS_PER_PERIOD;
    }
    else if (buffer[0] == ',') msElapsed += MS_PER_COMMA;
    else if (buffer[0] == '\"') msElapsed += MS_PER_QUOTE;
    else if (buffer[0] == '!') msElapsed += MS_PER_EXCAMATION;
    else if (buffer[0] == '?') msElapsed += MS_PER_QUESTION;
    else msElapsed += MS_PER_DEFAULT;

    return strlen(buffer);
}

void checkFileStatus(FILE ** files, int size) {
    for (int i = 0; i < size; i++) {
        if (files[i] == NULL) {
            fprintf(stderr, "404: Unable to open file!\n");
            fcloseall();
            exit(404);
        }
    }
} 

void getTimeLine(char *buffer, int ms0, int ms1) {
    msElapsed += MS_OFFSET;
    int hrPrev, minPrev, secPrev, hr, min, sec;
    hrPrev = ms0/3600000;
    ms0 -= hrPrev*3600000;
    minPrev = ms0/60000;
    ms0 -= minPrev*60000;
    secPrev = ms0/1000;
    ms0 -= secPrev*1000;

    hr = ms1/3600000;
    ms1 -= hr*3600000;
    min = ms1/60000;
    ms1 -= min*60000;
    sec = ms1/1000;
    ms1 -= sec*1000;
    
    snprintf(buffer, 54, "%02d:%02d:%02d,%03d --> %02d:%02d:%02d,%03d", hrPrev%100, minPrev%60, secPrev%60, ms0%1000, hr%100, min%60, sec%60, ms1%1000);
    msElapsedPrev = msElapsed + TIME_SPACING;
    
}

void newSubtitleLine(FILE* writeFile, char* c) {
    getTimeLine(timeLine, msElapsedPrev, msElapsed);
    fseek(writeFile, writeTimeLineCursor, SEEK_SET);
    fprintf(writeFile, "%d\n%s\n", ++numSubtitle, timeLine);

    fseek(writeFile, 0, SEEK_END);
    if (*c != EOF) {
        fprintf(writeFile, "\n\n");
        writeTimeLineCursor = ftell(writeFile);
        initSubtitleFile(writeFile);
    }
}

void initSubtitleFile(FILE* writeFile) {
    fprintf(writeFile, "%d\n%s\n", numSubtitle+1, timeLine);
}
