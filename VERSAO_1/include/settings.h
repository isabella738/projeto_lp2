/*

Possui a definicao de macros, structs, e referencia as principais variaveis do programa.
Incluir 'settings.h' em um arquivo e o suficiente para que ele reconheca todos estes dados.

*/

#ifndef SETTINGS

#define SETTINGS
#include <time.h>

//Tamanhos de vetor
#define MAX_LIVROS 100
#define MAX_EXEMPLARES 100
#define MAX_EMP 5 //max de emprestimos por usuario
#define TAM_USUARIOS 100

//Tamanhos de strings (lembrar que é semrpe esse valor -1)
#define TAM_CODIGO 6
#define TAM_SENHA 8
#define TAM_STRING 100

//Outros
#define LIM_ATRASOS 5
#define ANO_ATUAL 2026
#define DIAS_EMPRESTIMO 30
#define CODIGO_PROP "12345" // codigo de acesso do proprietario dps mudar (ou nao k)
#define LIM_EMPRESTIMOS 5

//Edição de texto
#define VOLTAR_LINHA "\033[F\r"
#define APAGAR_LINHA "\033[2K\r"
#define VOLTAR_APAGAR "\033[F\r\033[2K\r"

typedef struct{
    char codigo[TAM_CODIGO];
    char titulo[TAM_STRING];
    char autor[TAM_STRING];
    char editora[TAM_STRING];
    int ano;
    int quantidade;
    int qtdDisponiveis;
    int edicao;
}Livros;

typedef struct{
    char codigo[TAM_CODIGO];
    int prazo;
    int atrasado; //0 ou 1
}Emprestimos;

typedef struct {
    char nome[TAM_STRING];
    char senha[TAM_SENHA];
    Emprestimos emprestimo[MAX_EMP];
    int qtd_emp;
    int suspenso;//0 ou 1. usuario fica bloqueado de fazer pegar novos livros ate quitar seus atrasos
}Usuarios;

extern Livros livro[MAX_LIVROS];
extern int total_livros;
extern Usuarios usuario[TAM_USUARIOS];
extern int total_usuarios;
extern int user_ativo;
extern Usuarios *user;
extern time_t dia_de_hoje, ultimo_dia;

#endif