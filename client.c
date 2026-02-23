#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9001

int main() {
    int serverSocketID = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocketID < 0) {
        perror("Socket creation failed");
        return -1;
    }

    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    if (connect(serverSocketID, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        return -1;
    }

    char filename[256];
    printf("Enter filename to request: ");
    scanf("%s", filename);

    send(serverSocketID, filename, strlen(filename), 0);

    char serverMsg[512];
    memset(serverMsg, 0, sizeof(serverMsg));
    recv(serverSocketID, serverMsg, sizeof(serverMsg), 0);
    printf("Server response:\n%s\n", serverMsg);

    close(serverSocketID);
    return 0;
}
