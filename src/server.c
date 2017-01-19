// NAME          : server.c
// DESCRIPTION   : Stats server
// AUTHOR        : Madh93 (Miguel Hernandez)
// VERSION       : 0.1.0
// LICENSE       : GNU General Public License v3

#include "server.h"


int initServer(int port) {

    // Create socket
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        printf("LOG_NOTICE: Failed to create socket\n");
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
        printf("LOG_ERROR: Failed to bind to socket\n");
        exit(EXIT_FAILURE);
    }

    // Listen for connections
    if (listen(sockfd, MAX_CONNECTIONS) < 0) {
        printf("LOG_ERROR: Failed to listen on socket\n");
        exit(EXIT_FAILURE);
    }

    // Start to waiting new connections
    waiting = 1;
    printf("LOG_INFO: Started server\n");

    return sockfd;
}

void closeServer(int sockfd) {

    if (close(sockfd) < 0) {
        printf("LOG_ERR: Failed to close server\n");
        exit(EXIT_FAILURE);
    }

    printf("LOG_INFO: Server closed\n");
}

void waitForRequests(int sockfd, struct sockaddr_in *client) {

    // Accept connection
    socklen_t clientlen = sizeof(client);
    int newsockfd = accept(sockfd, (struct sockaddr*)client, &clientlen);

    if (newsockfd < 0) {
        printf("LOG_ERROR: Failed to accept connection\n");
        exit(EXIT_FAILURE);
    }

    printf("LOG_NOTICE: New connection from %s\n", inet_ntoa(client->sin_addr));

    // Read received data
    char buffer[256];
    if (read(newsockfd, buffer, 255) < 0) {
        printf("LOG_ERROR: Failed read content\n");
        exit(EXIT_FAILURE);
    }

    printf("NEW MESSAGE: %s\n", buffer);


    close(newsockfd);
    waiting = 0;
    return;
}


int runServer(int port) {

    // Get TCP socket
    int sockfd = initServer(port);

    //
    struct sockaddr_in client;

    while(waiting) {
        waitForRequests(sockfd, &client);
    }

    // Close and free
    closeServer(sockfd);

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
