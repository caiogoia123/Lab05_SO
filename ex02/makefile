# Makefile para o programa ex02

# Nome do executável
TARGET = ex02

# Compilador e flags
CC = gcc
CFLAGS = -Wall -Wextra -Werror

# Arquivo fonte
SRC = ex02.c

# Arquivo objeto
OBJ = $(SRC:.c=.o)

# Regra padrão
all: $(TARGET)

# Regra para compilar o executável
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# Regra para compilar o arquivo objeto
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regra para limpar arquivos gerados
clean:
	rm -f $(TARGET) $(OBJ)

