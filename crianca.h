typedef struct crianca Crianca;


void menu_crianca(void);

Crianca *cria_crianca(void);

Crianca *adiciona_crianca(Crianca *c, char nome[50], int idade, int doc, char sexo[10]);

Crianca *edita_crianca(Crianca *c, char nome[50], char Nnome[50], int idade, int doc, char sexo[10]);

Crianca *remove_crianca(Crianca *c, char nome[100]);

Crianca *busca_crianca(Crianca *c, char nome[100]);

int vazia(Crianca *c);

void libera_crianca(Crianca *c);

void imprime_dados(Crianca *c);