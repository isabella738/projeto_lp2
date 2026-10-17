#include "settings.h"

int string_vazia(char texto[]);

int sim();//imprime [s/n] e espera um caractere

int remover_espacos(char texto[]);//remove espacos e o enter do fgets 

int somente_numeros(char texto[]);

int letras_minusculas(char string[]);//aviso: a funcao altera diretamente a string

int strcmp_noCS(char string1[], char string2[]);//strcmp sem Case Sensitive. Retorna 0 (iguais) ou 1 (diferentes)

int strstr_noCS(char string1[], char string2[], int margem);//strstr sem Case Sentsitive. Retorna 1 se string2 for substring de string1. Aceita margem de erro

int busca_codigo(Livros livro[], int tam, char codigo[]);//retorna a posicao no array do livro dado pelo codigo

void exibir_info_livro(Livros livro);//imprime todas as informacoes do livro

void exibir_info_rapida(Livros livro);//exibe codigo, titulo e autor somente

void imprimir_lista_livros(Livros vetor[], int max);//imprime qualquer vetor do tipo Livros com informacoes rapidas

void swap_livros(Livros *livro1, Livros *livro2);

int livro_duplicado(Livros l);//verifica se existe um ja existe um livro com o mesmo titulo, autor e editora de 'l' cadastrado no sistema

void apagar_livro(Livros lista[], int x, int *tam);//apaga o livro x de uma lista do tipo Livros

void apagar_usuario(Usuarios users[], int x, int *tam);//apaga o usuario x de uma lista do tipo Usuarios

void imprimir_info_usuario(Usuarios u);//imprime nome, qntd de livros emprestados e de atrasados

void limpar_tela();//limpa a tela do cursor pra cima

int erro(int i);//1:sem livros; 2:sem usuarios; 3:problema no ponteiro user; 4:usuario suspenso

void passagem_de_tempo();

int qtd_atrasos(Usuarios u);

void pausa();

int busca_rapida();//le um codigo, verifica se existe, limpa a tela e exibe informações integrais do livro

void carregar_dados();

int salvar_dados();//retorna 0 somente se os usuarios ou livros nao foram salvos