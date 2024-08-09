#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>

#define FIFO_NAME "/tmp/meu_fifo"
#define BUFFER_SIZE 256

void process_string(const char *str) {
    int tamanho = strlen(str);
    int consoantes = 0, vogais = 0, espacos = 0;

    for (int i = 0; i < tamanho; i++) {
        char c = tolower(str[i]);
        if (c == ' ') {
            espacos++;
        } else if (c >= 'a' && c <= 'z') {
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vogais++;
            } else {
                consoantes++;
            }
        }
    }

    printf("String: '%s'\n", str);
    printf("Tamanho: %d\n", tamanho);
    printf("Consoantes: %d\n", consoantes);
    printf("Vogais: %d\n", vogais);
    printf("Espaços: %d\n\n", espacos);
}

int main() {
    int fifo_fd;
    char buffer[BUFFER_SIZE];

    // Criar o FIFO se ele não existir
    if (access(FIFO_NAME, F_OK) == -1) {
        if (mkfifo(FIFO_NAME, 0666) != 0) {
            perror("Erro ao criar FIFO");
            exit(EXIT_FAILURE);
        }
    }

    printf("Aguardando strings... (CTRL+C para sair)\n");

    while (1) {
        fifo_fd = open(FIFO_NAME, O_RDONLY);
        if (fifo_fd == -1) {
            perror("Erro ao abrir FIFO");
            exit(EXIT_FAILURE);
        }

        if (read(fifo_fd, buffer, BUFFER_SIZE) > 0) {
            process_string(buffer);
        }

        close(fifo_fd);
    }

    return 0;
}
