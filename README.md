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