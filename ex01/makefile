# Variáveis
CC = gcc
CFLAGS = -Wall -Wextra -Werror
TARGETS = escritor leitor

# Alvo padrão: compila todos os programas
all: $(TARGETS)

# Regras de compilação
escritor: escritor.c
	$(CC) $(CFLAGS) -o escritor escritor.c

leitor: leitor.c
	$(CC) $(CFLAGS) -o leitor leitor.c

# Alvo para rodar ambos os programas (leitor primeiro, depois escritor)
run: all
	@echo "Iniciando o leitor..."
	./leitor &
	@echo "Iniciando o escritor..."
	./escritor

# Limpar arquivos compilados
clean:
	rm -f $(TARGETS)

.PHONY: all clean run
