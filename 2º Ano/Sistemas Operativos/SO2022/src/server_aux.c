/**
 * @file server_aux.c
 * @author Pedro Faria
 * @brief  Contem funçoes adicionais a ser usadas com o server
 * @version 0.1
 * @date 2022-03-30
 * 
 * 
 */

#include "globals.h"


extern int transformCounter; // variavel global de server.c
extern QUEUE queue; //variabel global de server.c


/**
 * @brief Lê 1 linha de um fd e devolve o numero de bytes lidos
 * 
 * @param fd O descritor de onde é lido o ficheiro
 * @param line O buffer onde é guardado o que é lido.
 * @param size O tamanho do bu
 * 
 * @return Numero de bytes lidos
 */
ssize_t readln(int fd, char *line, size_t size){
    //não podemos usar o line porque o apontador está sempre a apontar para o inicio do array
    int next_pos = 0;
    int read_bytes = 0;

    while((read(fd, line + next_pos, 1) > 0) && next_pos < size){  //line + next_post avança com o apontador 
        read_bytes ++; //para ler o '\n'
        if (line[next_pos] == '\n'){  // line[next_post] dá o valor que está nessa posição que será um char e nao um apontador 
            break;                    
        }                        
        next_pos ++;                                             
    }
    return read_bytes;
}



/**
 * @brief Guarda as transformações
 * 
 * Recebe 1 array de Transformações, um ficheiro de configuração, e um path onde estao as transformações e guarda as informaçoes no array
 * 
 * @param array the array to be reallocated
 * @param config Nome do ficheiro de configuração
 * @param local Path para o diretorio onde estao os executaveis
 * 
 * @return Numero de transformações criadas.(size do array)
 */
int guardaTransform(TRANSFORM ** array, char *config,char *local){
    int tCounter=0; //<numero de transformações
    int file_fd = open(config,O_RDONLY); ///< descritor para a localização do ficheiro config

    if (file_fd<0){ ///< Verifica se o descritor é aberto
        perror("server_aux>guardaTransform>erro a abrir fd");
        exit(0);
    }

    int bRead =0; ///< numero de bytes lidos
    char buf[MSIZE]; ///< Buffer onde serão guardados os dados lidos

    while((bRead = readln(file_fd,buf,MSIZE)) > 0){
        buf[bRead] = '\0';
        TRANSFORM *tmp = realloc(*array,sizeof(TRANSFORM) * (tCounter + 1)); ///< array temporario para os filtros
        if (!tmp) return 0; // verifica se o array temporario foi criado

        (*array) = tmp; //

        TRANSFORM t;
        t.nome= strdup(strtok(buf," ")); // guarda o nome da transformação
        t.nome[strlen(t.nome)] = '\0'; ///< sem isto não é uma string pois não termina
        t.exec= strcat(strdup(local),t.nome);// guarda o caminho do executavel
        t.max=atoi(strtok(NULL,"\0")); ///< vai nos devolver o que falta na string de nome
        t.running=0;
        tmp[tCounter++] = t;///< guarda-se no temporario e incrementa-se o numero de filtros
    }
    close(file_fd);
    return tCounter; // saiu com sucesso

}

/**
 * 
 * 
 * @param argc The number of arguments passed to the program.
 * @param argv The argument vector.
 * @param config the configuration file name
 * @param tFolder the folder where the transformation files are located.
 * 
 * @return 1 caso de erro
 * @return 0 caso saia com sucesso
 */

/**
 * @brief Inicializa o servidor
 * 
 * @param argc numero de argumentos recebidos na main 
 * @param argv array com os argumentos recebidos
 * @param config Variavel onde é guardado o nome do ficheiro de config
 * @param tFolder Variavel onde é guardado o nome do diretorio das transformações
 * @return 0 Caso bem sucedido, 1 caso contrario
 */
