#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "responsavel.h"
#include "crianca.h"

typedef struct crianca{
    char nome[50];
    int idade;
    int doc;
    char sexo[10];
    struct crianca *proximo;
}Crianca;

void menu_crianca(){
    printf("== MENU ==\n");
    printf("1 - Adicionar crianca\n");
    printf("2 - Remover crianca\n");
    printf("3 - Edita os dados da crianca\n");
    printf("4 - imprimir dados\n");
    printf("0 - SAIR\n");
}

void menu()
{
    printf("Bem vindo ao gerenciamento da creche Praxedes, escolha uma opção:\n");
    printf("------------------------------------------------------------------");
    printf("Escolha 1, para adicionar responsável!");
    printf("Escolha 2, para remover responsável!");
    printf("Escolha 3, para adicionar criança!");
    printf("Escolha 4, para remover criança!");
    printf("Escolha 5, para editar informações da criança!");
    printf("Escolha 6, para buscar criança por nome!");
    printf("Escolha 7, para listar responsáveis e suas crianças!");
    printf("Escolha 8, para sair!");
}


int comparar_criancas(const void *a, const void *b) {
    const Crianca *crianca1 = (const Crianca *)a;
    const Crianca *crianca2 = (const Crianca *)b;
    return strcmp(crianca1->nome, crianca2->nome);
}


void ordenar_criancas(Crianca **lista) {
    
    int tamanho = 0;
    Crianca *atual = *lista;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }

    
    Crianca **array = (Crianca **)malloc(tamanho * sizeof(Crianca *));
    if (array == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    
    atual = *lista;
    for (int i = 0; i < tamanho; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    
    qsort(array, tamanho, sizeof(Crianca *), comparar_criancas);

    
    *lista = array[0];
    for (int i = 0; i < tamanho - 1; i++) {
        array[i]->proximo = array[i + 1];
    }
    array[tamanho - 1]->proximo = NULL;

    
    free(array);
}


int comparar_responsaveis(const void *a, const void *b) {
    const Responsavel *resp1 = (const Responsavel *)a;
    const Responsavel *resp2 = (const Responsavel *)b;
    return strcmp(resp1->nome, resp2->nome);
}

void ordenar_lista(Responsavel **lista) {
    
    int tamanho = 0;
    Responsavel *atual = *lista;
    while (atual != NULL) {
        tamanho++;
        atual = atual->proximo;
    }


    Responsavel **array = (Responsavel **)malloc(tamanho * sizeof(Responsavel *));
    if (array == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória\n");
        exit(EXIT_FAILURE);
    }

    atual = *lista;
    for (int i = 0; i < tamanho; i++) {
        array[i] = atual;
        atual = atual->proximo;
    }

    qsort(array, tamanho, sizeof(Responsavel *), comparar_responsaveis);

    *lista = array[0];
    for (int i = 0; i < tamanho - 1; i++) {
        array[i]->proximo = array[i + 1];
    }
    array[tamanho - 1]->proximo = NULL;

    free(array);
}



int main(void)
{
    FILE *responsaveis_e_criancas = fopen("responsaveisEsuasCriancas.txt", "w");
    if (responsaveis_e_criancas == NULL)
    {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }

    Responsavel *responsavel;
    if (responsavel == NULL)
    {
        printf("Erro ao alocar responsável!");
        exit(1);
    }
    
    int telefone;
    char nome[80];
    int doc;
    int idade;
    char sexo[10];
    
    while (fscanf(responsaveis_e_criancas, "%s %d", nome, &telefone) == 2) 
    {
        char nome_crianca[100];
        int idade, doc;
        char sexo[10];

        while (fscanf(responsaveis_e_criancas, "%s %d %d %s", nome_crianca, &idade, &doc, sexo) == 4) 
        {
                adicionar_crianca(responsavel, nome_crianca, idade, doc, sexo);
        }
    }

    while (1)
    {
        int opcao = 0;
        
        menu();
        
        scanf("%d", &opcao);

        char nome1[80];
        int telefone;

        char nome2[80];
        
        switch (opcao)
        {
        case 1:
            printf("Nome do responsável: \n");
            scanf(" %[^\n]79", nome1);
            printf("Telefone do responsável: \n");
            scanf("%d", &telefone);
            adicionar_responsavel(nome1, telefone, &responsavel);
            break;
        
        case 2:
            printf("Nome do responsável: \n");
            scanf(" %[^\n]", nome2);
            excluir_responsavel(&responsavel, nome2);
            break;

        case 3:
            break;

        case 4:
            break;

        case 5:
            break;

        case 6:
            break;

        case 7:
            listar_responsavel_e_criancas(responsavel);
            break;

        case 8:
            ordenar_lista(&responsavel);
            ordenar_criancas(&responsavel->crianca);
            /*parte para passar lista ordenada pro arquivo*/

            return 0;
            break;
        
        default:
            printf("\nOpção inválida, escolha os valores de 1 à 8!\n");
            break;
        }
    }
    
    

    return 0;
}