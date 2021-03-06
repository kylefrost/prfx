/************************************************************
 *
 *  prfx.c:      www.github.com/kylefrost/prfx
 *  
 *  By:          Kyle Frost
 *  Created:     10/15/2014
 *
 *  Description: Command line tool that finds all
 *               'transform' and 'transition' modifiers 
 *               in CSS file and add browser specific 
 *               prefixes (i.e. -webkit-, -moz-, -ms-).
 *
 *  Usage:       prfx <filename>.css
 *
 ***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#ifdef DEBUG
#define INITIAL_ALLOC 2
#else
#define INITIAL_ALLOC 512
#endif

char *newFilePrfx = "prfxd_";
int s;

char *concat(char *s1, char *s2) {
    char *result = malloc(strlen(s1)+strlen(s2)+1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void usage(char *program) {
    printf("\n");
    printf("Stop being dumb.\n");
    printf("Usage: %s <filename>\n", program);
    printf("\n");
}

float version() {
    return 1.5;
}

char *versionChar() {
    return "1.5";
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
    printf("Options:\n");
    printf("    -v, --version     Shows version\n");
    printf("    -h, --help        Shows this help\n");
    printf("    -u, --update      Checks if an update is available and installs if necassary\n");
    printf("\n");
    printf("Notes:\n");
    printf("    prfx can only take one file\n");
    printf("    at a time. Passing more will simply\n");
    printf("    tell you you are dumb for trying.\n");
    printf("\n");
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

char *getCurrentFolder() {
    
    static char cwdir[1024];

    if (getcwd(cwdir, sizeof(cwdir)) != NULL) {
        return cwdir;
    }

    return NULL;
}

bool checkForUpdate() {

    char cwd[1024];

    if (getcwd(cwd, sizeof(cwd)) != NULL) {

        FILE *versionFile;
        char *buff;

        system("mkdir ~/.prfx_tmp/");
        system("cd ~/.prfx_tmp/");
        system("curl -OLs https://raw.githubusercontent.com/kylefrost/prfx/master/version.txt");
        
        versionFile = fopen("version.txt", "r");

        char *currentVersion = read_line(versionFile);
        
        char *command = concat("cd ", cwd);
        fclose(versionFile);
        system(command);
        system("rm -rf ~/.prfx_tmp/");

        if ((strcmp(currentVersion, versionChar()))) {
            return false;
        } else {
            return true;
        }
    }
    else {
        perror("Error 1: Could not get current directory");
    }

    return false;
}

void getLeadingWhitespace(char *line) {

    char keys[] = "abcdefghijklmnopqrstuvwxyz1234567890";
    int i;
    i = strcspn(line, keys);
    s = i;
}

char *addPrefixes(int p, char *modifier, char *attrs) {

    char *new;
    char *tabs = "";
    char *webkit = "-webkit-";
    char *moz = "-moz-";
    char *ms = "-ms-";
    char *o = "-o-";
    char *orig = "";

    for (int i = 0; i < p; i++) {
        tabs = concat(" ", tabs);
    }

    orig = concat(tabs, orig);
    webkit = concat(tabs, webkit);
    moz = concat(tabs, moz);
    ms = concat(tabs, ms);
    o = concat(tabs, o);

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
        getLeadingWhitespace(line);
        if (s) {
            newString = addPrefixes(s, modifier, target);
        } else {
            s = 4;
            newString = addPrefixes(s, modifier, target);
        }
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
    if (strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0) {
        float vers = version();
        printf("PRFX version %.01f\nCopyright (c) Kyle Frost\n", vers);
        exit(1);
    }

    // If arg is -h show help
    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0) {
        showInfo();
        exit(1);
    }

    if (strcmp(argv[1], "-u") == 0 || strcmp(argv[1], "--update") == 0) {
        bool needsUpdate = checkForUpdate();
        if (!needsUpdate) {
            // Update
            printf("\nThere is an update available!\n\n");
            //system("cd /usr/local/bin/");
            printf("Updating prfx...\n\n");
            system("ruby -e \"$(curl -fsSL https://raw.github.com/kylefrost/prfx/master/install)\"");
        } else {
            // No updates
            printf("\nThere are no updates available.\n\n");
        }
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