int configSetup(int argc,char const *argv[],char *config,char *tFolder){
    char buf[MSIZE];
    if  (argc>4){ 
        perror("argumentos > 3");
        return 1;
    }
    if (argc<2) { // handling dos argumentos default
        write(STDOUT_FILENO,"arguments not found \t>>loading defaults\n",41);
        strcpy(config,"etc/sdstored.conf");
        strcpy(tFolder,"bin/sdstore-transformations/");
    }else { //caso receba argumentos
        write(STDOUT_FILENO,"argumentos recebidos do user\n",30);
        strcpy(config,argv[1]);
        sprintf(buf,"config-filename: '%s'\n",config);
        write(STDOUT_FILENO,buf,strlen(buf));
        strcpy(tFolder,argv[2]);
        if ((tFolder[strlen(tFolder)]) !="/") {
            char ch = '/';
            strncat(tFolder,&ch,1);
        }
        sprintf(buf,"transformations-folder: '%s'\n",tFolder);
        write(STDOUT_FILENO,buf,strlen(buf));
    }
    return 0;
}

/**
 * @brief Função auxiliar que verifica se 1 palavra k se encontra num array de tamanho n
 * 
 * @param array Onde ira procurar a palavra
 * @param k Palavra a procurar.
 * @param n Numero de elementos do array
 * @return int 0 Caso encontre, 1 Caso não encontre
 */
int isInArray(char** array, char* k,int n){
    if (n==0) return 1;
    for (int j=0;j<n;j++){
        if (strcmp(array[j],k)==0) return 0;
    }
    return 1;
}


/**
 * @brief Cria 1 array com transformações
 * 
 * @param mess Mensagem com as transformações
 * @param trans numero de transformações a serem criadas
 * @return char** array com 1 transformação por "linha"
 */
char** makeTransArray(char * mess,int trans){

    char ** array =malloc(trans * sizeof(char*));
    char *m=strdup(mess);
    char *k=strdup(strtok(m," "));
    for (int i=0;i<trans;i++){
            
        
            array[i] = malloc(strlen(k)*sizeof(char));
            strcpy(array[i],k);
            if (i+1!=trans) k= strdup(strtok(NULL," "));
            

        }
    
    return array;
        
}

/**
 * @brief Cria 1 array com todas as transformações UNICAS (pois estando 1 reservada)
 * pode ser usada multiplas vezes pela mesma instancia
 * 
 * @param mess Mensagem com as transformações
 * @param trans numero de transformações a serem criadas
 * @return char** array com 1 transformação por "linha" 
 */
char** makeTransArrayUnique(char * mess,int trans,int* count){
    int counter=0;
    char ** array =malloc(trans * sizeof(char*));
    char *m=strdup(mess);
    char *k=strdup(strtok(m," "));
    for (int i=0;i<trans;i++){
            
            if (isInArray(array,k,i)){// se a transformação não esta no array ele adiciona
                array[i] = malloc(strlen(k)*sizeof(char));
                strcpy(array[i],k);
                if (i+1!=trans) k= strdup(strtok(NULL," "));
                counter++;
            }

        }
        *count =counter;
    return array;
        
}

    


/**
 * @brief Guarda uma Task
 * 
 * @param buffer A string que contem as informações para a task
 * @param array O array com todas as tasks criadas ate ao momento
 * @param taskCounter numero total de tasks até ao momento
 */
int saveTask(char *buffer,TASK ** array,int taskCounter){
/// EXemplo : ./sdstore proc-file -p 0 samples/file-a outputs/file-a-output bcompress nop gcompress encrypt nop
    TASK *tmp = realloc(*array,sizeof(TASK) * (taskCounter + 1)); ///< array temporario para as tasks
        if (!tmp) return EXIT_FAILURE; // verifica se o array temporario foi criado
        
        char *k;
        
        (*array) = tmp; 

        TASK t;
        t.message=strdup(buffer);
        t.tasknum=taskCounter;
        t.pid=strdup(strtok(buffer,":"));
        k=strtok(NULL," ");
        if (strcmp(k,"status")==0){ // caso seja status nao precisa das infos seguintes
            t.destino = NULL;
            t.origem  = NULL;
            t.trans = NULL;
            t.priority=-1;
            t.isProc=1; //1 significa que não é proc-file
        }else{
            if (strcmp(k,"-p")==0){
                k=strdup(strtok(NULL," "));
                t.priority = atoi(k);
                t.origem = strdup(strtok(NULL," ")); //copia a origem
                t.destino = strdup(strtok(NULL," "));// copia o destino
                t.trans = strdup(strtok(NULL,"\0"));// copia as transformações
                t.isProc=0;
            }else{// caso nao exista -p default é 0
                t.priority = 0;
                t.origem = strdup(k); //copia a origem
                t.destino = strdup(strtok(NULL," "));// copia o destino
                t.trans = strdup(strtok(NULL,"\0"));// copia as transformações
                t.isProc=0;
            }
        }
        t.status=0;
        tmp[taskCounter] = t;
    

    return EXIT_SUCCESS;
}

