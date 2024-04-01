#include "crianca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct crianca{
    char nome[50];
    int idade;
    int doc;
    char sexo[10];
    struct crianca *prox;
}Crianca;


Crianca *cria_crianca(void){
    return NULL;
}

Crianca *adiciona_crianca(Crianca *c, char nome[50], int idade, int doc, char sexo[10]){
    Crianca *novo = (Crianca*) malloc(sizeof(Crianca));
    if(novo == NULL){
        printf("Erro na alocacao de crianca!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->doc = doc;
    strcpy(novo->sexo, sexo);
    novo->prox = c;
    
    return novo;
}

Crianca *busca_crianca(Crianca *c, char nome[100]){
    Crianca *p;
    for(p = c; p != NULL; p = p->prox){
        if(strcmp(p->nome, nome) == 0){
            return p;
        }
    }
    return NULL;
}

Crianca *remove_crianca(Crianca *c, char nome[100]){
    Crianca *ant = NULL;
    Crianca *p = c;
    
    while(p != NULL && strcmp(p->nome, nome) != 0){
        ant = p;
        p = p->prox;
    }
    
    if(ant == NULL){
        c = p->prox;
    }
    else{
        ant->prox = p->prox;
    }
    
    free(p);
    return c;

}

Crianca *edita_crianca(Crianca *c, char nome[50], char Nnome[50], int idade, int doc, char sexo[10]){
    Crianca *p = busca_crianca(c, nome);

    if(p == NULL){
        printf("Nome nao encontrado!\n");
        exit(1);
    }

    if(p == c){
        strcpy(c->nome, Nnome);
        c->idade = idade;
        c->doc = doc;
        strcpy(c->sexo, sexo);
    }
    else{
        strcpy(p->nome, Nnome);
        p->idade = idade;
        p->doc = doc;
        strcpy(p->sexo, sexo);
    }
    
    return c;
}

void libera_crianca(Crianca *c){
    Crianca *p = c;
    while(p != NULL) {
        Crianca *t = p->prox;
        free(p);
        p = t;
    }
}

int vazia(Crianca *c){
    if(c == NULL){
        printf("Lista de criancas vazia!\n");
        return 1;
    }
    else{
        return 0;
    }
}