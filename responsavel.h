#ifndef RESPONSAVEL_H
#define RESPONSAVEL_H
#include "crianca.h"
typedef struct responsavel Responsavel;

typedef struct responsavel
{
    char nome[80];
    int telefone;
    Crianca *crianca;
    struct responsavel *proximo;

}Responsavel;

Responsavel *busca_responsavel(Responsavel *r, char nome[100]);
Responsavel *busca_crianca_nas_lst(Responsavel *r, char nome[100]);
void adicionar_responsavel(char nome[80], int telefone, Responsavel **responsavel);
void excluir_responsavel(Responsavel **responsavel, char nome[80]);
void listar_responsavel_e_criancas(Responsavel *responsavel);

#endif