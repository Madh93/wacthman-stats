// NAME          : main.c
// DESCRIPTION   : Parse input argumens
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#include "server.h"

int main(int argc, char *argv[]) {

    // Parse arguments
    if (argc > 1) {
        if ((!strcmp(argv[1], "-p")) || (!strcmp(argv[1], "--port"))) {
            printf("%d\n", runServer(atoi(argv[2])));
        } else if ((!strcmp(argv[1], "-?")) || (!strcmp(argv[1], "--help"))) {
            showHelp();
        } else if ((!strcmp(argv[1], "-v")) || (!strcmp(argv[1], "--version"))) {
            showVersion();
        } else {
            printf("Unknown option '%s'\nTry: %s --help\n", argv[1], APP);
        }
    } else {
        printf("No arguments\n");
    }

    return 0;
}
