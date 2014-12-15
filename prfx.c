/************************************************************
 *
 *  prfx.c:      www.github.com/kylefrost/prfx
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
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifdef DEBUG
#define INITIAL_ALLOC 2
#else
#define INITIAL_ALLOC 512
#endif

char *newFilePrfx = "prfxd_";

void usage(char *program) {
    printf("Usage: %s <filename>\n", program);
}

float version() {
    return 1.0;
}

char *concat(char *s1, char *s2) {
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
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

char *prfxTransform(char *line) {

    return NULL;
}

char *prfxTransition(char *line) {

    return NULL;
}

int main(int argc, char *argv[]) {
    
    // Make sure arguments are in right amount
    if (argc != 2) {
        usage(argv[0]);
        exit(1);
    }
    
    // If arg is -v show version information
    if (strcmp(argv[1], "-v") == 0) {
        float vers = version();
        printf("PRFX version %.01f\nCopyright (c) Kyle Frost\n", vers);
        exit(1);
    }

    // Search through file for lines containing transform and transition
    FILE *css;
    FILE *new;
    char *line;    
    
    char *transform = "transform";
    char *transition = "transition";

    // Open file
    css = fopen(argv[1], "r");

    // Create file name for new file containing prfx's
    char *newFileName = concat(newFilePrfx, argv[1]);
    
    // Loop through and print containing lines
    if (css) {

        new = fopen(newFileName, "w");

        while ((line = read_line(css))) {
            
            // If contains transform
            if (strstr(line, transform)) {
                printf("Found transform line:\n%s\n", line);
                char *transformPrfx = prfxTransform(line);
            }
            // If contains transition
            else if (strstr(line, transition)) {
                printf("Found transition line:\n%s\n", line);
                char *transitionPrfx = prfxTransition(line);
            }
            // Contains neither
            else {
                fprintf(new, "%s\n", line);
            }

            free(line);
        }
    }

    // Close files
    fclose(css);
    fclose(new);

    return 0;
}
