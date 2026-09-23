/*

Como o programa de gerenciamento de biblioteca possui tipos de entrada especificos para seu contexto,
como código e nome de livro, existem outras funcoes, derivadas de ler_string, proprias para a leitura
destes dados com suas respectivas verificacoes.
Desta forma, todas as funcoes de entrada do tipo "ler_'input'" seguem o mesmo formato visto acima


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
    char teste[tam+100]; fgets(teste, tam+1, stdin);

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
    printf("> ");

    char teste[5]; while(ler_string(teste, 20));

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
    char teste[5]; ler_string(teste, TAM_CODIGO);

    if(strlen(teste) != TAM_CODIGO){
        printf("Formato de codigo invalido. Tente novamente." VOLTAR_APAGAR);
        return 1;
    }
    
    strcpy(string, teste);
    printf(APAGAR_LINHA);
    return 0;
}

int ler_senha(char senha[]) { // essa aqui ficou bem parecida com ler_codigo, talvez de p fazer uma unica mais generica?
    ler_string(senha, TAM_SENHA);

    if(strlen(senha) != TAM_SENHA){
        printf("A senha deve conter exatamente %d caracteres. Tente novamente." VOLTAR_APAGAR, TAM_SENHA);
        return 1;
    }

    printf(APAGAR_LINHA);
    return 0;
}

int ler_novo_codigo(char codigo[]){
    ler_codigo(codigo);
    if(string_vazia(codigo)) return 0;

    if(busca_codigo(livro, total_livros, codigo) >= 0){
        printf("Ja existe um livro cadastrado com este codigo. Tente Novamente." VOLTAR_APAGAR);
        return 1;
    }

    printf(APAGAR_LINHA);
    return 0;
}

int ler_livro(Livros *livro){
    char titulo[TAM_STRING], autor[TAM_STRING], editora[TAM_STRING], codigo[TAM_CODIGO];
    int ano, quantidade, edicao;

    printf("Titulo do livro:\n"); while(ler_string(titulo, TAM_STRING)); 
    if(string_vazia(titulo)) return 0;

    printf("Nome do autor:\n"); while(ler_string(autor, TAM_STRING)); 
    if(string_vazia(autor)) return 0;

    printf("Editora:\n"); while(ler_string(editora, TAM_STRING)); 
    if(string_vazia(editora)) return 0;

    printf("Ano de publicacao:\n"); while(ler_int(&ano, 0, ANO_ATUAL));
    if(!ano) return 0;

    printf("Edicao:\n"); while(ler_int(&edicao, 0, 100));
    if(!edicao) return 0;

    printf("Numero de exemplares disponiveis:\n"); while(ler_int(&quantidade, 0, MAX_EXEMPLARES));
    if(!quantidade) return 0;

    printf("Codigo:\n"); while(ler_novo_codigo(codigo)); 
    if(string_vazia(codigo)) return 0;

    return 1;
}