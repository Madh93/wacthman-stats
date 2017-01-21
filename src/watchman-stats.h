// NAME          : watchman-stats.h
// DESCRIPTION   : Demonize server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3


#ifndef WATCHMAN_STATS_H
#define WATCHMAN_STATS_H

// To demonize
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>


// General
#define APP "watchman-stats"
#define VERSION "0.1.0"

// General
int demonize(int port);

// Other
void showHelp();
void showVersion();

#endif /* WATCHMAN_STATS_H */
