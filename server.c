#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>

#define PORT 9001
#define MAX_SIZE 255

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr;
    char filename[MAX_SIZE + 1];     // buffer for filename
    char fileContent[MAX_SIZE + 1];  // buffer for file content

    // Create server socket
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    // Server address
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    // Listen
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        exit(1);
    }

    printf("Server listening for connections on port %d\n", PORT);

    while (1) {
        printf("Waiting for client request...\n");

        clientSocket = accept(serverSocket, NULL, NULL);
        if (clientSocket < 0) {
            perror("Accept failed");
            continue;
        }

        // Clear filename buffer
        memset(filename, 0, sizeof(filename));

        // Receive filename from client
        int bytesReceived = recv(clientSocket, filename, sizeof(filename) - 1, 0);
        if (bytesReceived <= 0) {
            printf("Failed to receive filename.\n");
            close(clientSocket);
            continue;
        }

        filename[bytesReceived] = '\0';
        printf("Client requested file: %s\n", filename);

        // Open the requested file
        FILE *fp = fopen(filename, "r");
        if (!fp) {
            char *errorMsg = "Error: File not found.";
            send(clientSocket, errorMsg, strlen(errorMsg), 0);
        } else {
            // Read up to MAX_SIZE chars
            size_t bytesRead = fread(fileContent, 1, MAX_SIZE, fp);
            fileContent[bytesRead] = '\0';
            send(clientSocket, fileContent, strlen(fileContent), 0);
            fclose(fp);
        }

        printf("Responded to client request!\n");
        close(clientSocket);
    }

    close(serverSocket);
    return 0;
}
