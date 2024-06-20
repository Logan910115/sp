#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8888
#define BUFFER_SIZE 1024

void* receive_messages(void* arg) {
    int server_fd = *((int*)arg);
    char buffer[BUFFER_SIZE];
    int bytes_received;

    while ((bytes_received = recv(server_fd, buffer, BUFFER_SIZE, 0)) > 0) {
        buffer[bytes_received] = '\0';
        printf("%s", buffer);
    }

    pthread_exit(NULL);
}

int main() {
    int server_fd;
    struct sockaddr_in server_addr;
    pthread_t tid;
    char message[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        perror("socket error");
        exit(1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    if (connect(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect error");
        close(server_fd);
        exit(1);
    }

    if (pthread_create(&tid, NULL, receive_messages, (void*)&server_fd) != 0) {
        perror("pthread_create error");
        close(server_fd);
        exit(1);
    }

    while (1) {
        fgets(message, BUFFER_SIZE, stdin);
        if (send(server_fd, message, strlen(message), 0) == -1) {
            perror("send error");
        }
    }

    close(server_fd);
    return 0;
}
