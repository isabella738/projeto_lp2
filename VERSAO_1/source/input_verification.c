/*
Muitas das entradas no programa precisam passar pelas mesmas verificações. Por exemplo, nenhuma
string pode ser vazia, assim como todo número deve pertencer a um intervalo. Por isso foram
criadas funções para otimizar este processo, "ler_string" e "ler_int". Elas leem a entrada ao mesmo 
tempo que verificam se sao validas e substituem fgets e scanf ao longo do codigo.

Exemplo de uso:
    char string[x];
    while(ler_string(string, x));
    //chama a funcao ate que a string tenha um numero de caracteres dentro do esperado

    int n;
    while(ler_int(&n, 0, 10)); 
    //chama a funcao ate receber um numero de 0 a 10

Como o programa de gerenciamento de biblioteca possui tipos de entrada especificos para seu contexto,
como código e nome de livro, existem outras funcoes, derivadas de ler_string, proprias para a leitura
destes dados com suas respectivas verificacoes.
Desta forma, todas as funcoes de entrada do tipo "ler_'input'" seguem o mesmo formato visto acima
*/

#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "auxiliary_functions.h"

extern Livros livro[];
extern int total_livros;

int ler_string(char string[], int tam){
    printf("> ");
    char teste[tam+100]; fgets(teste, tam, stdin);

    remover_espacos(teste);

    if(strlen(teste) > tam){
        printf("Voce estourou o limite de caracteres. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

    printf(APAGAR_LINHA);
    strcpy(string, teste);
    return 0;
}

int ler_int(int *inteiro, int min, int max){
    printf("> ");

    char teste[5]; while(ler_string(teste, 5));

    if(!somente_numeros(teste)){
        printf("Deve conter somente numeros. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

    int n;
    for(int i=0; i<strlen(teste); i++){
        n *= 10; n += teste[i] - '0';
    }

    if(n < min || n > max){
        printf("Numero invalido. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

    printf(APAGAR_LINHA);
    (*inteiro) = n;
    return 0;
}

int ler_codigo(char string[]){
    char teste[100]; ler_string(teste, 5);

    if(strlen(teste) < 5){
        printf("Formato de codigo invalido. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

}

int ler_novo_codigo(char codigo[]){
    ler_codigo(codigo);
    if(string_vazia(codigo)) return 0;

    if(busca_codigo(livro, total_livros, codigo) > 0){
        printf("Ja existe um livro cadastrado com este codigo. Tente Novamente." VOLTAR_APAGAR);
        return 1;
    }

    return 0;
}

int ler_livro(Livros *livro){
    char titulo[TAM_TITULO], autor[TAM_AUTOR], editora[TAM_EDITORA], codigo[TAM_CODIGO];
    int ano, quantidade, edicao;

    printf("Titulo do livro:\n"); while(ler_string(titulo, TAM_TITULO)); 
    if(string_vazia(titulo)) return 0;

    printf("Nome do autor:\n"); while(ler_string(autor, TAM_AUTOR)); 
    if(string_vazia(autor)) return 0;

    printf("Editora:\n"); while(ler_string(editora, TAM_EDITORA)); 
    if(string_vazia(editora)) return 0;

    printf("Ano de publicacao:\n"); while(ler_int(&ano, 0, ANO_ATUAL));
    if(!ano) return 0;

    printf("Edicao:\n"); while(ler_int(&edicao, 0, 100));
    if(!edicao) return 0;

    printf("Numero de exemplares disponiveis:\n"); while(ler_int(&quantidade, 0, MAX_EXEMPLARES));
    if(!quantidade) return 0;

    printf("Codigo:\n"); while(ler_string(codigo, TAM_CODIGO)); 
    if(string_vazia(codigo)) return 0;
}