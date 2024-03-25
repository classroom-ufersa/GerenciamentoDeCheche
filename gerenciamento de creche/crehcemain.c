#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "responsavel.h"

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
    
    /*função passa_para_a_lista*/

    while (1)
    {
        int opcao = 0;
        
        menu();
        
        scanf("%d", &opcao);

        char nome1[80];
        int telefone;

        char nome2;
        
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
            scanf(" %[^\n]79", nome2);
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
            /*função ordena*/
            /*função passa_para_o_arquivo*/
            return 0;
            break;
        
        default:
            printf("\nOpção inválida, escolha os valores de 1 à 8!\n");
            break;
        }
    }
    
    

    return 0;
}