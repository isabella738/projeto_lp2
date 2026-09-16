#ifndef SETTINGS

#define SETTINGS
#define MAX_LIVROS 100
#define MAX_EXEMPLARES 100
#define TAM_CODIGO 5
#define TAM_TITULO 100
#define TAM_AUTOR 100
#define TAM_EDITORA 100
#define ANO_ATUAL 2026
#define VOLTAR_LINHA "\033[F\r"
#define APAGAR_LINHA "\033[2K\r"
#define VOLTAR_APAGAR "\033[F\r\033[2K\r"

typedef struct{
    char codigo[TAM_CODIGO];
    char titulo[TAM_TITULO];
    char autor[TAM_AUTOR];
    char editora[TAM_EDITORA];//
    int ano;
    int quantidade;
    int edicao;//
}Livros;

#endif