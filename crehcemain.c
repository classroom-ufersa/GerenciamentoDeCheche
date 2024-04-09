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
    printf("0 - SAIR\n");
}

int verifica_positivo(int n){
    if(n > 0){
        return 1;
    }
    else{
        return 0;
    }
}

int verifica_nome(char nome[100])
{
    int i;
    for (i = 0; nome[i] != '\0'; i++)
    {
        int c = nome[i];
        if (!((('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z')) || c == ' ' || c == '^' || c == '~'))
        {
            return 0;
        }
    }
    return 1;
}

int verificar_criancas(Responsavel *ultimo_responsavel) {
    if (ultimo_responsavel != NULL && ultimo_responsavel->crianca != NULL) {
        return 1; 
    } else {
        return 0; 
    }
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
    printf("\nBem vindo ao gerenciamento da creche Praxedes, escolha uma opção:\n");
    printf("\n------------------------------------------------------------------\n");
    printf("Escolha 1, para adicionar responsável!\n");
    printf("Escolha 2, para remover responsável!\n");
    printf("Escolha 3 para acessar o menu crianca do responsavel!\n");
    printf("Escolha 4 para buscar por crianca na lista dos responsaveis\n");
    printf("Escolha 5, para listar responsáveis e suas crianças!\n");
    printf("Escolha 6, para sair!\n");
}