/**
 * @brief Verifica se uma transformação pode ser executada
 * 
 * @param trans Nome da transformação.
 * @param array Array com todas as transformações
 * 
 * @return 0 caso esteja livre, 1 caso contrario
 */
int is_free(char * trans, TRANSFORM * array,int n){
    for(int i=0;i<transformCounter;i++){
        if (strcmp(trans,array[i].nome)==0){
            if (array[i].max>array[i].running){
                return EXIT_SUCCESS;
            }else return EXIT_FAILURE;   
        }
    }
    perror("server>aux>is_free:404 Trans not found");
    exit(1);
}


/**
 * @brief Verifica se as transformações podem ser executadas
 * 
 * @param n numero de transformações a serem pesquisadas
 * @param T_array O array com as strings, cada string é uma transformação.
 * @param array O array com as Transformações
 * 
 * @return 0 caso estejam livres, 1 caso contrario
 */
int isTransFree(int n,char *T_array[n],TRANSFORM * array){
    for(int i=0;i<n;i++){
        if (is_free(T_array[i],array,n) == 1) return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Verifica se 1 tarefa é possivel de ser feita
 * 
 * @param t a task a ser verificada
 * @param array o array com todas as transformações
 * @return int 0 caso a task seja possivel de fazer
 * @return int 1 caso a task não seja possivel de fazer
 */
int is_doable(TASK t,TRANSFORM *array){
    int trans = countWord(t.trans);
    int unique=0;
    char** T_array = makeTransArrayUnique(t.trans,trans,&unique);
    
    if (isTransFree(unique,T_array,array) == 1) {
        free(T_array);
        return EXIT_FAILURE;
    }
    else {
        free(T_array);
        return EXIT_SUCCESS;
        }
}

/**
 * @brief Inicializa a proc-file
 * 
 * Função que verifica se a task com maior prioridade da queue é possivel de ser feita, e a inicia caso seja
 * 
 * @param tsk_array Array com todas as tasks
 * @param trn_array Array com todas as transformações
 * @param curr Cabeça da queue no momento da invocação da função
 * @return int 0 caso a task seja possivel de fazer
 * @return int 1 caso a task não seja possivel de fazer 
 */
int doProc(TASK *tsk_array,TRANSFORM * trn_array){
    
     QUEUE curr = queue; // cabeça da queue
     while (curr){ // enquanto houver queue
         if (is_doable(tsk_array[curr->task],trn_array)==0) {//verifica se 1 task é possivel de ser feita
             tsk_array[curr->task].status=1;//caso seja, mete o status em execução e inicia a task
             doTask(tsk_array[curr->task],trn_array);  
         }
         curr = curr->prox;// anda para o proximo elemento da queue
     }
    
    return EXIT_SUCCESS;
}


/**
 * @brief Remove uma task da Queue
 * 
 * @param num Numero da task
 * 
 * @return A cabeça da queue
 */
int removeQueue(int num){
    int i,pos=0;
    QUEUE temp,curr = queue;
    if(queue==NULL){
        perror("server>aux>removeQueue: Vazio");
        return EXIT_SUCCESS;
    }else{
        while(curr!=NULL){
            if(curr->task == num) break;
            pos++;
            curr = curr->prox;
        }
        if (pos==0){
            curr = queue;
            queue= queue->prox;
            free(curr);
        }else{
            curr = queue;
            for(i=0;i<pos;i++){
                temp = curr;
                curr = curr->prox;
            }
            temp->prox= curr->prox;
            free(curr);
        }
    }
    return EXIT_SUCCESS;
}

/**
 * @brief Muda o estado das transformações para running.
 * 
 * Função que dada 1 task vai ao array das transformações e poe em execução as transformações dadas.
 * @param array Array com todas as transformações
 * @param t Task a ser verificada
 */
void busyTrn(TRANSFORM * array,TASK t){
    int trans = countWord(t.trans);
    int count=0;
    char** T_array = makeTransArrayUnique(t.trans,trans,&count); // embora 1 task possa ter 3 nop, apenas ira usar 1 de cada vez, logo apenas 1 é reservado
    for (int i=0;i<count;i++){
        for(int j=0;j<transformCounter;j++){
            if (strcmp(T_array[i],array[j].nome)==0) {
                array[j].running++;
                break;
                }
        }
    }
    
}

/**
 * @brief Muda o estado das transformações para free.
 * 
 * Função que dada 1 task vai ao array das transformações e liberta as transformações dadas.
 * @param array Array com todas as transformações
 * @param t Task a ser verificada
 */
void unBusyTrn(TRANSFORM * array, TASK t){
    int trans = countWord(t.trans);
    int count=0;
    char** T_array = makeTransArrayUnique(t.trans,trans,&count);
    for (int i=0;i<count;i++){
        for(int j=0;j<transformCounter;j++){
            if (strcmp(T_array[i],array[j].nome)==0) {
                if (array[j].running>0){
                    array[j].running--;
                    break;
                }else{
                    perror("server>aux>unBystTrn: running <=0");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
    t.status=2;

}


/**
 * @brief Comunicação com o cliente.
 * 
 * @param t Task em realização
 * @param m Mensagem a ser enviada
 * @param size Tamanho da mensagem
 * @return int 0 caso a task seja possivel de fazer 
 * @return int 1 caso a task não seja possivel de fazer 
 */
int talk_client(TASK t,char * m,int size){
    char path_client[30] ={"tmp/"};
    strcat(path_client,t.pid);
    int client_pid_fd;
    if ((client_pid_fd = open(path_client,O_WRONLY)) <= 0){
            perror("Server>Aux>talk_client>open client_fifo");
            return EXIT_FAILURE;
    }

    write(client_pid_fd,m,size);
    close(client_pid_fd);
    return EXIT_SUCCESS;


}

/**
 * @brief Getter do indice da Transformação
 * 
 * @param trans nome da transformação a ser procurada
 * @param array Array de todas as transformações
 * @return int 0 caso a task seja possivel de fazer 
 * @return int 1 caso a task não seja possivel de fazer 
 */
int getTransformIndex(char * trans, TRANSFORM * array){
    for (int i=0;i<transformCounter;i++){
        if (strcmp(trans,array[i].nome)==0) return i;
    }
    perror("server>aux>getTransformIndex: Transform not found\n");
    _exit(EXIT_FAILURE);
}


/**
 * @brief Cria 1 mensgem com os bytes dos ficherios de input e output
 * 
 * @param t Task para qual se verificara os valores
 * @param m String onde sera guardado os valores
 * @return int 0 caso a task seja possivel de fazer 
 * @return int 1 caso a task não seja possivel de fazer 
 */
int getStats(TASK t,char * m){
    struct stat buf;
    stat(t.origem,&buf);
    unsigned long size_origem = buf.st_size;
    stat(t.destino,&buf);
    unsigned long size_destino= buf.st_size;
    sprintf(m,"concluded (bytes-input : %lu, bytes-output: %lu)\n",size_origem,size_destino);
    return EXIT_SUCCESS;

}

/**
 * @brief Escreve para um log
 * 
 * @param fd_log Descritor de ficheiro do log   
 * @param exec executavel que foi invocado
 * @param i numero de fork
 * @param flag Tipo exec (start,final,middle,single)
 */
void writeLog(int fd_log,char * exec,int i,int flag){
    char log[MSIZE];
    int pid = getpid();
    switch (flag){
        case 0:
            sprintf(log,"fork #%d >>fd_origem -> fd[%d] : exec : %s\n",pid,i,exec); break;
        case 1:
            sprintf(log,"fork #%d final fd[%d] -> fd_destino : exec : %s\n",pid,i,exec); break;
        case 2:
            sprintf(log,"fork #%d intermédio fd[%d] -> fd[%d] : exec : %s\n",pid,i-1,i,exec); break;
        default:
            sprintf(log,"fork #%d unico origem -> destino : exec : %s\n",pid,exec);
    }
    write(fd_log,log,strlen(log));
}

/**
 * @brief Faz os forks do proc-file.
 * 
 * @param t Task em realização
 * @param trn_array Array com todas as transformações
 * @return int 0 caso a task seja possivel de fazer 
 * @return int 1 caso a task não seja possivel de fazer 
 */
int doForks(TASK t,TRANSFORM * trn_array){
    int num = countWord(t.trans);//numero de transformações a serem realizadas
    //aberuta de fd
    int fd_origem = open(t.origem,O_RDONLY);
    int fd_destino = open(t.destino,O_CREAT | O_WRONLY | O_TRUNC,0644 );
    int fd_log = open("tmp/log.txt",O_CREAT | O_WRONLY | O_APPEND,0644);
    
    //indicar que esta em processamento
    talk_client(t,"processing\n",12);
    
    //fd para pipes a serem criados
    int fd[num-1][2];// 0- In 1 - Out
    int status;
    //array de strings com todas as transformações a sereme executadas (com repetidos)
    char **T_array =makeTransArray(t.trans,num);
    
    //abrir pipes
    for (int i=0;i<num;i++){
        if(num>1){ // caso exista apenas 1 transformação não faz sentido abrir pipes
                if (pipe(fd[i])<0){ 
                    perror("server>aux>doForks:pipe\n");
                    return EXIT_FAILURE;
                }
        }
    }
    
    
    for (int i=0;i<num;i++){ //fork sequencial

        if(fork()==0){

            if (num==1){ //caso apenas exista 1 transformação
                dup2(fd_origem,0);
                dup2(fd_destino,1);
                close(fd_origem);
                close(fd_destino);
                
                int trans = getTransformIndex(T_array[i],trn_array);
                
                writeLog(fd_log,trn_array[trans].exec,i,3);

                execl(trn_array[trans].exec,trn_array[trans].nome,NULL); perror("server>doForks>num==1:execl");
                exit(i);
            }else {// caso existam varias transformações
                if(i==0){ //1o pipe fd_origem -> fd[0]
                dup2(fd_origem,0);
                close(fd_origem);

                close(fd[i][0]);
                dup2(fd[i][1],1);
                close(fd[i][1]);

                int trans = getTransformIndex(T_array[i],trn_array);
                
                writeLog(fd_log,trn_array[trans].exec,i,0);

                execl(trn_array[trans].exec,trn_array[trans].nome,NULL); perror("server>doForks>i==0:execl");
                //_exit(i);
                
                }else if (i==num-1){//ultimo pipe fd[num] -> fd_destino
                    dup2(fd[i-1][0],0);
                    close(fd[i-1][0]);

                    dup2(fd_destino,1);
                    close(fd_destino);

                    int trans = getTransformIndex(T_array[i],trn_array);
                    
                    writeLog(fd_log,trn_array[trans].exec,i,1);

                    execl(trn_array[trans].exec,trn_array[trans].nome,NULL);  perror("server>doForks>i==num:execl");               
                
    
                    }else{ // pipes intermédios fd[i-1] -> fd[i]
                        dup2(fd[i-1][0],0);
                        close(fd[i-1][0]);

                        close(fd[i][0]);

                        dup2(fd[i][1],1);
                        close(fd[i][1]);


                        int trans = getTransformIndex(T_array[i],trn_array);

                        writeLog(fd_log,trn_array[trans].exec,i,2);

                        execl(trn_array[trans].exec,trn_array[trans].nome,NULL); perror("server>doForks>intermedio:execl");
                        //_exit(i);

                    }
            }
        _exit(i);//fechar os forks
        }
        
        if (num>1){// fechar os pipes que possam estar abertos
            
            if (i==0){
			    close(fd[i][1]);
		    }
		    else if (i==num-1){
			    close(fd[i-1][0]);
		    }
		    else {
			    close(fd[i][1]);
			    close(fd[i-1][0]);
		    }
        }
    
    }

    while(wait(&status)>0); // espera que todos os filhos terminem
    char stats[MSIZE];
    getStats(t,stats);//para indicar os bytes
    talk_client(t,stats,strlen(stats)); // comunicar os bytes
    

    talk_client(t,"EXIT",5);// comando para terminar cliente
    unBusyTrn(trn_array,t);//para libertar as transformações
    return EXIT_SUCCESS;
}


/**
 * @brief Inicia execução da Proc-file
 * 
 * @param t Task a ser executada
 * @param trn_array Array com todas as transformações
 * @return int 0 caso a task seja possivel de fazer 
 * @return int 1 caso a task não seja possivel de fazer 
 */
int doTask(TASK t,TRANSFORM * trn_array){
    removeQueue(t.tasknum); // elimina a task da queue
    busyTrn(trn_array,t); // mete as transformaçoes em execução
    if (fork()==0)
        doForks(t,trn_array);  //Faz os forks da task

    return EXIT_SUCCESS;
}

/**
 * @brief Cria e envia todas as informações de tasks e transformações.
 * 
 * Cria uma mensagem com o estado atual de todas as transformaçoes e tasks, e envia-os ao cliente requerente através de um fifo
 *  
 * @param tsk_array Array com todas as tasks
 * @param trn_array Array com todas as Transformações
 * @param taskCounter numero de tasks atual
 * @param tCounter numero de transformações
 * 
 * @return int 0 caso a saia com sucesso
 * @return int 1 caso contrario 
 */
int doStatus(TASK *tsk_array,TRANSFORM *trn_array, int taskCounter,int tCounter){
    char buffer[MSIZE];
    char * res =calloc(MSIZE, sizeof(char));
    
        //abrir o fifo
        char src[30] ={"tmp/"};
        int client_pid_fd;
        strcat(src,tsk_array[taskCounter].pid);

        if ((client_pid_fd = open(src,O_WRONLY)) <= 0){
            perror("Server>Aux>doStatus>fork-open fifo");
            _exit(1);
        }    
    
        //criar a mensagem
        for (int i=0;i<=taskCounter;i++){
            if (i!=taskCounter && tsk_array[i].status ==1){ // nao queremos a propria task na resposta e queremos só tasks em execução
            char * mensagem=strdup(tsk_array[i].message); // vai buscar a mensagem guardada em array
            strtok(mensagem,":"); // retira o pid que esta guardado
            char *mes=strdup(strtok(NULL,"\0"));
            sprintf(buffer,"Task #%d : %s\n",tsk_array[i].tasknum,mes);
            strcat(res,buffer);
            }
        }
        for(int i=0;i<tCounter;i++){ 
            sprintf(buffer,"transf %s: %d/%d (running/max) \n",trn_array[i].nome,trn_array[i].running,trn_array[i].max);
            strcat(res,buffer);
        }
    
        //enviar mensagem
        write(client_pid_fd,res,MSIZE);
        write(client_pid_fd,"EXIT",5); //terminar o cliente
    
        //fechar o fifo e sair
        close(client_pid_fd);
        free(res);


    return EXIT_SUCCESS;

}

/**
 * @brief Conta o numero de palavras de uma string
 * 
 * @param s A string a ser contada
 * 
 * @return Numero de palavras da string.
 */
int countWord(char *m){
    int i, res=0;
    for (i=0;m[i];i++){
        if (m[i]==32) res++;
    }
    if (i>0) res++;
    return res;
}


/**
 * @brief Cria 1 nova struct para a queue
 * 
 * @param t Task a ser colocada na queue 
 * @return QUEUE Nova struct pronta a ser utilizada
 */
QUEUE newBox(TASK t){
    QUEUE r = malloc(sizeof(struct node));
    if(r!=NULL){
        r->task = t.tasknum;
        r->priority = t.priority;
        r->prox = NULL;
    }
    return r;
}


/**
 * @brief Adiciona uma task á queue
 * 
 * @param t Task a ser adicionada
 * @return int 0 caso saia com sucesso
 * @return int 1 caso contrario
 */
int addQueue(TASK t){
    QUEUE new = newBox(t);
    // caso em que a nova task fique na cabeça da lista (ie tem a maior prioridade)
    if (queue==NULL || queue->priority<new->priority){ // priority, sorted decrescente 5 -> 0
        new->prox=queue;
        queue = new;
    }else{
    // caso em que a nova task terá de ser inserida ordenadamente
        QUEUE curr = queue;
        while(curr->prox!=NULL && curr->prox->priority >= new->priority) curr = curr->prox;
        new->prox=curr->prox;
        curr->prox = new;
    }
    talk_client(t,"pending\n",8);
    return EXIT_SUCCESS;
}
    
