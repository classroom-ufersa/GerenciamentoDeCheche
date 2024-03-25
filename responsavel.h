typedef struct responsavel Responsavel;

typedef struct responsavel
{
    char nome[80];
    int telefone;
    /*aqui colocar uma lista encadeada de crianças*/
    struct responsavel *proximo;

}Responsavel;

void adicionar_responsavel(char nome[80], int telefone, Responsavel **responsavel);
void excluir_responsavel(Responsavel **responsavel, char nome[80]);
void listar_responsavel_e_criancas(Responsavel *responsavel);