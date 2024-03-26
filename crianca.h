typedef struct crianca Crianca;
typedef enum sexo Sexo;

void menu_crianca(void);

Crianca *cria_crianca(void);

Crianca *adiciona_crianca(Crianca *c, char nome[50], int idade, int doc, int r);

Crianca *edita_crianca(Crianca *c, char nome[50], char Nnome[50], int idade, int doc, int r);

Crianca *remove_crianca(Crianca *c, char nome[100]);

Crianca *busca_crianca(Crianca *c, char nome[100]);