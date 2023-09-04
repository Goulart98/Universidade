/**
 * @file globals.h
 * @author Pedro Faria
 * @brief Ficheiro com todas as variaveis globais, structs e esqueletos de funções
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#define MSIZE 1024 ///< Tamanho maximo (geralmente usado para limitar o buffer)

#define FIFO "tmp/fifo" ///< Defenição standard da localização do fifo 





/** 
 *
 * @struct transform
 * @brief Contem todas as informações para uma transformação 
 * @param nome nome da transformação
 * @param exec localização do executavel
 * @param max maximo numero de transformações concorrentes permitido
 * @param running numero atual de transformações em utilização
 * 
 */
typedef struct transform
{
    char *nome; 
    char *exec; 
    int running;
    int max;    
}TRANSFORM;

/** 
 *
 * @struct task
 * @brief Contem todas as informações para uma tarefa 
 * 
 * @param tasknum numero da task
 * @param pid numero do processo do requerente
 * @param message mensagem original
 * @param origem origem do ficheiro
 * @param destino destino do ficheiro
 * @param trans transformações da mensagem (NULL caso não exista)
 * @param priority valor de 0 (default) a 5 que define a prioridade
 * @param isProc flag que define se é 1 status ou uma proc-file (0 se for proc/ 1 se for status)
 * @param status flag que define o estado de execução (0 -> ainda por iniciar, 1 -> em execução, 2 -> Terminado)
 */
typedef struct task{
    int tasknum;  
    char *pid; 
    char *message; 
    char *origem; 
    char *destino;
    char *trans; 
    int priority; 
    int isProc; 
    int status; 
}TASK;

/**
 * @struct node
 * @brief Contem as tasks e as suas prioridades.
 * 
 * De forma a ordenar as tasks por ordem de prioridade, usamos uma Lista Ligada, ordenada e teremos sempre a task mais importante na cabeça
 * @param task numero da task
 * @param priority prioridade da task
 * @param prox proximo elemento da queue, NULL caso seja o ultimo elemento
 */
typedef struct node{
    int task;
    int priority;
    struct node *prox;
}*QUEUE;

//server_aux
int guardaTransform(TRANSFORM ** array, char *config,char *local);
int configSetup(int argc,char const *argv[],char *config,char *tFolder);
int saveTask(char *buffer,TASK ** tsk_array,int taskCounter);
int doStatus(TASK *tsk_array,TRANSFORM *trn_array, int taskCounter,int transformCounter);
int doProc(TASK *tsk_array,TRANSFORM * array);
int countWord(char *s);
int addQueue(TASK t);
int doTask(TASK t,TRANSFORM * trn_array);

//client_aux
void help();
int status(int cpid);
int proc(int cpid, char ** argv);
