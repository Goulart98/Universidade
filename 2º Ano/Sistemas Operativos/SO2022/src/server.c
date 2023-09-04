/**
 * @file server.c
 * @author Pedro Faria - a72640
 * @brief sdstored
 * @version 0.1
 * @date 2022-03-23
 * 
 * 
 */


#include "globals.h"

int transformCounter = 0; ///< Variavel global para numero de transformações

QUEUE queue = NULL; //Variabel global da cabeça da Queue das tasks a realizar

int taskCounter = 0; // Variavel global para numero de tasks


/**
 * @brief Função que inicia o servidor
 * 
 * @param argc Numero de argumentos passados pelo utilizador
 * @param argv Argumentos passados pelo utilizador
 * @return int 
 */

int main(int argc, char const *argv[]){

    
    char config[MSIZE]; // Variavel onde é guardado o nome do ficheiro de config
    char tFolder[MSIZE]; // Variavel onde é guardado o nome do diretorio das transformações
    TRANSFORM *t_array = NULL; // Array com todas as transformações
    TASK *tsk_array = NULL; //Array com todas as Tasks
    
    
    if (configSetup(argc,argv,config,tFolder)){ // Configuração do servidor
        perror("main>configSetup");
        exit(EXIT_FAILURE);
    }
    
    if(!(transformCounter = guardaTransform(&t_array,config,tFolder))){ // inicialização dos filtros
        perror("main>guardaTransform>");
        exit(EXIT_FAILURE);
    }
    
    
    
    
    printf("---server boot--- %d\n",getpid());
    // criação do fifo
    if (access(FIFO,W_OK)!=0){ //verifica se já existe 1 fifo criado e se tem permissao de escrita
        if (mkfifo(FIFO,0644)){
            perror("server>mkfifo");
            _exit(EXIT_FAILURE);
        } else write(STDOUT_FILENO,"fifo criado\n",13);
    } else write(STDOUT_FILENO,"fifo found\n",12);
    
    int fifo_fd;
    

    // criaçao de buffer usando calloc, para garantir que o bloco de memoria está "limpo"
    char buffer[MSIZE];
    int bytes_read=0;
    //abertura do fifos

    if ((fifo_fd = open(FIFO,O_RDONLY)) <= 0){
        perror("server > open(fifo)");
        _exit(1);
        }
    

    while(1){
        
        if ((bytes_read = read(fifo_fd,buffer,MSIZE)) > 0){
            write(STDOUT_FILENO, buffer, bytes_read); write(1,"\n",1); // escreve na consola o comando recebido e escreve um newline apos isso
             if (saveTask(buffer,&tsk_array,taskCounter++)){ // cria 1 task
                 perror("server>saveTask");
                 exit(1);
             }else{
                 if (tsk_array[taskCounter-1].isProc == 1){ // se a flag is proc for falsa faz status
                    
                    if (fork()==0) doStatus(tsk_array,t_array,taskCounter-1,transformCounter);// cria 1 filho de forma a nao parar o servidor

                 }else addQueue(tsk_array[taskCounter-1]); // adiciona a task á queue
                    
                
             
                }
        }
        
        doProc(tsk_array,t_array); // inicia o procedimento fazer a task proc
        
    }      
    

    close(fifo_fd);

    return 0;
}
