/*

Estas funcoes fazem pequenas verificacoes/acoes curtas e objetivas, somente para auxiliar.
Sao genericas e nao exibem mensagem de erro.

*/

#include <stdio.h>
#include <string.h>
#include "settings.h"

int sim(){
    printf("[s/n] ");
    char c; scanf(" %c", &c);
    while(getchar() != '\n'); 
    if(c == 'S' || c == 's') return 1;
    return 0;
}

int string_vazia(char string[]){
    if(strlen(string) > 0) 
        for(int i=0; i<strlen(string); i++){
            if(string[i] != ' ') return 0;
        }
    return 1;
}

int remover_espacos(char string[]){
    char novo[strlen(string)+1];
    int n = 0;

    if(string[strlen(string)-1] == '\n') string[strlen(string)-1] = '\0';

    for(int i=0; i<strlen(string); i++){
        if(string[i] == ' ' && (string[i+1] == ' ' || string[i+1] == '\0')) continue;
        else{ novo[n] = string[i]; n++;}
    }

    novo[n] = '\0';
    if(novo[0] == ' ') for(int i=0; i<n; i++) novo[i] = novo[i+1];

    strcpy(string, novo);
}

int somente_numeros(char string[]){
    for(int i=0; i<strlen(string); i++){
        if(string[i] < '0' || string[i] > '9') return 0;
    }
    return 1;
}

int letras_minusculas(char string[]){
    for(int i=0; string[i] != '\0'; i++){
        if(string[i] >= 'A' && string[i] <= 'Z'){
            string[i] += 'a' - 'A';
        }
    }
    return 0;
}

int strcmp_noCS(char string1[], char string2[]){
    char novo1[TAM_STRING], novo2[TAM_STRING];
    strcpy(novo1, string1);
    strcpy(novo2, string2);
    letras_minusculas(novo1); letras_minusculas(novo2);
    return strcmp(novo1, novo2);
}

int strstr_noCS(char string1[], char string2[]){
    char novo1[TAM_STRING], novo2[TAM_STRING];
    strcpy(novo1, string1);
    strcpy(novo2, string2);
    letras_minusculas(novo1); letras_minusculas(novo2);
    return strstr(novo1, novo2) != NULL;
}

int busca_codigo(Livros livro[], int tam, char codigo[]){
    for(int i=0; i<tam; i++){
        if(strcmp(livro[i].codigo, codigo) == 0) return i;
    }
    return -1;
}

void exibir_info_livro(Livros livro){
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Codigo: %s\n", livro.codigo);
    printf("Editora: %s\n", livro.editora);
    printf("Ano de publicacao: %d\n", livro.ano);
    printf("Edicao: %da\n", livro.edicao);
    printf("Exemplares disponiveis: %d\n", livro.quantidade);
}

void exibir_info_rapida(Livros livro){
    printf("(%s) %s - %s\n", livro.codigo, livro.titulo, livro.autor);
}

void imprimir_lista_livros(Livros vetor[], int max){
    for(int i=0; i<max; i++){
        exibir_info_rapida(vetor[i]);
    }
}

void swap_livros(Livros *livro1, Livros *livro2){
    Livros temp = *livro1;
    *livro1 = *livro2;
    *livro2 = temp;
}

int livro_duplicado(Livros l){
    for(int i=0; i<total_livros; i++){
        int correspondencias = 0;

        if(strcmp_noCS(l.titulo, livro[i].titulo) == 0) correspondencias++;
        if(strcmp_noCS(l.autor, livro[i].autor) == 0) correspondencias++;
        if(strcmp_noCS(l.editora, livro[i].editora) == 0) correspondencias++;
        if(l.edicao == livro[i].edicao) correspondencias++;

        if(correspondencias == 4) return i;
    }
    return -1;
}