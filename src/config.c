
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char defaultSettings[] = 
    "[FILES]\n"
    "READ_FILE_DIR = \"read.txt\"\n"
    "WRITE_FILE_DIR = \"subtitles.srt\"\n"
    "\n"
    "[SUBTITLE_TIMINGS]\n"
    "TIME_SPACING = 1\n"
    "MS_OFFSET = 200\n"
    "\n"
    "[TIMINGS]\n"
    "MS_PER_LETTER = 60\n"
    "MS_PER_WORD = 0\n"
    "MS_PER_PERIOD = 0\n"
    "MS_PER_COMMA = 0\n"
    "MS_PER_QUOTE = 0\n"
    "MS_PER_QUESTION = 0\n"
    "MS_PER_ELLIPSIS = 0\n"
    "MS_PER_EXCAMATION = 0\n"
    "MS_PER_DEFAULT = 0\n"
    "MS_PER_OR = 0\n"
    "MS_PER_AND = 0\n"
    "\n"
    "[BUFFER_SIZES]\n"
    "LINE_BUFFER_SIZE = 500\n"
    "WORD_BUFFER_SIZE = 100\n"
    "PUNCT_BUFFER_SIZE = 10\n";

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

// #define DEBUG

void loadConfig() {
    FILE* config = fopen("config.ini","r");
    if (config == NULL) {
        config = fopen("config.ini","w");
        
        if (config == NULL) {
            fprintf(stderr, "No permission to create config.ini file: Loading default settings\n");
            fclose(config);
            return;
        }

        fprintf(config, defaultSettings);
        fprintf(stderr, "No config.ini found: Loading default settings\n");

        fclose(config);
        return;
    }

    #ifdef DEBUG
    printf("Loading Config...\n");
    #endif

    // int mode = 0;
    char buffer[50];
    char *key, *val;
    while (fgets(buffer, sizeof(buffer), config) != NULL) {
        buffer[strcspn(buffer,"\n")] = '\0';

        //token
        key = strtok(buffer," \"=");
        val = strtok(NULL," \"=");
        while (val != NULL) {
            #ifdef DEBUG
                printf("0: %s,%s\n",key,val);
            #endif
            if (strcmp(key, "READ_FILE_DIR") == 0) {
                strcpy(READ_FILE_DIR, val);
            } else if (strcmp(key, "WRITE_FILE_DIR") == 0) {
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
            val = strtok(NULL," \"=");
        }

    }
    #ifdef DEBUG
    printf("Loaded Config\n"); 
    #endif
    fclose(config);
}