# Lab05_SO
IPC com pipe, fifo, sockets, shm

# Exercicio 1

Este projeto demonstra a comunicação entre dois programas utilizando FIFOs (named pipes) no Linux. O projeto inclui dois programas: um escritor que envia strings para o FIFO e um leitor que recebe e processa essas strings.

Estrutura do Projeto

    escritor.c: Programa que escreve strings para o FIFO.
    leitor.c: Programa que lê strings do FIFO e exibe informações sobre elas.
    Makefile: Script para compilar os programas e executar o teste.

# Como compilar e testar o codigo 

Para compilar os programas, use o comando:

    make

Em um terminal, para iniciar o leitor.c, execute o comando no terminal:

    ./leitor

Agora para o escritor, abra outro terminal e execute o comando: 

    ./escritor 


No terminal do escritor, digite as strings que deseja enviar e pressione Enter após cada string.

# Exercicio 02

Este projeto demonstra a manipulação de sinais e a escrita de dados em um arquivo utilizando C no Linux. O programa principal (ex02.c) abre um arquivo para escrita e permite que o usuário insira dados que são registrados no arquivo. O programa também lida com sinais de interrupção e terminação para garantir uma finalização limpa.

# Como compilar e testar o codigo 

Para compilar os programas, use o comando:

    make

Em um terminal, execute o comando para iniciar o programa ex02:

    ./ex02

Digite as entradas que deseja armazenar no arquivo dados.txt. Para finalizar o programa, use CTRL+C para enviar um sinal de interrupção ou kill <PID> para enviar um sinal de terminação. O programa fechará o arquivo e exibirá uma mensagem de finalização limpa.