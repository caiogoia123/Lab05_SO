#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>  // Incluir este cabeçalho para usar mkfifo

#define FIFO_NAME "/tmp/meu_fifo"
#define BUFFER_SIZE 256

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

    printf("Digite strings para enviar (CTRL+D para sair):\n");

    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        fifo_fd = open(FIFO_NAME, O_WRONLY);
        if (fifo_fd == -1) {
            perror("Erro ao abrir FIFO");
            exit(EXIT_FAILURE);
        }
        
        write(fifo_fd, buffer, strlen(buffer) + 1);
        close(fifo_fd);
    }

    return 0;
}
