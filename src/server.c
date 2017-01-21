// NAME          : server.c
// DESCRIPTION   : Stats server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#include "server.h"


// Signal handling

void signalHandler(int signo) {
    if (signo == SIGKILL) {
        syslog(LOG_INFO, "Received SIGKILL");
        waiting = 0;
    } else {
        syslog(LOG_ERR, "Received unknown signal");
        exit(EXIT_FAILURE);
    }
}


// General

int initServer(int port) {

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        syslog(LOG_ERR, "Failed to create socket");
        exit(EXIT_FAILURE);
    }

    struct sockaddr_in server;

    // Add server socket info
    memset(&server, 0, sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);

    // Bind name to socket
    if (bind(sockfd, (struct sockaddr*)&server, sizeof(server)) < 0) {
        syslog(LOG_ERR, "Failed to bind to socket");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(sockfd, MAX_CONNECTIONS) < 0) {
        syslog(LOG_ERR, "Failed to listen on socket");
        exit(EXIT_FAILURE);
    }

    // Start to waiting new connections
    waiting = 1;
    syslog(LOG_INFO, "Started server in port %d\n", port);

    return sockfd;
}


void closeServer(int sockfd) {

    if (close(sockfd) < 0) {
        syslog(LOG_ERR, "Failed to close server");
        exit(EXIT_FAILURE);
    }

    syslog(LOG_INFO, "Server closed");
}


void sendMessage(int fd, char *message) {

    if (write(fd, message, strlen(message)) < 0) {
        syslog(LOG_ERR, "Failed to send message to client");
        exit(EXIT_FAILURE);
    }
}


void waitForRequests(int sockfd) {

    // Initialize a new client connection
    int newsockfd = initConnection(sockfd);
    sendMessage(newsockfd, (char*)"Welcome!");

    // Handling multiple connections
    pthread_t thread;
    if (pthread_create(&thread, NULL, runConnection, (void*)&newsockfd) < 0) {
        syslog(LOG_ERR, "Failed to create threaded connection");
        exit(EXIT_FAILURE);
    }
}


int runServer(int port) {

    // Register signal SIGTERM and signal handler
    signal(SIGTERM, signalHandler);

    // Get TCP socket
    int sockfd = initServer(port);

    // Client petitions loop
    while(waiting) {
        waitForRequests(sockfd);
    }

    // Close and free
    closeServer(sockfd);

    return 0;
}
