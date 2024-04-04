#include "crianca.h"

typedef struct responsavel Responsavel;

typedef struct responsavel
{
    char nome[80];
    int telefone;
    Crianca *crianca;
    struct responsavel *proximo;

}Responsavel;

void adicionar_responsavel(char nome[100], int telefone, Responsavel **responsavel);
void excluir_responsavel(Responsavel **responsavel, char nome[80]);
void listar_responsavel_e_criancas(Responsavel *responsavel);
Responsavel *busca(Responsavel* responsavel, char nome[100]);