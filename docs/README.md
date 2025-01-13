# SubText: TXT to SRT file

The purpose of this small program is to solve a simple problem, that is ***"how do I convert a transcript file to subtitles conveniently?".***

Nah, not really. I wanted to convert ***transcript text to timed subtitles**, so that I can feed the **subtitles to a text-to-speech** program which in turn creates a **voice over for free**.

## Features
- Manual configuration of subtitle timings through ```config.ini```
- Length of subtile per line can be changed

## Building
```ps
gcc src\main.c src\config.c -Wall -W -O -o main
```
I appologize, I only know gcc to build all of my codes as of wrtiting this readme.

## Configuration ```config.ini```

Each configuration has default values, if it is ommited in the ```config.ini``` file.

- ```[FILES]``` section specifies the directory of the read and write files
    - ```READ_FILE_DIR``` defaults to ```"read.txt"```
    - ```WRITE_FILE_DIR``` defaults to ```"write.srt"```
- ```[SUBTITLE_TIMINGS]``` section specifies the spacing and padding time per line of subtitle
- ```[TIMINGS]``` section specifies the timing per type it found.
- ```[BUFFER_SIZES]``` section specifies the spacing and padding time per line of subtitle
    - ```LINE_BUFFER_SIZE``` specifies the maximum lenght of one subtitle line, defaults to ```500```
    - ```WORD_BUFFER_SIZE``` specifies the maximum word that it can read from the read file, defaults to ```100```
    - ```PUNCT_BUFFER_SIZE``` specifies the maximum symbol that it can read from the read file, defaults to ```10```

