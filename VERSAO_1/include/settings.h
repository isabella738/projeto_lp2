/*

Possui a definicao de macros, structs, e referencia as principais variaveis do programa.
Incluir 'settings.h' em um arquivo e o suficiente para que ele reconheca todos estes dados.

*/

#ifndef SETTINGS

#define SETTINGS

#define MAX_LIVROS 100
#define MAX_EXEMPLARES 100
#define TAM_USUARIOS 100

#define TAM_CODIGO 5
#define TAM_SENHA 8
#define TAM_STRING 100
#define ANO_ATUAL 2026

#define VOLTAR_LINHA "\033[F\r"
#define APAGAR_LINHA "\033[2K\r"
#define VOLTAR_APAGAR "\033[F\r\033[2K\r"
#define CODIGO_PROP "12345" // codigo de acesso do proprietario dps mudar (ou nao k)

typedef struct{
    char codigo[TAM_CODIGO];
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int ano;
    int quantidade;
    int edicao;//
}Livros;

typedef struct {
    char nome[TAM_STRING];
    char senha[TAM_SENHA];
}Usuarios;

extern Livros livro[MAX_LIVROS];
extern int total_livros;

extern Usuarios usuario[TAM_USUARIOS];
extern int total_usuarios;


#endif