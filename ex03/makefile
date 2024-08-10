# Makefile para o programa ex03

# Nome do arquivo fonte
SRC = ex03.c

# Nome do executável
TARGET = soma_vetores

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Alvo padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET)

.PHONY: all clean
