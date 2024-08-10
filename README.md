# Lab05_SO
IPC com pipe, fifo, sockets, shm

Autor: Caio Goia RA:2482070

Github do projeto: https://github.com/caiogoia123/Lab05_SO

# Ambiente de Teste

Sistema Operacional: Ubuntu 22.04.4 LTS 

Arquitetura: x86_64

Compilador GCC:(Ubuntu 11.4.0-1ubuntu1~22.04) 11.4.0


# Exercício 1

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

# Exercício 2

Este projeto demonstra a manipulação de sinais e a escrita de dados em um arquivo utilizando C no Linux. O programa principal (ex02.c) abre um arquivo para escrita e permite que o usuário insira dados que são registrados no arquivo. O programa também lida com sinais de interrupção e terminação para garantir uma finalização limpa.

# Como compilar e testar o codigo 

Para compilar os programas, use o comando:

    make

Em um terminal, execute o comando para iniciar o programa ex02:

    ./ex02

Digite as entradas que deseja armazenar no arquivo dados.txt. Para finalizar o programa, use CTRL+C para enviar um sinal de interrupção ou kill <PID> para enviar um sinal de terminação. O programa fechará o arquivo e exibirá uma mensagem de finalização limpa.

# Exercício 3

Este projeto demonstra a comunicação entre processos utilizando memória compartilhada. O programa principal (ex03.c) cria dois vetores de inteiros, utiliza múltiplos processos para somar os vetores e exibe o resultado. O uso de memória compartilhada permite que todos os processos acessem e modifiquem os dados de forma eficiente.

# Como compilar e testar o codigo 

Para compilar o programa, use o comando:

    make

Em um terminal, execute o programa ex03 com o comando:

    ./ex03

Digite o número de elementos dos vetores e o número de processos desejado. O programa exibirá os vetores e o resultado da soma no terminal.

# Exercício 4

Este exercício implementa um serviço de tradução simples utilizando sockets UNIX. O serviço permite que um cliente envie palavras para tradução de uma língua para outra. O servidor realiza a tradução e envia a resposta de volta ao cliente. Este exemplo usa sockets UNIX para comunicação entre o cliente e o servidor.

# Como compilar e testar o codigo 

Para compilar o programa, use o comando:

    make

Em um terminal, execute o servidor:

    ./servidor

O servidor ficará aguardando conexões dos clientes.

Inicie o Cliente em outro terminal:

    ./cliente

O cliente solicitará que você digite a palavra para traduzir.
No terminal do cliente, digite a palavra para traduzir no formato code:word. Exemplo:

    pt-en:cachorro


O cliente exibirá a tradução recebida do servidor. Se a tradução não for encontrada, o servidor retornará ERROR:UNKNOWN.

Para encerrar a conexão com o servidor, digite NO-NO no terminal do cliente e pressione Enter.

    NO-NO