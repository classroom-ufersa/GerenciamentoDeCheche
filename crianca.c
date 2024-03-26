#include "crianca.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
enum sexo{
    MASCULINO,
    FEMININO
};

struct crianca{
    char nome[50];
    int idade;
    int doc;
    Sexo sex;
    Crianca *prox;
    Crianca *ant;
};

void menu_crianca(){
    printf("== MENU ==\n");
    printf("1 - Adicionar crianca\n");
    printf("2 - Remover crianca\n");
    printf("3 - Edita os dados da crianca\n");
    printf("0 - SAIR");
}

Crianca *cria_crianca(void){
    return NULL;
}

Crianca *adiciona_crianca(Crianca *c, char nome[50], int idade, int doc, int r){
    Crianca *novo = (Crianca*) malloc(sizeof(Crianca));
    if(novo == NULL){
        printf("Erro na alocacao de crianca!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->doc = doc;
    novo->sex = (r == 0) ? MASCULINO : FEMININO;
    novo->prox = c;
    novo->ant = NULL;
    if(c != NULL){
        c->ant = novo;
        return novo;
    }
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
    Crianca *p = busca_crianca(c, nome);
    if(p == NULL){
        printf("Nome nao encontrado!\n");
        return c;
    }

    if(p == c){
        c = p->prox;
    }
    else{
        p->ant->prox = p->prox;
    }

    if(p->prox != NULL){
        p->prox->ant = p->ant;
    }

    free(p);
    return c;

}

Crianca *edita_crianca(Crianca *c, char nome[50], char Nnome[50], int idade, int doc, int r){
    Crianca *p = busca_crianca(c, nome);

    if(p == NULL){
        printf("Nome nao encontrado!\n");
        exit(1);
    }

    if(p == c){
        strcpy(c->nome, Nnome);
        c->idade = idade;
        c->doc = doc;
        c->sex = (r == 0) ? MASCULINO : FEMININO;
    }
    else{
        strcpy(p->nome, Nnome);
        p->idade = idade;
        p->doc = doc;
        p->sex = (r == 0) ? MASCULINO : FEMININO;
    }
    
    return c;
}