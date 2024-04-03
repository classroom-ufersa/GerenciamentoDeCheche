#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "responsavel.h"
#include "crianca.h"



void menu_crianca(){
    printf("== MENU ==\n");
    printf("1 - Adicionar crianca\n");
    printf("2 - Remover crianca\n");
    printf("3 - Edita os dados da crianca\n");
    printf("4 - imprimir dados\n");
    printf("0 - SAIR\n");
}


int verifica_nome(char nome[100])
{
    int i;
    for (i = 0; nome[i] != '\0'; i++)
    {
        int c = nome[i];
        if (!((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || c == ' '))
        {
            return 0;
        }
    }
    return 1;
}


void converte_caracteres(char nome[100])
{
    int i;
    for (i = 0; nome[i] != '\0'; i++)
    {
        int c = nome[i];
        if ('A' <= c && c <= 'Z')
        {
            nome[i] = c - 'A' + 'a';
        }
    }
}


void menu()
{
    printf("Bem vindo ao gerenciamento da creche Praxedes, escolha uma opção:\n");
    printf("\n------------------------------------------------------------------\n");
    printf("Escolha 1, para adicionar responsável!\n");
    printf("Escolha 2, para remover responsável!\n");
    printf("Escolha 3, para adicionar criança!\n");
    printf("Escolha 4, para remover criança!\n");
    printf("Escolha 5, para editar informações da criança!\n");
    printf("Escolha 6, para buscar criança por nome!\n");
    printf("Escolha 7, para listar responsáveis e suas crianças!\n");
    printf("Escolha 8, para sair!\n");
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



void escrever_para_arquivo(FILE *responsaveis_e_criancas, Responsavel *lista_responsaveis) 
{
    Responsavel *responsavel_atual = lista_responsaveis;

    
    while (responsavel_atual != NULL) 
    {
        
        fprintf(responsaveis_e_criancas, "Responsavel:\tNome:\t%s\tTelefone:\t%d\t", responsavel_atual->nome, responsavel_atual->telefone);

        struct crianca *crianca_atual = responsavel_atual->crianca;

        
        while (crianca_atual != NULL) 
        {
            
            fprintf(responsaveis_e_criancas, "\t\tCriancas:\t\tNome:\t%s\tIdade:\t%d\tDocumento:\t%d\tSexo:\t%s", crianca_atual->nome, crianca_atual->idade, crianca_atual->doc, crianca_atual->sexo);
            crianca_atual = crianca_atual->proximo;
        }

        responsavel_atual = responsavel_atual->proximo;
    }
}






int main(void)
{
    FILE *responsaveis_e_criancas = fopen("responsaveisEsuasCriancas.txt", "r");
    if (responsaveis_e_criancas == NULL)
    {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }

    Responsavel *responsavel;
    responsavel = NULL;
    
    int telefone;
    char nome[100];
    char nome_crianca[100];
    char novo_nome[100];
    int idade, doc;
    char sexo[10];
    
    while (fscanf(responsaveis_e_criancas, "%s %d", nome, &telefone) == 2)
    {
        adicionar_responsavel(nome, telefone, &responsavel);
        if(fscanf(responsaveis_e_criancas, "%s %d %d %s", nome_crianca, &idade, &doc, sexo) == 4)
        {
            responsavel->crianca = adiciona_crianca(responsavel->crianca, nome_crianca, idade, doc, sexo);
        }
        
    }
    
    listar_responsavel_e_criancas(responsavel);

    while (1)
    {
        int opcao = 0;
        menu();
        scanf("%d", &opcao);
        
        switch (opcao)
        {
        case 1:
            printf("Nome do responsável: \n");
            scanf(" %[^\n]", nome);

            if (verifica_nome(nome))
            {
                converte_caracteres(nome);
                printf("Telefone do responsável: \n");
                scanf("%d", &telefone);
                adicionar_responsavel(nome, telefone, &responsavel);
            }
            else
            {
                printf("Nome invalido!\n");
            }
            break;
        
        case 2:
            printf("Nome do responsável: \n");
            scanf(" %[^\n]", nome);
            excluir_responsavel(&responsavel, nome);
            break;

        case 3:
            printf("Nome: \n");
            scanf(" %[^\n]", nome);

            if (verifica_nome(nome))
            {
                converte_caracteres(nome);
                printf("Idade: \n");
                scanf("%d", &idade);
                printf("Documento: \n");
                scanf("%d", &doc);
                printf("Sexo: \n");
                scanf(" %[^\n]", sexo);
                responsavel->crianca = adiciona_crianca(responsavel->crianca, nome, idade, doc, sexo);
            }
            else
            {
                printf("Nome invalido!\n");
            }
            break;

        case 4:
            printf("Digite o nome da criança: \n");
            scanf(" %[^\n]", nome);
            responsavel->crianca = remove_crianca(responsavel->crianca, nome);
            break;

        case 5:
            printf("Nome: \n");
            scanf(" %[^\n]", nome);
            printf("Novo nome: \n");
            scanf(" %[^\n]", novo_nome);
            
            if (verifica_nome(nome) + verifica_nome(novo_nome) == 2)
            {
                converte_caracteres(nome);
                printf("Idade: \n");
                scanf("%d", &idade);
                printf("Documento: \n");
                scanf("%d", &doc);
                printf("Sexo: \n");
                scanf(" %[^\n]", sexo);
                responsavel->crianca = edita_crianca(responsavel->crianca, nome, novo_nome, idade, doc, sexo);  
            }
            else
            {
                printf("Nome invalido!\n");
            }
            break;

        case 6:
            printf("Nome: \n");
            scanf(" %[^\n]", nome);
            responsavel->crianca = busca_crianca(responsavel->crianca, nome);
            break;

        case 7:
            listar_responsavel_e_criancas(responsavel);
            break;

        case 8:

            fclose(responsaveis_e_criancas);
            FILE* arquivo2 = fopen("responsaveisEsuasCriancas.txt", "w");
            if (arquivo2 == NULL)
            {
                exit(1);
            }
            
            ordenar_lista(&responsavel);
            ordenar_criancas(&responsavel->crianca);
            escrever_para_arquivo(arquivo2, responsavel);
            fclose(arquivo2);
            free(responsavel->crianca);
            free(responsavel);

            return 0;
            break;
        
        default:
            printf("\nOpção inválida, escolha os valores de 1 à 8!\n");
            break;
        }
    }
    
    return 0;
}