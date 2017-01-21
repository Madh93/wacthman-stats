// NAME          : watchman-stats.c
// DESCRIPTION   : Demonize server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#include "watchman-stats.h"
#include "server.h"


int demonize(int port) {

    pid_t pid;

    // Fork of the parent process
    pid = fork();

    if (pid < 0) {
        exit(EXIT_FAILURE);
    } else if (pid > 0) {
        exit(EXIT_SUCCESS);
    }

    // Change the file mode mask for permissions
    umask(0);

    // Open logs
    openlog(APP, LOG_NOWAIT | LOG_PID, LOG_USER);
    syslog(LOG_INFO, "Starting...");

    // Create a new SID for the child process
    if (setsid() < 0) {
        syslog(LOG_ERR, "Failed to start a new sesion");
        exit(EXIT_FAILURE);
    }

    // Change current directory
    if ((chdir("/")) < 0) {
        syslog(LOG_ERR, "Failed to change of directory");
        exit(EXIT_FAILURE);
    }

    // Close out the standard file descriptors
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    syslog(LOG_NOTICE, "Started %s", APP);

    // Do something interesting
    runServer(port);

    // Close logs
    syslog(LOG_NOTICE, "Finished %s", APP);
    closelog();

    return 0;
}


void showHelp() {
    printf("%s: Stats server for Watchman\n", APP);
    printf("\nUsage: %s [options]\n", APP);
    printf("\nOptions:\n");
    printf("  -p, --port          Number port\n");
    printf("  -h, --help          Show this help\n");
    printf("  -v, --version       Show version\n");
}


void showVersion() {
    printf("%s %s\n", APP, VERSION);
}
