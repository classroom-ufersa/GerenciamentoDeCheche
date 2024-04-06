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
Essa função recebe como parâmetro o nome, telefone e um ponteiro duplo para a struct do responsavel,  que corresponde a lista encadeada dos responsáveis. Ela aloca dinamicamente uma variável resp do tipo Responsavel * para armazenar os novos dados. Em seguida, o programa vê se a lista está vazia e, caso sim, somente é atualizado com as informações do resp o conteúdo de responsavel. Caso contrário, o novo nó será adicionado no final da lista.
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
A função recebe os novos dados e declara um ponteiro para um novo nó, onde serão colocados. Após os procedimentos, ela retorna o novo nó, que se tornará o primeiro da lista.
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
   O loop principal é responsável por ler o arquivo linha por linha até o final dele. A função fgets() é usada para ler cada linha do arquivo. Enquanto ainda houver linhas para ler, ou seja, fgets() != NULL, o código continuará sendo executado.
  #### Passo 2
  Verifica se o que será lido faz parte do conjunto de dados do responsável ou da criança. No primeiro caso, a próxima linha do arquivo é lida, observando se ela está vazia (nesse caso, fgets() retorna NULL, e não há dados para ler) ou se está com os dois atributos esperados para o responsável (nome e telefone). Se qualquer uma das condições se concretizar, a execução da função é interrompida com exit(1). No segundo, olha se os dados do responsável pela aquelas crianças foram corretamente lidos, para depois iniciar um outro loop para ler as informações de todas as crianças na lista encadeada. 
  #### Passo 3
  Depois de passar das condições sem problemas, inicia-se a etapa de transferência de dados. A função sscanf() irá ler os dados do arquivo e armazená-los nas variáveis nome_responsavel e telefone_responsavel, que serão úteis para ir adicionando os responsáveis um por um por meio da função adicionar responsavel. Logo em seguida, o ponteiro para o último elemento é atualizado, em decorrência dessa adição. Na parte das crianças, o procedimento é o mesmo.
  #### Passo 4
   ftell e fseek trabalham em conjunto para garantir que o arquivo seja lido por completo. O código usa ftell() para obter a posição atual no arquivo antes de ler informações sobre crianças. Isso é usado para retornar à posição atual no arquivo caso seja necessário ler mais informações sobre responsáveis depois de ler informações sobre crianças. fseek() então procura pela posição informada pela outra função e retorna para ela, possibilitando uma leitura organizada e eficiente do código.
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
A função escrever_para_arquivo tem como objetivo escrever os dados de uma lista de responsáveis e suas respectivas crianças em um arquivo. Ela recebe como parâmetros um ponteiro para o arquivo onde os dados serão escritos e um ponteiro para p primeiro elemento da lista encadeada os responsáveis. 
#### Passo 1
Inicializa-se um ponteiro responsavel_atual para percorrer a lista de responsáveis, começando pelo primeiro responsável. Depois, inicia-se um loop while para percorrer a lista de responsáveis. Este loop continua enquanto o ponteiro responsavel_atual não for nulo, ou seja, enquanto houver responsáveis na lista. 
#### Passo 2
Para cada responsável, escreve no arquivo a indicação de início de uma nova seção de responsável ("Responsavel:\n") e em seguida escreve o nome e telefone do responsável utilizando a função fprintf. 
#### Passo 3
Verifica se o responsável possui crianças associadas. Se sim, escreve no arquivo a indicação de início de uma nova seção de crianças ("Criancas:\n"). Inicia um loop interno para percorrer a lista de crianças associadas ao responsável atual (crianca_atual), escrevendo no arquivo o nome, idade, documento e sexo utilizando novamente a função fprintf. Após isso, o ponteiro de crianca_atual é atualizada para apontar para a próxima criança na lista. Isso vai se repetindo até que todos os dados das crianças referentes ao responsavel_atual sejam transferidos para o arquivo com êxito.
#### Passo 4
Após percorrer todas as crianças associadas ao responsável atual, atualiza o ponteiro responsavel_atual para apontar para o próximo responsável na lista. O loop externo continua até percorrer todos os responsáveis da lista. 
## Função de ordenação
```c
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
```
Função cuja finalidade é ordenar os responsáveis e as crianças em ordem alfabética. A seguir, está escrita uma explicação sobre sua funcionalidade:
#### Passo 1
Verificar se a lista está vazia ou se possui apenas um elemento. Caso sim, a função é encerrada, pois não há o que fazer.
#### Passo 2
O algoritmo executa repetidamente o processo de ordenação até que nenhuma troca seja necessária. Inicialmente, a variável trocou é definida como 0 para indicar que nenhuma troca ocorreu.
#### Passo 3
São definidos três ponteiros: atual, anterior e proximo. O ponteiro atual aponta para o primeiro elemento da lista de responsáveis, enquanto anterior é inicializado como NULL. O ponteiro proximo aponta para o próximo elemento após o atual.
#### Passo 4
O loop while percorre a lista de responsáveis e compara os nomes dos responsáveis adjacentes. O loop continua até que não haja mais elementos para comparar.
#### Passo 5
Dentro do loop while, é feita uma comparação dos nomes dos responsáveis apontados pelos ponteiros atual e proximo. Se o nome do responsável atual for maior (em ordem alfabética) do que o nome do responsável seguinte, ocorre a troca de posição entre eles. O ponteiro proximo do responsável atual é ajustado para apontar para o elemento seguinte ao próximo elemento, enquanto o ponteiro proximo do responsável seguinte é ajustado para apontar para o responsável atual. 

