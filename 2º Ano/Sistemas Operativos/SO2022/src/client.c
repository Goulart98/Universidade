/**
 * @file client.c
 * @author Pedro Faria
 * @brief sdstore
 * @version 0.1
 * @date 2022-03-23
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "globals.h"

int main(int argc, char *argv[]){
    
    char * buffer =calloc(MSIZE, sizeof(char));
     
    int pid = getpid();
    
    switch (argc){

    case 1:// sem args -> menu ajuda
        help();
        break;
    case 2:
        //apenas status -> verificar status de tasks e transforms
        if (strcmp(argv[1],"status")==0){  
            if(status(pid)){
                perror("Error:client>status ");
                return 1;
            }
        }else help();
        break;
    
    default:
        // proc-file
        // a mensagem client -> server : se for status envia status, se nao for status nao envia nada
        if (strcmp(argv[1],"proc-file")==0){
            if(proc(pid,argv)){
                perror("Error:client>proc-file\n");
                return EXIT_FAILURE;
            }

        }else help();
        break;
        
    }
    sprintf(buffer,"tmp/%d",pid);
    remove(buffer);// eliminar o tmp/%pid
    free(buffer);
    return 0;
}
