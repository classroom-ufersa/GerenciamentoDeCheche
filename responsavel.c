#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "responsavel.h"
#include "crianca.h"


void adicionar_responsavel(char nome[80], int telefone, Responsavel **responsavel)
{
    Responsavel *resp = (Responsavel*)malloc(sizeof(Responsavel));
    strcpy(resp->nome, nome);
    resp->telefone = telefone;
    resp->proximo = NULL;
    resp->crianca = NULL;
        
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
    Crianca *pont2;
    for (pont1 = responsavel; pont1 != NULL; pont1 = pont1->proximo)
    {
        printf("Nome: %s", pont1->nome);
        printf("Numero: %d", pont1->telefone);
        
        for (pont2 = pont1->crianca; pont2 != NULL; pont2 = pont2->proximo)
        {
            printf("Nome: %s", pont2->nome);
            printf("Documento: %d", pont2->doc);
            printf("Sexo: %s", pont2->sexo);
            printf("Idade: %d", pont2->idade);
            
        }
        
    }
    
}
