# Nome dos binários
BINARIES = servidor cliente

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Alvo padrão
all: $(BINARIES)

# Regra para compilar o servidor
servidor: servidor.c
	$(CC) $(CFLAGS) -o $@ $^

# Regra para compilar o cliente
cliente: cliente.c
	$(CC) $(CFLAGS) -o $@ $^

# Regra para limpar arquivos gerados
clean:
	rm -f $(BINARIES) /tmp/translation_socket

# Regra para executar o servidor e o cliente
run: all
	@echo "Iniciando o servidor..."
	./servidor &
	@echo "Iniciando o cliente..."
	./cliente

.PHONY: all clean run
