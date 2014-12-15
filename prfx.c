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

void usage(char *program) {
    printf("Usage: %s <filename>\n", program);
}

float version() {
    return 1.0;
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

    css = fopen(argv[1], "r+");

    if (css == 0) {
        printf("Could not open file named \"%s\". Make sure it exists and was typed correctly.\n", argv[1]);
        exit(1);
    }

    

    return 0;
}
