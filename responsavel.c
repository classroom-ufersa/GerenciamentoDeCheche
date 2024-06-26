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


Responsavel *busca_crianca_nas_lst(Responsavel *r, char nome[100]){
    Responsavel *ref;
    Crianca *p;
    for(ref = r; ref != NULL; ref = ref->proximo){
        for(p = ref->crianca; p != NULL; p = p->proximo){
            if(strcmp(p->nome, nome) == 0){
                return ref;
            }
        }
    }
    return NULL;
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
        printf("Nome: %s\t", pont1->nome);
        printf("Numero: %d\n", pont1->telefone);
        
        for (pont2 = pont1->crianca; pont2 != NULL; pont2 = pont2->proximo)
        {
            printf("Nome: %s\t", pont2->nome);
            printf("Documento: %d\t", pont2->doc);
            printf("Sexo: %s\t", pont2->sexo);
            printf("Idade: %d\n", pont2->idade);
            
        }
        
    }
    
}

Responsavel *busca_responsavel(Responsavel *r, char nome[80]){
    Responsavel *p;
    for(p = r; p != NULL; p = p->proximo){
        if(strcmp(p->nome, nome) == 0){
            return p;
        }
    }
    return NULL;
}