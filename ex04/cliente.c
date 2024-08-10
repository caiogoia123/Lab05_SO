#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>

#define SOCKET_PATH "/tmp/translation_socket"
#define BUFFER_SIZE 256

int main() {
    int client_socket;
    struct sockaddr_un server_addr;
    char buffer[BUFFER_SIZE];
    ssize_t bytes_sent, bytes_received;

    // Cria o socket UNIX
    client_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (client_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configura o endereço do servidor
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Conecta ao servidor
    if (connect(client_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    // Loop para enviar mensagens de tradução
    while (1) {
        printf("Digite o código e a palavra (ex: pt-en:cachorro) ou 'NO-NO' para sair: ");
        fgets(buffer, BUFFER_SIZE, stdin);
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character

        bytes_sent = send(client_socket, buffer, strlen(buffer), 0);
        if (bytes_sent < 0) {
            perror("send");
            exit(EXIT_FAILURE);
        }

        if (strcmp(buffer, "NO-NO") == 0) {
            break;
        }

        bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            perror("recv");
            exit(EXIT_FAILURE);
        }

        buffer[bytes_received] = '\0';
        printf("Resposta do servidor: %s\n", buffer);
    }

    close(client_socket);
    return 0;
}
