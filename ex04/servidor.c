#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/wait.h>

#define SOCKET_PATH "/tmp/translation_socket"
#define BUFFER_SIZE 256

// Função de tradução fictícia
const char* translate(const char *code, const char *word) {
    // Dicionário simples de traduções
    if (strcmp(code, "pt-en") == 0) {
        if (strcmp(word, "cachorro") == 0) return "dog";
        if (strcmp(word, "gato") == 0) return "cat";
    }
    // Caso não encontre tradução
    return "ERROR:UNKNOWN";
}

void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    ssize_t bytes_received;

    // Loop para continuar recebendo traduções até receber "NO-NO"
    while ((bytes_received = recv(client_socket, buffer, BUFFER_SIZE - 1, 0)) > 0) {
        buffer[bytes_received] = '\0';
        if (strcmp(buffer, "NO-NO") == 0) {
            break;
        }

        // Processa a tradução
        char code[10], word[BUFFER_SIZE];
        sscanf(buffer, "%[^:]:%s", code, word);

        const char *translation = translate(code, word);

        // Envia a tradução de volta ao cliente
        send(client_socket, translation, strlen(translation), 0);
    }

    close(client_socket);
    exit(0);
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_un server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // Cria o socket UNIX
    server_socket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (server_socket < 0) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // Configura o endereço do socket
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sun_family = AF_UNIX;
    strncpy(server_addr.sun_path, SOCKET_PATH, sizeof(server_addr.sun_path) - 1);

    // Remove o socket se ele já existir
    unlink(SOCKET_PATH);

    // Associa o socket ao endereço
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // Escuta por conexões
    if (listen(server_socket, 5) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        // Aceita uma conexão
        client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len);
        if (client_socket < 0) {
            perror("accept");
            continue;
        }

        // Cria um processo filho para tratar o cliente
        pid_t pid = fork();
        if (pid == 0) {
            // Processo filho
            close(server_socket);
            handle_client(client_socket);
        } else if (pid > 0) {
            // Processo pai
            close(client_socket);
            wait(NULL); // Espera pelo filho terminar
        } else {
            perror("fork");
            close(client_socket);
        }
    }

    close(server_socket);
    unlink(SOCKET_PATH);
    return 0;
}
