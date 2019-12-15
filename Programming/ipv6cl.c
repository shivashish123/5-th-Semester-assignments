#include <sys/types.h>                                                                                                      // Required by getaddrinfo()
#include <sys/socket.h>                                                                                                     // Required by getaddrinfo()
#include <netdb.h>                                                                                                          // Required by getaddrinfo()
#include <string.h>                                                                                                         // Required by memset()
#include <stdio.h>                                                                                                          // Required by perror()
#include <stdlib.h>                                                                                                         // Required by exit()
#include <unistd.h>                                                                                                         // Required by close()

int main() {

    printf("Client started.\n");

    const char *hostName = "::1";                                                                                     // Set destination server IP address
    const char *portNumber = "23439";                                                                                        // Set destination port number
    int clientSocket;                                                                                                       // File descriptor for client socket
    struct addrinfo hints;                                                                                                  // Hints provided to getaddrinfo() for translation
    memset(&hints, 0, sizeof(struct addrinfo));                                                                             // Initialize memory for hints
    struct addrinfo *results;                                                                                               // Linked list of results generated by getaddrinfo()
    struct addrinfo *record;                                                                                                // Single record of the linked list pointed by results
    hints.ai_family = AF_UNSPEC;                                                                                              // Set IP family to IPv4
    hints.ai_socktype = SOCK_STREAM;                                                                                        // Set socket type to stream
    hints.ai_protocol = IPPROTO_TCP;                                                                                        // Set protocol type to TCP

    if ((getaddrinfo(hostName, portNumber, &hints, &results)) != 0) {                                                       // Translate address
        perror("Failed to translate client socket.");
        exit(EXIT_FAILURE);
    }

    printf("Client socket translated.\n");

    for (record = results; record != NULL; record = record->ai_next) {                                                      // Iterate through every record in results
        clientSocket = socket(record->ai_family, record->ai_socktype, record->ai_protocol);                                 // Attempt to create socket from information provided in current record
        if (clientSocket == -1) continue;                                                                                   // Skip current iteration in the loop if socket creation fails
        if (connect(clientSocket, record->ai_addr, record->ai_addrlen) != -1) break;                                        // Attempt to connect socket after its successful creation. If successful, break out of the loop
        close(clientSocket);                                                                                                // Close the socket if socket creation is successful but connection is unsuccessful
    }

    if (record == NULL) {                                                                                                   // record will iterate to NULL if the above loop encounters no success
        perror("Failed to create or connect client socket.");
        exit(EXIT_FAILURE);
    }

    freeaddrinfo(results);                                                                                                  // results is a linked list and hence dynamically allocated. It must be freed manually

    printf("Client socket created and connected.\n");

    char *message = "Like, subscribe, comment, send money.\n#SubliminalMessagingDefinitelyWorks";                           // Set data to send

    if (send(clientSocket, message, strlen(message), 0) == -1) {                                                            // Send data
        perror("Failed to perform cognitive recalibration.");                                                               // Error message for when send() fails
        exit(EXIT_FAILURE);
    } else {
        printf("Subliminal message has been planted.\n");
    }

    close(clientSocket);                                                                                                    // Don't forget to close the socket as client

    printf("Client socket closed.\n");

    return 0;
}