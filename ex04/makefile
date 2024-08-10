# Define o compilador e as flags
CC = gcc
CFLAGS = -Wall -Wextra -O2

# Define os arquivos fonte e os executáveis
SOURCES = servidor.c cliente.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLES = servidor cliente

# Regra para compilar todos os executáveis
all: $(EXECUTABLES)

# Regra para compilar o servidor
servidor: servidor.c
	$(CC) $(CFLAGS) -o servidor servidor.c

# Regra para compilar o cliente
cliente: cliente.c
	$(CC) $(CFLAGS) -o cliente cliente.c

# Regra para limpar os arquivos gerados
clean:
	rm -f $(EXECUTABLES) $(OBJECTS)
