
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char READ_FILE_DIR[500] = "read.txt";
char SUBTITLE_FILE_DIR[500] = "subtitles.srt";

int TIME_SPACING = 1;
int MS_OFFSET = 200;

int MS_PER_LETTER = 60;
int MS_PER_WORD = 0;
int MS_PER_PERIOD = 0;
int MS_PER_COMMA = 0;
int MS_PER_QUOTE = 0;
int MS_PER_QUESTION = 0;
int MS_PER_ELLIPSIS = 0;
int MS_PER_EXCAMATION = 0;
int MS_PER_DEFAULT = 0;

int MS_PER_OR = 0;
int MS_PER_AND = 0;

int LINE_BUFFER_SIZE = 500;
int WORD_BUFFER_SIZE = 100;
int PUNCT_BUFFER_SIZE = 10;


void loadConfig(FILE* config) {
    if (config == NULL) {
        fprintf(stderr, "401: Unable to open file!\n");
        fcloseall();
        return;
    }
    // int mode = 0;
    char buffer[50];
    char *key, *val;
    while (fgets(buffer, sizeof(buffer), config) != NULL) {
        buffer[strcspn(buffer,"\n")] = '\0';

        //token
        key = strtok(buffer," \"=");
        
        do {
            val = strtok(NULL," \"=");
            if (strcmp(key, "READ_FILE_DIR") == 0) {

                strcpy(READ_FILE_DIR, val);
            } else if (strcmp(key, "SUBTITLE_FILE_DIR") == 0) {
                strcpy(SUBTITLE_FILE_DIR, val);
            } else if (strcmp(key, "TIME_SPACING") == 0) {
                TIME_SPACING = (atoi(val)) ? atoi(val) : TIME_SPACING;
            } else if (strcmp(key, "MS_OFFSET") == 0) {
                MS_OFFSET = (atoi(val)) ? atoi(val) : MS_OFFSET;
            } else if (strcmp(key, "MS_PER_LETTER") == 0) {
                MS_PER_LETTER = (atoi(val)) ? atoi(val) : MS_PER_LETTER;
            } else if (strcmp(key, "MS_PER_WORD") == 0) {
                MS_PER_WORD = (atoi(val)) ? atoi(val) : MS_PER_WORD;
            } else if (strcmp(key, "MS_PER_PERIOD") == 0) {
                MS_PER_PERIOD = (atoi(val)) ? atoi(val) : MS_PER_PERIOD;
            } else if (strcmp(key, "MS_PER_COMMA") == 0) {
                MS_PER_COMMA = (atoi(val)) ? atoi(val) : MS_PER_COMMA;
            } else if (strcmp(key, "MS_PER_QUOTE") == 0) {
                MS_PER_QUOTE = (atoi(val)) ? atoi(val) : MS_PER_QUOTE;
            } else if (strcmp(key, "MS_PER_QUESTION") == 0) {
                MS_PER_QUESTION = (atoi(val)) ? atoi(val) : MS_PER_QUESTION;
            } else if (strcmp(key, "MS_PER_EXCAMATION") == 0) {
                MS_PER_EXCAMATION = (atoi(val)) ? atoi(val) : MS_PER_EXCAMATION;
            } else if (strcmp(key, "MS_PER_DEFAULT") == 0) {
                MS_PER_DEFAULT = (atoi(val)) ? atoi(val) : MS_PER_DEFAULT;
            } else if (strcmp(key, "MS_PER_OR") == 0) {
                MS_PER_OR = (atoi(val)) ? atoi(val) : MS_PER_OR;
            } else if (strcmp(key, "MS_PER_AND") == 0) {
                MS_PER_AND = (atoi(val)) ? atoi(val) : MS_PER_AND;
            } else if (strcmp(key, "LINE_BUFFER_SIZE") == 0) {
                LINE_BUFFER_SIZE = (atoi(val)) ? atoi(val) : LINE_BUFFER_SIZE;
            } else if (strcmp(key, "WORD_BUFFER_SIZE") == 0) {
                WORD_BUFFER_SIZE = (atoi(val)) ? atoi(val) : WORD_BUFFER_SIZE;
            } else if (strcmp(key, "PUNCT_BUFFER_SIZE") == 0) {
                PUNCT_BUFFER_SIZE = (atoi(val)) ? atoi(val) :PUNCT_BUFFER_SIZE;
            }
            
        } while (val != NULL);
            
    }
}