#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

#define SOCKET_PATH "/tmp/translation_socket"
#define BUFFER_SIZE 256

int main() {
    int sockfd;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];
    char response[BUFFER_SIZE];

    // Cria o socket
    sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configura o endereço do servidor
    memset(&server_addr, 0, sizeof(struct sockaddr_un));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Conecta ao servidor
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr_un)) < 0) {
        perror("connect");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Digite a palavra para traduzir (ou 'NO-NO' para sair):\n");
    while (1) {
        // Lê a entrada do usuário
        if (fgets(buffer, BUFFER_SIZE, stdin) == NULL) {
            perror("fgets");
            break;
        }

        // Remove o caractere de nova linha, se presente
        buffer[strcspn(buffer, "\n")] = '\0';

        // Envia a mensagem para o servidor
        if (send(sockfd, buffer, strlen(buffer) + 1, 0) < 0) {
            perror("send");
            break;
        }

        // Verifica se o usuário deseja sair
        if (strcmp(buffer, "NO-NO") == 0) {
            break;
        }

        // Recebe a resposta do servidor
        ssize_t bytes_received = recv(sockfd, response, BUFFER_SIZE - 1, 0);
        if (bytes_received > 0) {
            response[bytes_received] = '\0';
            printf("Resposta do servidor: %s\n", response);
        } else {
            perror("recv");
            break;
        }
    }

    // Fecha o socket
    close(sockfd);
    return 0;
}
