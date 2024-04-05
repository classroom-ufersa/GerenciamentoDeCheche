# GerenciamentoDeCheche
Esse projeto tem por finalidade criar um sistema, utilizando programação em C, para gerenciamento de uma creche em que responsáveis, crianças e seus dados correspondentes serão manipulados.
## Requisitos
Menu com as seguintes opções deverá ser apresentado:

- Adicionar responsável
- Remover responsável
- Adicionar criança
- Remover criança
- Editar informação da criança
- Buscar criança por nome
- Listar responsáveis e suas crianças
- Sair

  Além disso, a cada execução do programa, os dados devem ser carregados em um arquivo de texto, armazenados em ordem alfabética. O arquivo de texto será atualizado para refletir o estado
  atual dos dados em virtude da adição ou remoção.
  ## Variáveis e seus atributos
  No caso desse projeto, escolheu-se usar listas encadeadas simples para a manipulação dos dados tanto dos responsáveis como das crianças. As variáveis do programa foram declaradas da seguinte forma:
  ```c
  struct crianca{
    char nome[50];
    int idade;
    int doc;
    char sexo[10];
    struct crianca *proximo;
  };
  typedef struct crianca Crianca;
  ```
```c

typedef struct responsavel Responsavel;

typedef struct responsavel
{
    char nome[80];
    int telefone;
    Crianca *crianca;
    struct responsavel *proximo;

}Responsavel;
```
Como cada responsável irá cuidar de várias crianças, foi declarado um ponteiro para a lista das crianças dentro da struct responsavel.
## Menu
Este é o menu principal do programa
```c
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
```
## Menu criança
### Menu crianca
Menu que mostra as opções de manipulação dos dados das crianças dos responsáveis
```c
void menu_crianca(){
    printf("== MENU ==\n");
    printf("1 - Adicionar crianca\n");
    printf("2 - Remover crianca\n");
    printf("3 - Edita os dados da crianca\n");
    printf("0 - SAIR\n");
}
```
## Funções de manipulação de dados 
### Adicionar responsavel
```c
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
```
Essa função recebe como parâmetro o nome, telefone e um ponteiro duplo para a struct do responsavel,  que corresponde a lista encadeada dos responsáveis. Ela aloca dinamicamente uma variável resp do tipo Responsavel * para armazenar os novos dados. Em seguida, o programa vê se a lista está vazia e, caso sim, somente é atualizado com as informações do resp o conteúdo de responsavel. Caso contrário, um ponteiro para o último elemento da lista é declarado e para garantir que os novos dados adicionados não sobreescrevam um nó já existente, finalizando o procedimento.
### Excluir responsavel
```c
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
```
A um ponteiro duplo para a lista de responsavel e o nome daquele que se deseja remover são passados como parâmetro da função. Ela funciona da seguinte maneira:
#### Passo 1
Verifica se a lista está vazia. Se sim, a função retorna direto para main, pois não há nada para retirar.
#### Passo 2
Caso seja não para a lista vazia, procura-se pelo o responsável que irá ser excluido usando um ponteiro para um nó da lista e um laço de repetição até responsavel == NULL, onde a lista termina, e uma função condicional if para comparar nome por nome.
#### Passo 3
Se o elemento desejado é o primeiro, apenas atribui a ele o nó seguinte. Se ele estiver no meio da lista, o ponteiro para o próximo do elemento anterior (que no caso é o próprio nó que se deseja excluir) recebe os dados do nó seguinte, para depois liberar da memória o nó excluido.
### Menu crianca
Menu que mostra as opções de manipulação dos dados das crianças dos responsáveis
```c
void menu_crianca(){
    printf("== MENU ==\n");
    printf("1 - Adicionar crianca\n");
    printf("2 - Remover crianca\n");
    printf("3 - Edita os dados da crianca\n");
    printf("0 - SAIR\n");
}
```
### Adicionar criança
```c
Crianca *adiciona_crianca(Crianca *c, char nome[100], int idade, int doc, char sexo[10]){
    Crianca *novo = (Crianca*) malloc(sizeof(Crianca));
    if(novo == NULL){
        printf("Erro na alocacao de crianca!\n");
        exit(1);
    }
    strcpy(novo->nome, nome);
    novo->idade = idade;
    novo->doc = doc;
    strcpy(novo->sexo, sexo);
    novo->proximo = c;
    
    return novo;
}
```
A função recebe os novos dados e declara um ponteiro para um novo nó, onde serão colocados. Após os procedimentos, ela retorna o novo nó.
### Remove criança
```c
Crianca *remove_crianca(Crianca *c, char nome[100]){
    Crianca *ant = NULL;
    Crianca *p = c;
    
    while(p != NULL && strcmp(p->nome, nome) != 0){
        ant = p;
        p = p->proximo;
    }
    
    if(ant == NULL){
        c = p->proximo;
    }
    else{
        ant->proximo = p->proximo;
    }
    
    free(p);
    return c;

}
```
Esta função remove uma criança específica de uma lista endadeada. Para isso, recebe como parâmetro a lista e o nome do indivíduo que será removido. Seu funcionamento é igual ao da função de excluir responsavel.
### Edita crianca
```c
Crianca *edita_crianca(Crianca *c, char nome[100], char Nnome[100], int idade, int doc, char sexo[10]){
    Crianca *p = busca_crianca(c, nome);

    if(p == NULL){
        printf("Nome nao encontrado!\n");
        return c;
    }
    else{
        strcpy(p->nome, Nnome);
        p->idade = idade;
        p->doc = doc;
        strcpy(p->sexo, sexo);
    }
    
    return c;
}
```
Função tem como objetivo atualizar os dados de uma criança na lista. Dessa forma, um ponteiro recebe o nó do sujeito procurado por meio da função de busca_crianca. Se ele for igual a NULL, significa que a criança não foi encontrado, e retorna a lista do jeito que está. Caso contrário, sobreescreve os dados com os novos. 
## Funções relacionadas ao arquivo.txt
Essas funções serão responsáveis pela transferência de dados da lista para o arquivo.txt e vice-versa. A declaração deste está explicitada a seguir:
```c
FILE *responsaveis_e_criancas = fopen("responsaveisEsuasCriancas.txt", "r");
    if (responsaveis_e_criancas == NULL)
    {
        printf("Erro ao abrir arquivo!");
        exit(1);
    }
```
### Ler do arquivo
```c
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
```
Essa função em linguagem C tem o objetivo de ler dados de um arquivo, que contém informações sobre responsáveis e suas crianças associadas. Como parâmetros, tem-se um ponteiro para o arquivo do qual os dados serão lidos e um ponteiro duplo para a lista que irá recebê-los. As variáveis locais são:
- char linha[1000], para armazenar cada linha do arquivo
- char nome_responsavel[100], um array de caracteres usado para armazenar o nome do responsável.
- int telefone_responsavel,  uma variável inteira para armazenar o número de telefone do responsável.
- Responsavel *ultimo, um ponteiro para o último responsável lido do arquivo, inicializado como NULL.
  Ela funciona da seguinte forma:
  #### Passo 1
   O loop principal é responsável por ler o arquivo linha por linha até o final dele. A função fgets() é usada para ler cada linha do arquivo. 
### Escrever para o arquivo
```c
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
```




