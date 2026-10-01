#include "settings.h"

int ler_senha(char senha[]);

int ler_string(char texto[], int tam);

int ler_int(int *inteiro, int min, int max);

int ler_codigo(char texto[]);

int ler_codigo_existente(char string[], int *i);//junta as funcoes 'ler codigo' e 'busca codigo'

int ler_novo_codigo(char codigo[]);

int ler_livro(Livros *livro);

int ler_nova_senha(char senha[]);

int ler_novo_nome(char nome[]);