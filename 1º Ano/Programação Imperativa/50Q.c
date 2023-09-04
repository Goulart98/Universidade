//                                       50 QUESTÕES
//                                      PRIMEIRA PARTE

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>



// Questão 1 - Lê uma sequência de números terminada com 0 e imprime no ecrã o maior elemento da sequência.

void M(){
    int maior;
    scanf("%d",&maior);
    while(1){
        int num;
        scanf("%d",&num);
        if(num == 0) break;
        if(num > maior) maior = num;
    }
    printf("O maior elemento da sequência é: %d", maior);
}


// Questão 2 - Lê uma sequência de números terminada com 0 e imprime no ecrã a média da sequência.

void med(){
    int num = 0;
    int n = 0;
    int soma = 0;
    float media = 0;
    
    scanf("%d",&num);
    while(1){
        soma += num;
        if(soma == 0) break;
    }
    media = soma/n;
    printf("A média da sequência é %d",media);
}


// Questão 3 - Lê uma sequência de números terminada com 0 e imprime no ecrã o segundo maior elemento.

/*
void segmaior(){
    int maior;
    int smaior;

*/

// Questão 4 - 

int bitsUm (unsigned int x){
    int r=0;
    while(x!=0){
        if(x%2 == 1){
            r++;
            x = x/2;
        }
        else x = x/2;
    }
    return r;
}

// Questão 5* - 

int trailingZ (unsigned int n) {
	int res=0;
	while (n%2==0) {
		res++;
		n=n/2;
	}
	return res;
}


// Questão 6 - 

int qDig (int n) {
    int r = 0;
    
    while(n>0){
        r++;
        n = n/10;
    }
    return r;
}


// Questão 7 - 

char *mystrcat(char s1[], char s2[]) {
    int i=0, j=0;
    while(s1[i] != '\0') i++;
    
    while(s2[j] != '\0'){
        s1[i] = s2[j];
        i++;
        j++;
    }
    s1[i] = '\0';
    return s1;
}


// Questão 8* - 

char *mystrcpy(char s1[], const char s2[]) {
    int i=0;
    for (i=0;s2[i]!='\0';i++){
        s1[i]=s2[i];
    }
    return s1;
}

// Questão 9 - 

int mystrcmp(char s1[], char s2[]) {
    int i=0,j=0;
    
    while(s1[i] != '\0' && s2[j] != '\0'){
        if(s1[i] == s2[j]){
            i++;
            j++;
        }
        else break;
    }
    if(s1[i] == s2[j]) return 0;
    if(s1[i] < s2[j]) return -1;
    if(s1[i] > s2[j]) return 1;
    return 0;
}


// Questão 10 (Tá certo mas wtf) - 

char *mystrstr (char s1[], char s2[]) {
     int i=0,j=0,k,x=0;
     if(s1[i]=='\0' && s2[j]=='\0'){return s1;}
     for(i=0;s1[i] && !x;i++){
         x=1;
         for(j=i,k=0;s1[j] && s2[k] && x;j++,k++){
             if(s1[j]!=s2[k]) x=0;
         }
}
return (!s2[k] && x?s1+i-1:NULL);
}


// Questão 11 - 

void strrev (char s[]) {
    int i=0,j=0;
    while (s[j]!='\0'){
        j++;
    }
    char aux[strlen(s)];
    j=j-1;
    while (j>=0) {
        aux[i]=s[j];
        i++;
        j--;
    }
    aux[i]='\0';
    for (i=0;aux[i]!='\0';i++){
        s[i]=aux[i];
    }
}


// Questão 12 - 

int vogais(char c){
    int res;
    if (c=='a' || c=='e' || c=='i' || c=='o' || c=='u' || c=='A' || c=='E' || c=='I' || c=='O' || c=='U'){
        return 1;
    }
    return 0;
}

void strnoV (char t[]){
    char x[strlen (t) +1];
    int i,j=0;
    for(i=0;t[i]!='\0';i++){
        if (vogais (t[i])==0){
            x[j]=t[i];
            j++;
        }
    }
    x[j]='\0';
    for (i=0;x[i]!='\0';i++){
        t[i]=x[i];
    }
    t[i]='\0';
    
}


// Questão 13 - 



// Questão 14 - 

int conta(char x,char s[]){
    int i=0,conta=0;
    for (i=0;s[i];i++){
        if (s[i]==x){
            conta++;
        }
    }
    return conta;
}

char charMaisfreq (char s[]) {
    int i=0,x=0,res;
    char c;
    for(i=0;s[i]!='\0';i++){
        x=conta(s[i],s);
        if(x>res){
            res=x;
            c=s[i];
        }
    }
    return c;
}


// Questão 15 - 

