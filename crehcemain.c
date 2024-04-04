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




void ordenar(Responsavel **lista_responsaveis) {
    if (*lista_responsaveis == NULL || (*lista_responsaveis)->proximo == NULL) {
        return; // Lista vazia ou com apenas um elemento, nada a fazer
    }

    // Ordenação dos responsáveis pelo nome
    int trocou;
    do {
        trocou = 0;
        Responsavel *atual = *lista_responsaveis;
        Responsavel *anterior = NULL;
        Responsavel *proximo = atual->proximo;

        while (proximo != NULL) {
            if (strcmp(atual->nome, proximo->nome) > 0) {
                // Troca de posição
                trocou = 1;
                atual->proximo = proximo->proximo;
                proximo->proximo = atual;
                if (anterior == NULL) {
                    *lista_responsaveis = proximo;
                } else {
                    anterior->proximo = proximo;
                }
                // Atualização dos ponteiros
                anterior = proximo;
                proximo = atual->proximo;
            } else {
                // Avança na lista
                anterior = atual;
                atual = proximo;
                proximo = proximo->proximo;
            }
        }
    } while (trocou);

    // Ordenação das crianças de cada responsável pelo nome
    Responsavel *atual_responsavel = *lista_responsaveis;
    while (atual_responsavel != NULL) {
        Crianca *atual_crianca = atual_responsavel->crianca;
        Crianca *anterior_crianca = NULL;
        int trocou_crianca;

        do {
            trocou_crianca = 0;
            atual_crianca = atual_responsavel->crianca;
            anterior_crianca = NULL;

            while (atual_crianca != NULL && atual_crianca->proximo != NULL) {
                Crianca *proxCrianca = atual_crianca->proximo;

                if (strcmp(atual_crianca->nome, proxCrianca->nome) > 0) {
                    // Troca de posição
                    trocou_crianca = 1;
                    atual_crianca->proximo = proxCrianca->proximo;
                    proxCrianca->proximo = atual_crianca;
                    if (anterior_crianca == NULL) {
                        atual_responsavel->crianca = proxCrianca;
                    } else {
                        anterior_crianca->proximo = proxCrianca;
                    }
                    // Atualização dos ponteiros
                    anterior_crianca = proxCrianca;
                } else {
                    // Avança na lista
                    anterior_crianca = atual_crianca;
                    atual_crianca = proxCrianca;
                }
            }
        } while (trocou_crianca);

        atual_responsavel = atual_responsavel->proximo;
    }
}




void escrever_para_arquivo(FILE *responsaveis_e_criancas, Responsavel *lista_responsaveis) 
{
    Responsavel *responsavel_atual = lista_responsaveis;

    
    while (responsavel_atual != NULL) 
    {
        fprintf(responsaveis_e_criancas, "Responsavel:\n");
        fprintf(responsaveis_e_criancas, "Nome:\t%s\tTelefone:\t%d\n", responsavel_atual->nome, responsavel_atual->telefone);

        struct crianca *crianca_atual = responsavel_atual->crianca;

        if (crianca_atual != NULL)
        {
            fprintf(responsaveis_e_criancas, "Criancas:\n");
        }
        
        while (crianca_atual != NULL) 
        {
            fprintf(responsaveis_e_criancas, "Nome:\t%s\tIdade:\t%d\tDocumento:\t%d\tSexo:\t%s\n", crianca_atual->nome, crianca_atual->idade, crianca_atual->doc, crianca_atual->sexo);
            crianca_atual = crianca_atual->proximo;
        }

        responsavel_atual = responsavel_atual->proximo;
    }
}


void ler_do_arquivo(FILE *arquivo, Responsavel **lista_responsaveis) {
    char linha[1000]; 

    char nome_responsavel[100];
    int telefone_responsavel;
    Responsavel *ultimo_responsavel = NULL; 

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        if (strcmp(linha, "Responsavel:\n") == 0) {
            if (fgets(linha, sizeof(linha), arquivo) == NULL) {
                printf("Erro ao ler dados do responsável!\n");
                exit(1);
            }
            if (sscanf(linha, "Nome:\t%s\tTelefone:\t%d\n", nome_responsavel, &telefone_responsavel) != 2) {
                printf("Erro ao ler dados do responsável!\n");
                exit(1);
            }
            adicionar_responsavel(nome_responsavel, telefone_responsavel, lista_responsaveis);
            ultimo_responsavel = busca(*lista_responsaveis, nome_responsavel); 
        } else if (strcmp(linha, "Criancas:\n") == 0) {
            if (ultimo_responsavel == NULL) {
                printf("Erro: Crianças encontradas sem responsável associado!\n");
                exit(1);
            }
            
            int tem_criancas = 0; 
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                if (strcmp(linha, "Responsavel:\n") == 0) {
                    break; 
                } else if (strncmp(linha, "Nome:", 5) == 0) {
                    char nome_crianca[100], sexo[10];
                    int idade, doc;
                    if (sscanf(linha, "Nome:\t%s\tIdade:\t%d\tDocumento:\t%d\tSexo:\t%s\n", nome_crianca, &idade, &doc, sexo) != 4) {
                        printf("Erro ao ler dados da criança!\n");
                        continue; 
                    }
                    
                    ultimo_responsavel->crianca = adiciona_crianca(ultimo_responsavel->crianca, nome_crianca, idade, doc, sexo);
                    tem_criancas = 1; 
                }
            }
            if (!tem_criancas) {
                
                if (ultimo_responsavel->proximo != NULL) {
                    ultimo_responsavel = ultimo_responsavel->proximo;
                }
            }
        }
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
    char nome_respondavel[100];
    char novo_nome[100];
    int idade, doc;
    char sexo[10];
    
    ler_do_arquivo(responsaveis_e_criancas, &responsavel);
    
    ordenar(&responsavel);
    
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
            printf("Nome da crianca: \n");
            scanf(" %[^\n]", nome);
            printf("Nome do responsavel: \n");
            scanf(" %[^\n]", nome_respondavel);
            Responsavel *ref = busca(responsavel, nome_respondavel);

            if (ref == NULL)
            {
                printf("Responsavel nao encontrado!\n");
                break;
            }
            
            if (verifica_nome(nome))
            {
                converte_caracteres(nome);
                printf("Idade: \n");
                scanf("%d", &idade);
                printf("Documento: \n");
                scanf("%d", &doc);
                printf("Sexo: \n");
                scanf(" %[^\n]", sexo);
                ref->crianca = adiciona_crianca(ref->crianca, nome, idade, doc, sexo);
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
            
            ordenar(&responsavel);
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