#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>

#define MAX_SIZE 10000

// Estrutura para a memória compartilhada
typedef struct {
    int *vector1;
    int *vector2;
    int *result;
    int *done;
    int num_elements;
    int num_processes;
} shared_data_t;

void child_process(int start, int end, shared_data_t *shared) {
    // Espera a sinalização do pai
    sleep(1);
    
    // Processa os dados
    for (int i = start; i < end; i++) {
        shared->result[i] = shared->vector1[i] + shared->vector2[i];
    }

    // Marca que o processo terminou
    shared->done[getpid() % shared->num_processes] = 1;
    exit(0);
}

int main() {
    int num_elements, num_processes;
    printf("Digite o número de elementos dos vetores: ");
    scanf("%d", &num_elements);
    printf("Digite o número de processos: ");
    scanf("%d", &num_processes);

    if (num_elements > MAX_SIZE) {
        fprintf(stderr, "Número de elementos excede o limite.\n");
        return EXIT_FAILURE;
    }

    int fd[2];
    pipe(fd);
    
    // Cria memória compartilhada
    shared_data_t *shared = mmap(NULL, sizeof(shared_data_t), PROT_READ | PROT_WRITE,
                                 MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shared->vector1 = mmap(NULL, num_elements * sizeof(int), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shared->vector2 = mmap(NULL, num_elements * sizeof(int), PROT_READ | PROT_WRITE,
                           MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shared->result = mmap(NULL, num_elements * sizeof(int), PROT_READ | PROT_WRITE,
                          MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    shared->done = mmap(NULL, num_processes * sizeof(int), PROT_READ | PROT_WRITE,
                        MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    shared->num_elements = num_elements;
    shared->num_processes = num_processes;

    // Inicializa vetores e sinalização
    for (int i = 0; i < num_elements; i++) {
        shared->vector1[i] = i + 1; // Preenchendo com valores exemplo
        shared->vector2[i] = (i + 1) * 2;
        shared->result[i] = 0;
    }
    memset(shared->done, 0, num_processes * sizeof(int));

    // Cria os processos filhos
    pid_t pid;
    for (int i = 0; i < num_processes; i++) {
        pid = fork();
        if (pid == 0) {
            // No filho
            int start = i * (num_elements / num_processes);
            int end = (i == num_processes - 1) ? num_elements : (i + 1) * (num_elements / num_processes);
            close(fd[0]); // Fecha a extremidade de leitura do pipe
            child_process(start, end, shared);
            exit(0);
        }
    }

    // No pai
    close(fd[1]); // Fecha a extremidade de escrita do pipe

    // Aguarda os filhos terminarem
    for (int i = 0; i < num_processes; i++) {
        wait(NULL);
    }

    // Exibe o resultado
    printf("Resultado da soma dos vetores:\n");
    for (int i = 0; i < num_elements; i++) {
        printf("%d ", shared->result[i]);
    }
    printf("\n");

    // Limpa a memória compartilhada
    munmap(shared->vector1, num_elements * sizeof(int));
    munmap(shared->vector2, num_elements * sizeof(int));
    munmap(shared->result, num_elements * sizeof(int));
    munmap(shared->done, num_processes * sizeof(int));
    munmap(shared, sizeof(shared_data_t));

    return 0;
}