int iguaisConsecutivos (char s[]) {
    int i=0, t=1, ac=0;
    
    for(i=0; s[i]; i++){
        while(s[i] == s[i+1]){
            i++;
            t++;
        }
        if(s[i] !=s [i+1]){
            if(t>ac) ac=t;
            t=1;
        }
    }
    return ac;
}


// Questão 16 - 

void eliminaRepseguidas (char s[]){
    int i=0,j;
    while (s[i]!='\0'){
        if (s[i]==s[i+1]){
            for (j=i;s[j]!='\0';j++){
                s[j]=s[j+1];
            }
        }else {
            i++;
        }
    }
    for (i=0;s[i]!='\0';i++){
        printf ("%c",s[i]); 
        }
    printf ("\n");

}

int difConsecutivos(char s[]) {
    int i=0,conta=1;
    eliminaRepseguidas(s);
    for (i=0;s[i]!='\0';i++){
        conta++;
    }
    printf("%d\n",conta);
 return conta;   
}


// Questão 17 - 

int maiorPrefixo (char s1 [], char s2 []) {
    int i=0, j=0, ac=0;
    
    while(s1[i] == s2[j] && s1[i] && s2[j]){
        ac++;
        i++;
        j++;
    }
    return ac;
}


// Questão 18 -

int maiorSufixo (char s1 [], char s2 []) {
    int i=0, j=0, ac=0;
    while(s1[i]) i++;
    while(s2[j]) j++;
    
    i-=1;
    j-=1;
    
    while(s1[i]==s2[j]){
        ac++;
        i--;
        j--;
    }
    return ac;
}


// Questão 19 - 

int sufPref (char s1[], char s2[]) {
  int i=0, j=0, ac=0;
    char *save=s2;
    for(;*s1;++s1){
        if(*s1==*s2){
            s2++;
            ac++;
        }
        else{
            ac=0;
            s2=save;
        }
    }
    return ac;
}


// Questão 20 - 

int contaPal (char s[]) {
    int i=0,conta=0;
    for (;s[i];i++){
        if (!isspace(s[i]) && isspace(s[i+1])){
            conta++;
        }
        if(!isspace(s[i]) && s[i+1]=='\0') {conta++;};
        
    }
    return conta;
}


// Questão 21 - 

int contaVogais (char s[]) {
    int i=0, c=0;
    
    while(s[i]){
        if(s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u' || s[i] == 'A' || s[i] == 'E' || s[i] == 'I' || s[i] == 'O' || s[i] == 'U'){
            c++;
            i++;
        }
        else i++;
    }
    return c;
}


// Questão 22 - 

int contida(char a[], char b[]){
    int i, j, c;
    c = 1;
    for (i = 0; a[i] && c; i++){
        c = 0;
        for (j = 0; b[j] && !c; j++)
            if (a[i] == b[j])
                c = 1;
    }
    return c;
}


// Questão 23 -

int palindroma (char s[]) {
    int j=0,i=0;
    for (;s[j];j++);
    j=j-1;
    for (i=0;s[i];i++){
        if (s[i]==s[j]){
            j--;
        }else {
            return 0;
        }
    }
    return 1;
}


// Questão 24 -

int remRep (char texto []) {
    int i=0, j=0;;
    
    for(i=0; texto[i]; i++){
        if(texto[i] == texto[i+1]){
            for(j=i+1; texto[j]; j++)texto[j] = texto[j+1];
            i=i-1;
        }
    }
    return strlen(texto);
}


// Questão 25 - 

int limpaEspacos (char texto[]) {
    int r=0,i=0,j=0;
    for(;texto[i];i++){
        if (isspace(texto[i]) && isspace(texto[i+1])){
            for (j=i;texto[j];j++){
                texto[j]=texto[j+1];
            }
            i=i-1;
        }
    }
    return strlen(texto);
}


// Questão 26 -

  void insere (int s[], int N, int x){
   int i=N;
   for (;i>=0;i--){
       if(x<s[i-1]){
           s[i]=s[i-1];
       }
       if(x>=s[i-1] && i!=0){
           s[i]=x;
           x=s[i-1];
       }
       if(i==0){
           s[i]=x;
       }
     }
   }


// Questão 27 - 

   void merge (int r [], int a[], int b[], int na, int nb){
       int i=0,j=0;
       for(;i<na;i++){
           r[i]=a[i];
       }
       for (j=0;i+j<na+nb;j++){
           insere(r,na+j,b[j]);
       }
   }


// Questão 28* -

int crescente (int a[], int i, int j){
       int r=1;
       for(;i<j;i++){
           if (a[i]<a[i+1])
           if (a[i]>a[i+1]){
               r=0;
               break;
           }
       }
       return r;
   }


// Questão 29 -




