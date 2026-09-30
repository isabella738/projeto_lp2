//Declaracao das principais variaveis do programa

#include "settings.h"

Livros livro[MAX_LIVROS];

int total_livros = 0;

//
Usuarios usuario[TAM_USUARIOS];

int total_usuarios = 0;

int user_ativo = -1;

Usuarios *user; //ponteiro para o usuario logado atualmente
/*
    Esse ponteiro serve principalmente para encurtar o nome da estrutura durante o codigo.
    Visualmente, é muito melhor user->nome do que user[posicao].nome, ainda mais se for acessar
    uma variavel dentro de outra estrutura, tipo usuario[posicao].emprestimo[x].[...]
*/