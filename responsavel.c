#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "responsavel.h"




void adicionar_responsavel(char nome[80], int telefone, Responsavel **responsavel)
{
    Responsavel *resp = (Responsavel*)malloc(sizeof(Responsavel));
    strcpy(resp->nome, nome);
    resp->telefone = telefone;
    resp->proximo = NULL;
        
    if (*responsavel == NULL)
    {
        *responsavel = resp;
    }
    else
    {
        Responsavel *ultimo;
        for (ultimo = *responsavel; ultimo->proximo != NULL; ultimo = ultimo->proximo);
        ultimo->proximo = resp;
    }
    
}


void excluir_responsavel(Responsavel **responsavel, char nome[80])
{
    if (*responsavel == NULL)
    {
        return;
    }
    else
    {
        Responsavel *anterior = NULL;
        Responsavel *pont;
        for (pont = *responsavel; pont != NULL; pont = pont->proximo)
        {
            if (strcmp(nome, pont->nome) == 0)
            {
                if (anterior == NULL)
                {
                    Responsavel *temp;
                    temp = pont;
                    *responsavel = temp->proximo;
                    free(temp);
                }
                else
                {
                    Responsavel *temp;
                    temp = pont;
                    anterior->proximo = temp->proximo;
                    free(temp);
                }
            }
            anterior = pont;
        }
        
    }
    
    
}


void listar_responsavel_e_criancas(Responsavel *responsavel)
{
    Responsavel *pont1;
    Responsavel *pont2;
    for (pont1 = responsavel; pont1 != NULL; pont1 = pont1->proximo)
    {
        printf("Nome: %[^\n]79", pont1->nome);
        printf("Numero: %d", pont1->telefone);
        /*Nesse espaffo ficará um loop for para impressão das criançãs sob cuidade do responsável em questão*/
    }
    
}

Responsavel *busca_responsavel(Responsavel *r, char nome[80]){
    Responsavel *p;
    for(p = r; p != NULL; p = p->prox){
        if(strcmp(p->nome, nome) == 0){
            return p;
        }
    }
    return NULL;
}