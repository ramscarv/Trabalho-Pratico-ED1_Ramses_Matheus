#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Tamline 350 /* maximo de letras para cada linha do arquivo */
#define Maxline 60 /* maximo de linhas no arquivo  */

typedef struct lista{
    int vet[Maxline]; // vetor p/ armazenar repeticoes da msm palavra
    char info[30]; // palavras de ate 30 str
    struct lista* prox; // ponteiro para a prox lista
}Lista;

Lista * cria_lista();
Lista* insere_lista(Lista *l, char *letra, int linha);
void imprime_lista(Lista *l, int linha);
void libera_lista(Lista* l);
// kbecalho para a chamada das funcoes

int main(){

    Lista *lista = cria_lista(); 
    FILE *file;
    //file = fopen("rams and math.txt","r");
    file = fopen("mr.crowley.txt","r");
    //file = fopen("soneto.txt","r");
    //file = fopen("ligia joao gilberto.txt","r");

    if(file == NULL){
        printf("Arquivo invalido!\n");
    }
    //variaveis usadas p/ separar as palavras na str
    int contalinha = 0, l, c, j;

    char string[Tamline], string1[Tamline][Tamline];
    // abre o arquivo e le tds as palavras de cada linha do arquivo e tbm as printa
    while(fscanf(file," %[^\n]s", string) != EOF){
        printf("%s\n", string);
        // inicializa linha e coluna com 0
        l = 0, c = 0;
        //percorre a palavra lida na linha correspondente
        for(j = 0; j <= strlen(string); j++){
            //v se o caractere e nulo, espaco vaxio ou pontuacao
            if(string[j]==' ' || string[j]=='\0' || string[j]==',' || string[j]=='.' || string[j]==';' || string[j]==':'){
                    string1[l][c]='\0';
                    l++;
                    c = 0;
            }
            else{
                string1[l][c] = string[j];
                c++;}
 }
        for(j = 0; j < l; j++){
            //add a palavra no dicionario, junto com a linha
            lista = insere_lista(lista, string1[j], contalinha);}
        contalinha++; /* incrementa a qtd de linhas */
    }

    printf("\n");

    imprime_lista(lista, contalinha);
    libera_lista(lista);

    fclose(file);// fexa o arquivo usado
    return 0;
}

Lista * cria_lista(){
    return NULL;//cria e retorna uma lista vaxia
}

Lista* insere_lista(Lista* l, char *letra, int line){
    Lista *novo;
    Lista *ant = NULL; 
    Lista *p = l; 
    while (p != NULL){//v se a palavra já existe
       if (strcmp(p->info, letra) == 0)
          {
            p->vet[line]++;
            return l;
          }
       ant = p;
       p = p->prox;
    }
        novo = (Lista*)malloc(sizeof(Lista));
        strcpy(novo->info, letra);//copia de letra p/ novo->info

        int i;
        for(i = 0; i < Maxline; i++){
            novo->vet[i] = 0;//starter do vet com 0
        }
        novo->vet[line] = 1;// se a palavra nao existe, add a lista e soma 1 ao vet
            if (ant == NULL){//insere no inicio
            novo->prox = l;
            l = novo;
            }else{//insere no meio
            novo->prox = ant->prox;
            ant->prox = novo;}
    return l;
}


void imprime_lista(Lista *l, int linha){
    Lista *p;//pointer p percorrer a lista
    for(p = l; p!=NULL; p = p->prox){
        //percorre a lista
        printf("%s ",p->info);
        int i = 0;
        while (i < linha){//imprime o vetor
            if(p->vet[i] > 0){
                printf(" %d|%d -> ",i,p->vet[i]);
            }
            i++;
        }
        printf("\n");
    }
}

void libera_lista(Lista* l){
    Lista* p = l;
    while(p!=NULL){
        Lista* t = p->prox; 
        free(p);
        p = t;
    }free(l);
}
