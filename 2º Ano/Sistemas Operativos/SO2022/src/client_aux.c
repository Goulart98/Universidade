/**
 * @file client_aux.c
 * @author Pedro Faria
 * @brief Funções auxiliares usadas pelo cliente
 * @version 0.1
 * @date 2022-04-07
 * 
 * 
 */

#include "globals.h"

/**
 * @brief Imprime 1 menu de ajuda no STDOUT
 * 
 */
void help(){
    char *help="  \n\t>>Ajuda<<\n  >>./sdstore status\n  >>./sdstore proc-file <priority> input-filename output-filename transformation-id-1 transformation-id-2...\n  >> <priority> -p 0 a 5\n\n";
        write(STDOUT_FILENO,help,strlen(help));

}



/**
 * Cria um fifo com o PID do programa
 * 
 * @param strPid nome do fifo (PID:status) ou (PID:proc-file <options)
 * 
 * @return 0 se bem sucedido, 1 caso exista erros
 */
int clientFifo(char* strPid){ 
    if (mkfifo(strPid,0644)<0){
            perror("client>fifo");
            return(EXIT_FAILURE);
        } else return EXIT_SUCCESS;
}

/**
 * @brief Função que gere um pedido de status
 * 
 * @param cpid o PID do programa que invoca a função
 * @return 0 se bem sucedido, 1 caso exista erros
 */
int status(int cpid){
    int fifo_fd;
    int pidFifo_fd;
    char pid_str[25];
    char cPid[30] ={"tmp/"};
    // criaçao de buffer usando calloc, para garantir que o bloco de memoria está "limpo"
    char * buffer =calloc(MSIZE, sizeof(char));
    int bytes_read=0;
    
    
    sprintf(buffer,"%d",cpid);
    strcpy(pid_str,buffer);
    strcat(buffer,":status");
    strcat(cPid,pid_str);
    //criação do FIFO com cPid
    clientFifo(cPid);

    if((fifo_fd = open(FIFO,O_WRONLY)) < 0){
        perror("client_aux> status> open(server_fifo)");
        _exit(0);
    }
    write(fifo_fd,buffer,MSIZE);
    close(fifo_fd);
    
    
    
    //abertura do fifo do cliente
    if ((pidFifo_fd = open(cPid,O_RDONLY)) < 0){  //ate aqui 100% é preciso agora fazer o server
        perror("client_aux >status> open(Client_fifo)");
        _exit(0);
        }
    //Leitura do FIFO e escrita no STDOUT
    while (1){  
        if ((bytes_read = read(pidFifo_fd,buffer,MSIZE)) > 0){
            if (strcmp("EXIT",buffer)==0){
                exit(EXIT_SUCCESS); //caso receba comando de saida
            }else{
            write(STDOUT_FILENO, buffer, bytes_read);
            }
        }
    }
    
    //protcolos de saida
    close(pidFifo_fd);
    free(buffer);
    

    return EXIT_SUCCESS;
}

/**
 * @brief Função que gere um pedido Proc
 * 
 * @param cpid PID do processo que invoca a função
 * @param argv argumentos a serem enviados ao servidor (proc-file <options>)
 * @return int 0 se bem sucedido, 1 caso exista erros
 */
int proc(int cpid, char** argv){ 

    int fifo_fd;
    int pidFifo_fd;
    char pid_str[25];
    char cPid[30] ={"tmp/"};
    // criaçao de buffer usando calloc, para garantir que o bloco de memoria está "limpo"
    char * buffer =calloc(MSIZE, sizeof(char));
    int bytes_read=0;
    

    sprintf(buffer,"%d",cpid);
    
    strcpy(pid_str,buffer);
    strcat(buffer,":");
    
    for (int i=2;argv[i];i++){
        strcat(buffer,argv[i]);
        if(argv[i+1]) strcat(buffer," "); //adicionar espaços excepto no ultimo
    }
    strcat(buffer,"\0"); //adicionar o final da string

    if((fifo_fd = open(FIFO,O_WRONLY)) < 0){
        perror("client > open(fifo)");
        _exit(0);
    }
    //criação do FIFO com pid
    strcat(cPid,pid_str);
    clientFifo(cPid);
    

    //escrita no fifo da mensagem para o server e fecha-se a ligação ao mesmo  
    write(fifo_fd,buffer,MSIZE);
    close(fifo_fd);
    
    //abertura do fifo especifico do cliente em modo leitura
    if ((pidFifo_fd = open(cPid,O_RDONLY)) < 0){  
        perror("client > open(fifo)");
        _exit(0);
        }

    //Leitura do FIFO e escrita no STDOUT
    while(1){
        if ((bytes_read = read(pidFifo_fd,buffer,MSIZE)) > 0){
            if (strcmp(buffer,"EXIT")==0){
                exit(EXIT_SUCCESS); //caso receba comando de saida
            }else {
                write(STDOUT_FILENO, buffer, bytes_read);
            }
        }
    }
    //protcolos de saida
    close(pidFifo_fd);
    free(buffer);


    return EXIT_SUCCESS;
}

