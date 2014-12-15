/*
 *  prfx.c
 *  
 *  By:          Kyle Frost
 *  Created:     10/15/2014
 *
 *  Description: Command line too that finds all
 *               'transform' and 'transition' modifiers 
 *               in CSS file and add browser specific 
 *               prefixes (i.e. -webkit-, -moz-, -ms-).
 *
 *  Usage:       prfx <filename>
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifdef DEBUG
#define INITIAL_ALLOC 2
#else
#define INITIAL_ALLOC 512
#endif

void usage(char *program) {
    printf("Usage: %s <filename>\n", program);
}

float version() {
    return 1.0;
}

char *read_line(FILE *fin) {
    char *buffer;
    char *tmp;
    int read_chars = 0;
    int bufsize = INITIAL_ALLOC;
    char *line = malloc(bufsize);

    if (!line) {
        return NULL;
    }

    buffer = line;

    while (fgets(buffer, bufsize - read_chars, fin)) {
        read_chars = strlen(line);

        if (line[read_chars - 1] == '\n') {
            line[read_chars - 1] = '\0';
            return line;
        }

        else {
            bufsize = 2 * bufsize;
            tmp = realloc(line, bufsize);

            if (tmp) {
                line = tmp;
                buffer = line + read_chars;
            }
            else {
                free(line);
                return NULL;
            }
        }
    }

    return NULL;
}


int main(int argc, char *argv[]) {
    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }
    
    if (strcmp(argv[1], "-v") == 0) {
        float vers = version();
        printf("PRFX version %.01f\nCopyright (c) Kyle Frost\n", vers);
        exit(1);
    }

    FILE *css;
    char *line;    
    
    char *transform = "transform";
    char *transition = "transition";

    css = fopen(argv[1], "r");
    
    if (css) {
        while ((line = read_line(css))) {
            if (strstr(line, transform)) {
                printf("%s\n", line);
            }

            if (strstr(line, transition)) {
                printf("%s\n", line);
            }

            free(line);
        }
    }

    fclose(css);

    /*
    if (css == 0) {
        printf("Could not open file named \"%s\". Make sure it exists and was typed correctly.\n", argv[1]);
        exit(1);
    }
    */    

    return 0;
}
