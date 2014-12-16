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
    printf("\n");
    printf("Stop being dumb.\n");
    printf("Usage: %s <filename>\n", program);
    printf("\n");
}

float version() {
    return 1.0;
}

void showInfo() {
    printf("\n");
    printf("Really not that hard to use, but okay...\n");
    printf("\n");
    printf("Usage:\n");
    printf("    prfx <filename>.css\n");
    printf("\n");
    printf("Output:\n");
    printf("    prfxd_<filename>.css\n");
    printf("\n");
    printf("Notes:\n");
    printf("    prfx can only take one file\n");
    printf("    at a time. Passing more will simply\n");
    printf("    tell you you are dumb for trying.\n");
    printf("\n");
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

char *addPrefixes(char *modifier, char *attrs) {
    
    char *new;
    char *webkit = "    -webkit-";
    char *moz = "    -moz-";
    char *ms = "    -ms-";
    char *o = "    -o-";
    char *orig = "    ";

    orig = concat(orig, modifier);
    webkit = concat(webkit, modifier);
    moz = concat(moz, modifier);
    ms = concat(ms, modifier);
    o = concat(o, modifier);

    orig = concat(orig, attrs);
    webkit = concat(webkit, attrs);
    moz = concat(moz, attrs);
    ms = concat(ms, attrs);
    o = concat(o, attrs);

    orig = concat(orig, ";\n");
    webkit = concat(webkit, ";\n");
    moz = concat(moz, ";\n");
    ms = concat(ms, ";\n");
    o = concat(o, ";\n");

    new = concat(orig, webkit);
    new = concat(new, moz);
    new = concat(new, ms);
    new = concat(new, o);

    if (new) {
        return new;
    }

    return NULL;
}

char *prfx(char *line, char *modifier) {
    
    char *target = NULL;
    char *start, *end;
    char *newString;

    if ((start = strstr(line, modifier))) {
        start += strlen(modifier);

        if ((end = strstr(start, ";"))) {
            target = (char *)malloc(end-start+1);
            memcpy(target, start, end-start);
            concat(target, "\0");
        }
    }

    if (target) {
        newString = addPrefixes(modifier, target);
        return newString;
    }
    
    free(target);
    return NULL;
}

int main(int argc, char *argv[]) {
    
    // Show info if no args
    if (argc == 1) {
        showInfo();
        exit(1);
    }

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
                char *transformPrfx = prfx(line, transform);
                fprintf(new, "%s", transformPrfx);
            }
            // If contains transition
            else if (strstr(line, transition)) {
                printf("Found transition line:\n%s\n", line);
                char *transitionPrfx = prfx(line, transition);
                fprintf(new, "%s", transitionPrfx);
            }
            // Contains neither
            else {
                fprintf(new, "%s\n", line);
            }
            // Release line otherwise shit hits the fan
            free(line);
        }
    }

    // Close files
    fclose(css);
    fclose(new);

    return 0;
}