A partir daí, se anterior permanecer NULL, significa que o elemento maior que foi trocado era o primeiro elemento da lista. Por isso, o ponteiro para o primeiro elemento *lista_responsavel irá apontar agora para proximo. Para o caso em que o nó maior estiver no meio da lista, o programa faz o ponteiro proximo do elemento anterior ao responsavel_atual apontar agora para o proximo, efetuando com sucesso a troca dos elementos sem desmantelar o endadeamento da lista. 
#### Passo 6
Após a troca de posição, os ponteiros anterior, atual e proximo são atualizados para avançar na lista e continuar comparando os elementos restantes.
#### Passo 7
Após completar uma passagem pela lista e não ter realizado nenhuma troca (ou seja, trocou permanece como 0), o loop do-while termina, indicando que a lista está ordenada corretamente. Caso contrário, o loop continua até que o valor seja esse.
#### Passo 8
Depois de ordenar os responsáveis, é hora das crianças. Basicamente, o procedimento é o mesmo, com a diferença de que, após ordenar uma lista de um, deve-se passar para o próximo responsável para ordenar a lista dele, tarefa essa delegada para o loop maior while, em que o ponteiro do responsavel atual é ajustado para a apontar para o proximo nó e ocorre a verificação de fim de lista 
(atual_responsavel != NULL).
## Outras Funções
### Verificar nome
```c
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
```
Função para verificar se o nome digitado é adequado. No caso, ele será válido quando não possuir números ou caracteres especiais.
### Converte caracteres
```c
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
```
Função que converte os caracteres do nome do responsavel ou da criança de maiúsculo para minúsculo.
### Listar responsáveis e crianças
```c
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
```
Função que percorre uma lista de responsáveis, imprimindo seus dados e a quantidade de crianças sob seu cuidado, o que faz utilizando de dois ponteiros e dois loops.
## Funções de Busca
```c
Responsavel *busca_responsavel(Responsavel *r, char nome[80]){
    Responsavel *p;
    for(p = r; p != NULL; p = p->proximo){
        if(strcmp(p->nome, nome) == 0){
            return p;
        }
    }
    return NULL;
}
```
Função que percorre toda a lista de responsáveis em busca daquele cujo nome corresponde ao passado como parâmetro. Se encontrar, retorna o nó em que está, caso contrário, retorna NULL, indicando falha na busca.
```c
Crianca *busca_crianca(Crianca *c, char nome[100]){
    Crianca *p;
    for(p = c; p != NULL; p = p->proximo){
        if(strcmp(p->nome, nome) == 0){
            return p;
        }
    }
    return NULL;
}
```
Função que percorre toda a lista de crianças em busca daquela cujo nome corresponde ao passado como parâmetro. Funciona da mesma forma que o código anterior.
```c
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
```
Tem como objetivo principal retornar o responsável por uma determinada criança cujo nome é especificado no parâmetro. A função percorre cada lista de crianças dos responsáveis a procura da criança certa. Se encontrar, retorna o nó do responsável, caso contrário, retorna NULL.  











