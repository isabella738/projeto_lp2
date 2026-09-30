/*

O porgrama possui diferentes tipos de dados, que precisam passar por diversas verificacoes antes
de serem armazenados na maquina. Porem, trabalhar com diversas verificacoes e um processo demorado e 
propenso a erros. Este arquivo contem as funcoes que automatizam este processo. Elas solicitam a 
entrada do usuario ao mesmo tempo que verificam sua validade.

'ler_string' e 'ler_int' sao essas funcoes de proposito mais geral, fazendo verificacoes que toda 
string e todo inteiro, respectivamente, precisam passar independentemente de seu proposito. Quaisquer 
outras funcoes de entrada, como 'ler_codigo' sao derivadas destas duas, com verificacoes extras.

As funcoes retornam 1 caso tenha erro. Exemplo de uso:
    char string[x];
    while(ler_string(string, x));
    //chama a funcao ate que a string tenha um numero de caracteres dentro do esperado

    int n;
    while(ler_int(&n, 0, 10)); 
    //chama a funcao ate receber um numero de 0 a 10

Obs.: toda mensagem de erro deve terminanr com 'VOLTAR_APAGAR' e toda funcao deve terminar com um
printf(APAGAR_LINHA) antes do return 0, para apagar quaisquer mensagem de erro anteriores

*/

#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "auxiliary_functions.h"

int ler_string(char string[], int tam){
    printf("> ");
    char teste[tam+100]; fgets(teste, tam+100, stdin);

    remover_espacos(teste);

    if(strlen(teste) >= tam){
        printf("Voce estourou o limite de caracteres. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

    printf(APAGAR_LINHA);
    strcpy(string, teste);
    return 0;
}

int ler_int(int *inteiro, int min, int max){
    char teste[10]; while(ler_string(teste, 10));

    if(string_vazia(teste)){
        printf("Insira um numero ou 0 para cancelar a acao." VOLTAR_APAGAR);
        return 1;
    }

    if(!somente_numeros(teste)){
        printf("Deve conter somente numeros. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

    int n=0;
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
    char teste[TAM_CODIGO]; 
    if(ler_string(teste, TAM_CODIGO)) return 1;

    if(string_vazia(teste)){
        strcpy(string, teste);
        printf(APAGAR_LINHA);
        return 0;
    }

    if(strlen(teste) != TAM_CODIGO - 1){
        printf("Formato de codigo invalido. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }

    strcpy(string, teste);
    printf(APAGAR_LINHA);
    return 0;
}

int ler_senha(char senha[]) { 
    if(ler_string(senha, TAM_SENHA)) return 1;
    printf(APAGAR_LINHA);
    return 0;
}

int ler_novo_codigo(char codigo[]){
    if (ler_codigo(codigo)) return 1;
    if(string_vazia(codigo)) return 0;

    if(busca_codigo(livro, total_livros, codigo) >= 0){
        printf("Ja existe um livro cadastrado com este codigo. Tente Novamente." VOLTAR_APAGAR);
        return 1;
    }

    printf(APAGAR_LINHA);
    return 0;
}

int ler_livro(Livros *l){//return 1 = sucesso
    char titulo[TAM_STRING], autor[TAM_STRING], editora[TAM_STRING], codigo[TAM_CODIGO];
    int ano, quantidade, edicao;

    printf("\nTitulo do livro:\n"); while(ler_string(titulo, TAM_STRING)); 
    if(string_vazia(titulo)) return 0;

    printf("\nNome do autor:\n"); while(ler_string(autor, TAM_STRING)); 
    if(string_vazia(autor)) return 0;

    printf("\nEditora:\n"); while(ler_string(editora, TAM_STRING)); 
    if(string_vazia(editora)) return 0;

    printf("\nAno de publicacao:\n"); while(ler_int(&ano, 0, ANO_ATUAL));
    if(!ano) return 0;

    printf("\nEdicao:\n"); while(ler_int(&edicao, 0, 100));
    if(!edicao) return 0;

    printf("\nNumero de exemplares disponiveis:\n"); while(ler_int(&quantidade, 0, MAX_EXEMPLARES));

    printf("\nCodigo:\n"); while(ler_novo_codigo(codigo)); 
    if(string_vazia(codigo)) return 0;

    // salvar tudo
    strcpy(l->titulo, titulo);
    strcpy(l->autor, autor);
    strcpy(l->editora, editora);
    strcpy(l->codigo, codigo);
    l->ano = ano;
    l->edicao = edicao;
    l->quantidade = quantidade;

    return 1;
}

int ler_nova_senha(char senha[]){
    char s1[TAM_SENHA], s2[TAM_SENHA];

    while(ler_senha(s1));
    if(string_vazia(s1)) return 0;

    printf(VOLTAR_LINHA VOLTAR_APAGAR);
    printf("Confirme a senha:\n" APAGAR_LINHA);
    do{
        while(ler_senha(s2));
        if(string_vazia(s2)) return 0;

        if(strcmp(s1, s2)){
            printf("As senhas nao coincidem. Tente novamente ou aperte enter para voltars.\n");
            printf(VOLTAR_LINHA VOLTAR_APAGAR);
        }
        else break;
    }while(1);

    printf(APAGAR_LINHA);
    strcpy(senha, s1);
    return 0;
}

int ler_novo_nome(char nome[]){
    int repetido = 0;

    while(ler_string(nome, TAM_STRING));
    if(string_vazia(nome)) return 0;

    for(int i = 0; i < total_usuarios; i++) {
        if(strcmp(nome, usuario[i].nome)==0) {
            repetido = 1;
            break;
        }
    }
    if (repetido) {
        printf("Ja existe um usuario com esse nome. Tente novamente.");
        printf(VOLTAR_APAGAR);
        return 1;
    }
    return 0;
    printf(APAGAR_LINHA);
}