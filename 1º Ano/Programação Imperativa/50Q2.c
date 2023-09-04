//                                       50 QUESTÕES
//                                      SEGUNDA PARTE



//                                      LISTAS LIGADAS 




// NOTA: VER QUESTÕES 16, 17, 24, 25, 26  E 27

typedef struct lligada {
int valor;
struct lligada *prox;
} *LInt;


// Questão 1 - Calcula o comprimento de uma lista ligada.

int length (LInt l){
    int r=0;
    while(l != NULL) {
        r++;
        l=l->prox;
    }
    return r;
}


// Questão 2 - Liberta espaço ocupado por uma lista.

void freeL (LInt l){
    LInt a;

    while(l){
        a = l-> prox;
        free(l);
        l = a;
    return a;
}


// Questão 3 - Imprime no ecrã os elementos da lista um por linha.

void imprimeL (LInt l){
    while(l){
        printf("%d \n", l->valor);
        l= l->prox;
    }
}


// Questão 4 - Inverte uma lista sem criar uma nova.

LInt reverseL (LInt l){
    LInt a = l, anterior= NULL;
    
    while(l){
        a = l->prox;
        l->prox = anterior;
        anterior = l;
        l = a;
    }
    l = anterior;
    return l;
}


// Questão 5 - Insere ordenadamente um elemento numa lista ordenada.

void insertOrd (LInt *l, int x){
    LInt l2 = malloc(sizeof (struct lligada));
    l2->valor = x;
    l2->prox = NULL;
    
    while(*l && x > (*l)->valor)
        l = &((*l)->prox);
    l2->prox = *l;
    *l = l2;
}


// Questão 6 - Remove um elemento de uma lista (retornando 0 se for possível e 1 se não for possível).

int removeOneOrd (LInt *l, int x){
    LInt b;
    int r = 1;
    
    while(*l && (*l)->valor < x){
        l=&((*l)->prox);
    }
    if(*l){
    b = ((*l)->prox);
    free(*l);
    (*l) = b;
    r = 0;
    }
    return r;
}


// Questão 7 - Une duas listas ordenadas l1 e l2 numa lista ordenada r.

void merge (LInt *r, LInt l1, LInt l2){
    
    while(l1 != NULL && l2 != NULL){
        if(l1->valor < l2->valor){
            (*r) = l1;
            r = &((*r)->prox);
            l1 = l1->prox;
        }
        else {
            (*r) = l2;
            r = &((*r)->prox);
            l2 = l2->prox;
        }
    }
    if(l1==NULL) (*r) = l2;
    else (*r) = l1;
    
    }


// Questão 8 - Parte a lista l em duas,  (retornando os endere¸cos dos primeiros
//elementos da lista em *mx e *Mx): uma com os elementos de l menores do que x e a outra com
//os restantes.

void splitQS (LInt l, int x, LInt *mx, LInt *Mx){
    while(l){
        if(l->valor < x){
            (*mx)=l;
            mx = &((*mx)->prox);
        }
        else{
            (*Mx)=l;
            Mx = &((*Mx)->prox);
        }
        l=l->prox;
    }
    (*mx) = (*Mx) = NULL;
    
}


// Questão 10 - Remove todas as ocorrências de um inteiro x de uma lista, retornando o número de 
//elementos removidos.

int removeAll (LInt *l, int x){
    LInt n;
    int i = 0;
   
    while(*l){
        if((*l)->valor == x){
            n = (*l)->prox;
            free(*l);
            (*l) = n;
            i++;
        }
        else l=&((*l)->prox);
        }
    return i;
}


// Questão 11 - Remove os valores repetidos de uma lista, deixando apenas a primeira ocorrência.

int removeDups (LInt *l){
    int x = 0;
    
    while(*l){
        x += removeAll(&(*l)->prox, (*l)->valor);
        l=&((*l)->prox);
    }
    
    return x;
}


// Questão 12 - Remove a primdira ocorrência do maior elemento de uma lista e retorna o valor 
//desse elemento.

int removeMaiorL (LInt *l){
    LInt *a = l;
    int maior = (*l)->valor;
    
    while(*a){
        if((*a)->valor > maior) maior = (*a)->valor;
        a = &((*a)->prox);
    }
    while(*l){
        if((*l)->valor == maior){
            a = &((*l)->prox);
            free(*l);
            *l=*a;
            return maior;
        }
        else l = &((*l)->prox);
    }
    return maior;
}


// Questão 13 - Remove o último elemento de uma lista não vazia.

void init (LInt *l){
    
    while(*l && (*l)->prox) l = &((*l)->prox);
        free(*l); // Apagar o último elemento
        *l=NULL; // Colocar NULL no lugar do último elemento para terminar a lista
}


// Questão 14 - Acrescenta um elemento no fim da lista.

void appendL (LInt *l, int x){
    LInt a = malloc(sizeof(struct lligada));
    a->valor = x;
    a->prox = NULL;
    
    while(*l){
        l = &((*l)->prox);
    }
    (*l) = a;
}


// Questão 15 - Adiciona a lista b à lista *a.

void concatL (LInt *a, LInt b){
    while(*a) a = &((*a)->prox);
    (*a) = b;
}


// Questão 16 - Cria uma nova lista ligada com os elementos pela ordem em que aparecem na lista argumento.




// Questão 17 -




// Questão 18 - Calcula o maior valor armazenado numa lista não vazia.

int maximo (LInt l){
    int maior= l->valor;
    
    while(l){
        if (l->valor > maior) maior = l->valor;
        l= l->prox;
    }
    return maior;
}


// Questão 19 - 

int take (int n, LInt *l){
    int tamanho = 0;
    
    while(*l && n > 0){
        if (n>0){
            l = &((*l)->prox);
            n--;
            tamanho++;
        }
        else{
            l = &((*l)->prox);
        }
    }    
    free(*l);
    *l = NULL;
    return tamanho;
}


// Questão 20 - 

int drop (int n, LInt *l){
    int tamanho = 0;
    LInt *aux = l;
    while(*aux && n > 0){
        if (n>0){
            aux = &((*aux)->prox);
            n--;
            tamanho++;
        }
        else{
            aux = &((*aux)->prox);
        }
    }
    free (*l);
    *l = *aux;
    return tamanho;
}


// Questão 21 - 

LInt NForward (LInt l, int N){
    
    while(N>0){
    l = l->prox;
    N--;
    }
    
    return l;
}


// Questão 22 -

int listToArray (LInt l, int v[], int N){
    int i = 0;
    while(i<N && l){
        v[i] = l->valor;
        l = l->prox;
        i++;
    }
    return i;
}


// Questão 23 - 

/*
LInt arrayToList (int v[], int N){
    int i=0;
    LInt *aux;
    
    while(i<N){
        (*aux) = malloc (sizeof(struct lligada));
        (*aux)->valor = v[i];
        aux = &((*aux)->prox);
    }
    return *aux;
}
*/


// Questão 24 - 


// Questão 25 - 

void remreps (LInt l){
    LInt p, pt;
    while(l)
    {   p = l->prox;
        while(p && l->valor == p->valor){
            pt = p->prox;
            free(p);
            p = pt;
        }
        l->prox = p;
        l = l->prox;
    }
}


// Questão 26 - 

LInt rotateL (LInt l){
    if (l){
        LInt inicio = l;
        LInt aux = l;
        if (l -> prox != NULL) aux = l -> prox;
        while (l -> prox){
            l = l-> prox;
        }
        l -> prox = inicio;
        inicio -> prox = NULL;
        l = aux;
        return l;
    }
    else return NULL;
}


// Questão 27 -

LInt parte (LInt l){
	LInt pares;
	LInt *ep =&pares;
	while(l){
		if(l->prox){
  			*ep=l->prox;
  			ep=&(l->prox->prox);
  			l->prox=l->prox->prox;
		}
		l=l->prox;
	}
	*ep=NULL;
	return pares;
}




//                                      ÁRVORES BINÁRIAS 




// NOTA: VER QUESTÃO 38, 39, 41 E 51.

typedef struct nodo {
int valor;
struct nodo *esq, *dir;
} *ABin;


// Questão 28 - Calcula a altura de uma árvore binária.

int altura (ABin a){
    int altesq, altdir, x = 0;
    if(a){
        altesq = altura(a->esq);
        altdir = altura(a->dir);
        if(altesq > altdir) x = 1 + altura(a->esq);
        else x = 1 + altura(a->dir);
    }
	return x;
}


// Questão 29 - Cria uma cópia de uma árvore binária.

ABin cloneAB (ABin a) {
    ABin b;
    
    if(!a) b = NULL;
    else {
        b = (ABin)malloc(sizeof(struct nodo));
        b->valor = a->valor;
        b->esq = cloneAB(a->esq);
        b->dir = cloneAB(a->dir);
    }
    return b;
}


// Questão 30 - Inverte uma árvore.

void mirror (ABin *a) {
    ABin r;
    if (*a){
        r = (*a)->dir;
        (*a)->dir = (*a)->esq;
        (*a)->esq = r;
        
        mirror(&((*a)->dir));
        mirror(&((*a)->esq));
      
    }
}


// Questão 31 - Cria uma lista ligada de inteiros a partir de uma travessia inorder de uma árvore 
//binária.

void inorder (ABin a, LInt *l) {
    if(a==NULL) (*l) = NULL;
    else{
        inorder(a->esq, l);
        while(*l) l = &((*l)->prox);
        (*l) = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        l = &((*l)->prox);
        inorder(a->dir, l);
    }
}


// Questão 32 - Cria uma lista ligada de inteiros a partir de uma travessia preorder de uma árvore
//binária.

void preorder (ABin a, LInt * l) {
    LInt aux;
    
    if(a == NULL) *l = NULL;
    else{
        *l = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        preorder(a->esq, &((*l)->prox));
        aux = *l;
        while(aux->prox != NULL) aux = aux->prox;
        preorder(a->dir, &(aux->prox));
    }
}


// Questão 33 - Cria uma lista ligada de inteiros a partir de uma travessia posorder de uma árvore
//binária.

 void posorder (ABin a, LInt * l) {
    if(a == NULL) *l = NULL;
    else{
        posorder(a->esq, l);
        while(*l) l = &((*l)->prox);
        posorder(a->dir, l);
        while(*l) l = &((*l)->prox);
        (*l) = malloc(sizeof(struct lligada));
        (*l)->valor = a->valor;
        (*l)->prox = NULL;
    }
}

// Questão 34 - Calcula o nível (menor) a que um elemento está numa árvore binária.

int depth (ABin a, int x) {
    int cont = 1, le = 0, ld = 0;
    
    if(a==NULL) return -1;
    if(a->valor == x) return 1;
    else{
        le = depth(a->esq,x);
        ld = depth(a->dir,x);
        if(ld < 0) cont += le;
        if(le < 0) cont += ld;
        if(ld > 0 && le > 0 && le > ld) cont += ld;
        if (ld > 0 && le > 0 && le < ld) cont += le;
    }
    return cont;
}


// 35 - liberta o espaço ocupado por uma árvore binária, retornando o número de nodos libertados.

int freeAB (ABin a) {
    int c=0,cld=0, cle=0;
    if (a){
        if (a->esq) cle = freeAB(a->esq);
        if (a->dir) cld = freeAB(a->dir);
        free(a);
        c += (cle + cld + 1);
    }
    return c;
}


// 36 - Remove (libertando o espaço respectivo) todos os elementos da árvore *a que estão a uma profundidade superior a l, 
//retornando o número de elementos removidos.

 int pruneAB (ABin *a, int l) {
     int c = 0;
     if(*a){
         c += pruneAB (&(*a)->esq, l-1);
         c += pruneAB (&(*a)->dir, l-1);
         if(l<1){
             free(*a);
             (*a) = NULL;
             c++;
         }
     }
     return c;
 }


 // 37 - Testa se duas árvores são iguais.

int iguaisAB (ABin a, ABin b) {
    int r = 0;
    
    if(!a && !b) r = 1;
    if(a && b){
        if(a->valor == b->valor) r = 1;
        else r = 0;
        r = r && iguaisAB(a->esq,b->esq);
        r = r && iguaisAB(a->dir,b->dir);
    }
    return r;
}


// 38 - 

/*
LInt nivelL (ABin a, int n) {
    LInt l1 = NULL, l2 = NULL, x;
    if(a){
        if (n==1){
            l1 = malloc(sizeof(struct lligada));
            l1->valor = a->valor;
            l1->prox = NULL;
        }
        else{
            l1 = nivelL(a->esq, n-1);
            l2 = nivelL(a->dir, n-1);
            if(l1){
                x = l1;
                while(x && x->prox) x = x->prox;
                l1->prox = l2;
            }
            else if(l2) return l2;
        }
    }
    return l1;;
}
*/


// 39 - 


// 40 - 

int dumpAbin (ABin a, int v[], int N) {
    int i = 0, esq = 0, dir = 0;
    
    if(a){
        if(a->esq) esq = dumpAbin(a->esq,v,N);
        if(esq<N){
            v[esq] = a->valor;
            i++;
        }
        if(esq+1 < N && a->dir) dir = dumpAbin(a->dir,v,N-esq-1);
        i = i + esq + dir;
    }
    
    return i;
}


// 41 - 


// 42 - Calcula o número de nodos sem descendentes.

int contaFolhas (ABin a) {
    int cont = 0, le = 0, ld = 0;
    
    if (a){
        if(!(a->esq) && !(a->dir)) cont++;
        le = contaFolhas(a->esq);       
        ld = contaFolhas(a->dir);
    }
    cont = cont + le + ld; 
    
    return cont;
}


// 43 -  Cria uma árvore binária com o resultado de inverter a árvore binária inicial.

ABin cloneMirror (ABin a) {
    ABin b = NULL;
    
    if(a){
        b = malloc(sizeof(struct nodo));
        b->valor = a->valor;
        b->dir = b->esq = NULL;
        if(a->dir) b->esq = cloneMirror(a->dir);
        if(a->esq) b->dir = cloneMirror(a->esq);
    }
    return b;
}


// 44 - Adiciona um elemento a uma árvore binária de procura. Retorna 1 se o elemento já estiver presente na
//árvore e 0 caso contrário.

int addOrd (ABin *a, int x) {
    int r = 0;
    
    while(*a && !r){          // Enquanto for houver árvore e r for verdade (r==1).
        if((*a)->valor == x) r = 1;
        else{
            if((*a)->valor > x) a = &((*a)->esq);
            else if((*a)->valor < x) a = &((*a)->dir);
        }
    }
    
    if(!*a){                 // Adicionar x quando este não está na árvore.
        (*a) = malloc(sizeof(struct nodo));
        (*a)->valor = x;
        (*a)->esq = NULL;
        (*a)->dir = NULL;
    }
    
    return r;
}

// 45 - Testa se um elemento pertence a uma árvore binária de procura.

int lookupAB (ABin a, int x) {
   int r = 0;
   
   if (!a) r = 0;
   else{
       if(a->valor == x) r = 1;
       else{
           if(a->valor > x) r = lookupAB(a->esq,x);
           else r = lookupAB(a->dir,x);
       }
   }
    return r;
}


// 46 - Calcula o nível em que um elemento se encontra numa árvore binária.

int depthOrd (ABin a, int x){
    int n;
    
    if(!a) return -1;
    
    if(a->valor == x) return 1;                // Primeiro nível
    if(a->valor > x) n = depthOrd(a->esq, x);  // Nodo esquerdo
    else n = depthOrd(a->dir, x);              // Nodo direito
    if (n == -1) return -1;                    // Se não existir o elemento até este ponto
    else return (n+1);
}


// 47 - Calcula o maior elemento de uma árvore binária.

int maiorAB (ABin a) {
    int n;
    
    if(a){
        if(a->esq == NULL && a->dir == NULL) n = (a->valor);
        else{
            if(a->dir) n = maiorAB(a->dir);
            else n = (a->valor);
        }
    }
    return n;
}


// 48 - Remove o maior elemento de uma árvore binária.

void removeMaiorA (ABin *a) {
    while (*a && (*a)->dir) a = &((*a)->dir);
    free(*a);
    *a = (*a)->esq;
}


// 49 - Calcula quantos elementos maiores que x tem a árvore binária.

int quantosMaiores (ABin a, int x) {
    int n=0;
    
    if(!a) return 0;
    if(a){
        if(a->esq == NULL && a->dir == NULL){
            if(a->valor >x) n=1;
            else n=0;
        }
        else{
            if(a->valor >x){ 
                n++;
                n += quantosMaiores(a->dir,x) + quantosMaiores(a->esq,x);
            }
            else n += quantosMaiores(a->dir,x) + quantosMaiores(a->esq,x);
        }
    }
    return n;
}


// 50 -  Constrói uma árvore binária de procura a partir de uma lista ligada ORDENADA.

void listToBTree (LInt l, ABin *a) {
    while(l){
        (*a) = malloc(sizeof(struct nodo));
        (*a)->valor = l->valor;
        (*a)->esq = NULL;
        a = &((*a)->dir);
        l = l->prox;
    }
}


// 51 - 

int menor(ABin a , int x){
     int r=0;
     if(a==NULL) r=1;
     else if(a->valor<x && menor(a->esq,x) && menor(a->dir,x)) r=1;
     return r;
 }
 
 int maior(ABin a , int x){
     int r=0;
     if(a==NULL) r=1;
     else if(a->valor>x && maior(a->esq,x) && maior(a->dir,x)) r=1;
     return r;
 }
 
 
 
int deProcura (ABin a) {
    int r=0;
    if(a==NULL)r=1;
    else if(menor(a->esq,a->valor)&& maior(a->dir,a->valor) && deProcura(a->esq) && deProcura(a->dir)){
        r=1;
    }
    return r;
}
