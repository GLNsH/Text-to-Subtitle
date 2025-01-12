#include <stdio.h>

void getTimeLine(char *timeLine, int msElapsedPrev, int msElapsed);

int main(void) {
    char time[30] = {0};
    int prev = 1152000;
    int cur = 1368000;
    getTimeLine(time, prev, cur);
    printf("%s",time);
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
    
    snprintf(timeLine, 30, "%d:%d:%d,%03d --> %d:%d:%d,%03d",hrPrev, minPrev, secPrev, msElapsedPrev, hr, min, sec, msElapsed);
}   