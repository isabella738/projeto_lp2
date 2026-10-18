#include "settings.h"

void resetar_buffer();
void pausa();
void limpar_tela();//limpa a tela do cursor pra cima
int sim();//imprime '[s/n] ' e espera um caractere
/*
    1: sem livros
    2: sem usuarios
    3: user == NULL
    4: usuario suspenso
    5: qtd max livros (temp)
    6: qtd max usuarios (temp)
*/
int erro(int i);

int string_vazia(char texto[]);
void tirar_enter(char string[]);
int remover_espacos(char texto[]);
int somente_numeros(char texto[]);
int letras_minusculas(char string[]);//aviso: a funcao altera diretamente a string
int strcmp_noCS(char string1[], char string2[]);//strcmp sem Case Sensitive. Retorna 0 (iguais) ou 1 (diferentes)
int strstr_noCS(char string1[], char string2[], int margem);//strstr sem Case Sentsitive. Retorna 1 se string2 for substring de string1. Aceita margem de erro

void exibir_info_livro(Livros livro);//imprime todas as informacoes do livro
void exibir_info_rapida(Livros livro);//exibe codigo, titulo e autor somente
void imprimir_lista_livros(Livros vetor[], int max);//imprime qualquer vetor do tipo Livros com informacoes rapidas
void imprimir_info_usuario(Usuarios u);//imprime nome, qntd de livros emprestados e de atrasados

void apagar_livro(Livros lista[], int x, int *tam);//apaga o livro x de uma lista do tipo Livros
void apagar_usuario(Usuarios users[], int x, int *tam);//apaga o usuario x de uma lista do tipo Usuarios
void swap_livros(Livros *livro1, Livros *livro2);

int livro_duplicado(Livros l);//verifica se existe um ja existe um livro com o mesmo titulo, autor e editora de 'l' cadastrado no sistema
void passagem_de_tempo(); // calcula o tempo dos emprestimos
int qtd_atrasos(Usuarios u); //retorna a quantidade de livros atrasados do usuario u
int busca_codigo(Livros livro[], int tam, char codigo[]);//retorna a posicao no array do livro dado pelo codigo
int busca_rapida();//le um codigo, verifica se existe, limpa a tela e exibe informações integrais do livro

void carregar_dados();//exibe uma mensagem se os dados nao foram carregados, mas nao bloqueia o sistema
int salvar_dados();//retorna 0 somente se os usuarios ou livros nao foram salvos