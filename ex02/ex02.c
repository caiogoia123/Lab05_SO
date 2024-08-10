#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>

#define FILENAME "dados.txt"
#define BUFFER_SIZE 256

// Global file pointer
FILE *file;

// Função que será chamada quando o sinal for recebido
void handle_signal(int signal) {
    if (file != NULL) {
        fprintf(file, "Recebido sinal %d. Finalizando...\n", signal);
        fclose(file);
        printf("Arquivo fechado e finalização limpa concluída.\n");
    }
    exit(0);
}

int main() {
    char buffer[BUFFER_SIZE];
    
    // Abrir o arquivo para escrita
    file = fopen(FILENAME, "a");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(EXIT_FAILURE);
    }

    // Configurar handlers de sinal
    signal(SIGINT, handle_signal);  // Handle CTRL+C
    signal(SIGTERM, handle_signal); // Handle termination signal

    // Exemplo de escrita no arquivo
    printf("Digite algo para armazenar no arquivo (CTRL+C para sair):\n");
    while (1) {
        printf("> ");
        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            fprintf(file, "%s", buffer);
            fflush(file);  // Garantir que os dados são gravados no arquivo imediatamente
        } else {
            perror("Erro ao ler a entrada");
            break;
        }
    }

    return 0;
}