void ordenar(Responsavel **lista_responsaveis) {
    if (*lista_responsaveis == NULL || (*lista_responsaveis)->proximo == NULL) {
        return; 
    }

    
    int trocou;
    do {
        trocou = 0;
        Responsavel *atual = *lista_responsaveis;
        Responsavel *anterior = NULL;
        Responsavel *proximo = atual->proximo;

        while (proximo != NULL) {
            if (strcmp(atual->nome, proximo->nome) > 0) {
                
                trocou = 1;
                atual->proximo = proximo->proximo;
                proximo->proximo = atual;
                if (anterior == NULL) {
                    *lista_responsaveis = proximo;
                } else {
                    anterior->proximo = proximo;
                }
                
                anterior = proximo;
                proximo = atual->proximo;
            } else {
                
                anterior = atual;
                atual = proximo;
                proximo = proximo->proximo;
            }
        }
    } while (trocou);

    
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
                    
                    trocou_crianca = 1;
                    atual_crianca->proximo = proxCrianca->proximo;
                    proxCrianca->proximo = atual_crianca;
                    if (anterior_crianca == NULL) {
                        atual_responsavel->crianca = proxCrianca;
                    } else {
                        anterior_crianca->proximo = proxCrianca;
                    }
                    
                    anterior_crianca = proxCrianca;
                } else {
                    
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
            ultimo_responsavel = busca_responsavel(*lista_responsaveis, nome_responsavel);
        } 
        else if (strcmp(linha, "Criancas:\n") == 0) {
            if (ultimo_responsavel == NULL) {
                printf("Erro: Crianças encontradas sem responsável associado!\n");
                exit(1);
            }
            
            long int posicao_atual = ftell(arquivo);
            
            while (fgets(linha, sizeof(linha), arquivo) != NULL) {
                if (strncmp(linha, "Nome:", 5) == 0) {
                    char nome_crianca[100], sexo[10];
                    int idade, doc;
                    if (sscanf(linha, "Nome:\t%s\tIdade:\t%d\tDocumento:\t%d\tSexo:\t%s\n", nome_crianca, &idade, &doc, sexo) != 4) {
                        printf("Erro ao ler dados da criança!\n");
                        continue; 
                    }
                    
                    ultimo_responsavel->crianca = adiciona_crianca(ultimo_responsavel->crianca, nome_crianca, idade, doc, sexo);
                } else if (strcmp(linha, "Responsavel:\n") == 0) {
                    break;  
                }
            }
            
            fseek(arquivo, posicao_atual, SEEK_SET);
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
                while (scanf("%d", &telefone) != 1 || !verifica_positivo(telefone)) {
                printf("Entrada inválida. Por favor, digite um número inteiro positvo:\n");
                while (getchar() != '\n');
                }
                adicionar_responsavel(nome, telefone, &responsavel);
                printf("Responsável adicionado!\n");
            } else{
                printf("Nome inválido!\n");
            }
            break;
        
        case 2:
            printf("Nome do responsável: \n");
            scanf(" %[^\n]", nome);
            if(busca_responsavel(responsavel, nome) == NULL){
                printf("Responsável não encontrado!\n");
                break;
            }
            else{
                excluir_responsavel(&responsavel, nome);
                printf("Responsável removido com sucesso!\n");
            }
            break;
            
        case 3:
            printf("Nome do responsavel: \n");
            scanf(" %[^\n]", nome_respondavel);
            Responsavel *ref = busca_responsavel(responsavel, nome_respondavel);

            if (ref == NULL)
            {
                printf("Responsável nao encontrado!\n");
                break;
            }
            else{
            int op;
            do{
            menu_crianca();
            scanf("%d", &op);

            switch(op){
                
                case 1:
                printf("Nome: \n");
                scanf(" %[^\n]", nome);
                if (verifica_nome(nome))
                {
                converte_caracteres(nome);
                printf("Idade: \n");
                while (scanf("%d", &idade) != 1 || !verifica_positivo(idade)) {
                printf("Entrada inválida. Por favor, digite um número inteiro positvo:\n");
                while (getchar() != '\n');
                }
                printf("Documento: \n");
                while (scanf("%d", &doc) != 1 || !verifica_positivo(doc)) {
                printf("Entrada inválida. Por favor, digite um número inteiro positvo:\n");
                while (getchar() != '\n');
                }
                int sucesso = 0;
                while(!sucesso){
                sucesso = 1;
                printf("Sexo: \n");
                scanf(" %[^\n]", sexo);
                if(!verifica_nome(sexo)){
                printf("Entrada inválida! Por favor, insira somente caracteres não especiais\n");
                sucesso = 0;
                }
                else{
                converte_caracteres(sexo);
                ref->crianca = adiciona_crianca(ref->crianca, nome, idade, doc, sexo);
                printf("Crianca adicionada com sucesso!\n");
                }
                }
                }
                else
                {
                printf("Nome invalido!\n");
                }
                break;

            case 2:
            printf("Digite o nome da criança: \n");
            scanf(" %[^\n]", nome);
            if(busca_crianca(ref->crianca, nome) == NULL){
                printf("Crianca nao encontrada!\n");
                break;
            }
            else{
            ref->crianca = remove_crianca(ref->crianca, nome);
            printf("Crianca removida com sucesso!\n");
            }
            break;

            case 3:
            printf("Nome: \n");
            scanf(" %[^\n]", nome);
            if(busca_crianca(ref->crianca, nome) == NULL){
                printf("Crianca nao encontrada!\n");
                break;
            }
            else{
            printf("Novo nome: \n");
            scanf(" %[^\n]", novo_nome);
            
            if (verifica_nome(novo_nome))
            {
                converte_caracteres(novo_nome);
                printf("Idade: \n");
                while (scanf("%d", &idade) != 1 || !verifica_positivo(idade)) {
                printf("Entrada inválida. Por favor, digite um número inteiro positvo:\n");
                while (getchar() != '\n');
                }
                printf("Documento: \n");
                while (scanf("%d", &doc) != 1 || !verifica_positivo(doc)) {
                printf("Entrada inválida. Por favor, digite um número inteiro positvo:\n");
                while (getchar() != '\n');
                }
                int sucesso = 0;
                while(!sucesso){
                sucesso = 1;
                printf("Sexo: \n");
                scanf(" %[^\n]", sexo);
                if(!verifica_nome(sexo)){
                printf("Entrada inválida! Por favor, insira somente caracteres não especiais\n");
                sucesso = 0;
                }
                else{
                converte_caracteres(sexo);
                ref->crianca = edita_crianca(ref->crianca, nome, novo_nome, idade, doc, sexo);
                printf("Edicao de crianca concluida!\n");
                }
                }  
            }
            else
            {
                printf("Nome invalido!\n");
            }
            }
            break;

            case 0:
            break;

            default:
            printf("Opcao invalida!\n");
            }
            } while(op != 0);
            }
            break;

        case 4:
            printf("Nome: \n");
            scanf(" %[^\n]", nome);
            Responsavel *p = busca_crianca_nas_lst(responsavel, nome);
            if(p == NULL){
                printf("Crianca nao esta cadastrada em nenhuma lista!\n");
                break;
            }
            Crianca *pont = busca_crianca(p->crianca, nome);
            printf("Essa crianca esta sob a responsabilidade de %s\n", p->nome);
            printf("Nome: %s\n", pont->nome);
            printf("Idade: %d\n", pont->idade);
            printf("Documento: %d\n", pont->doc);
            printf("Sexo: %s\n", pont->sexo);
            break;

        case 5:
            listar_responsavel_e_criancas(responsavel);
            break;

        case 6:
        
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
            printf("\nOpção inválida, escolha os valores de 1 à 6!\n");
            break;
        }
    }
    
    return 0;
}