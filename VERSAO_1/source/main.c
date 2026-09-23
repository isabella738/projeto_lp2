/*

As funcoes retornam 1 caso o usuario queira fazer um novo processo dentro da mesma funcao.
Exemplo de uso:
    while(cadastro());

*/

#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "input_verification.h"
#include "auxiliary_functions.h"
#include "main.h"

int menu (int posicao) {

}

int cadastro_usuario() {
    printf("**=======================**\n");
    printf("    CADASTRO DE USUARIO    \n");
    printf("**=======================**\n");

    do {
        char nome[TAM_AUTOR], senha[TAM_SENHA];

        printf("Digite seu nome:\n"); 
        while(ler_string(nome, TAM_AUTOR));
        if(string_vazia(nome)) return 0;

        printf("Crie uma senha de (%d caracteres):\n", TAM_SENHA); // funcionava ai bugou aaa
        while(ler_senha(senha));
        if(string_vazia(senha)) return 0;

        strcpy(usuario[total_usuarios].nome, nome);
        strcpy(usuario[total_usuarios].senha, senha);
        total_usuarios++;

        printf("Cadastrar outro usuario?\n");
    } while(sim());

    entrada_usuario();

    return 0;
}

int entrada_usuario() {
    printf("Entrar como:\n[1] Proprietário\n[2] Usuario\n[3] Cadastrar novo usuario\n[4] Sair\n");
    int resposta;
    while(ler_int(&resposta, 1, 4));

    if(resposta == 1) { // proprietario
        char prop[TAM_CODIGO];
        do {
            printf("Digite o codigo de acesso:\n");
            while(ler_codigo(prop));

            if(strcmp(prop, CODIGO_PROP) == 0) {
                // alguma coisa que seja so do proprietario alem da de cadastrar livros
                return 1;
            }

            printf("Codigo invalido, deseja tentar novamente?\n");
        } while (sim());

    } else if (resposta == 2) { 
        char nome[TAM_AUTOR], senha[TAM_SENHA];

        printf("Digite seu nome (ou deixe vazio para cancelar):\n"); 
        while(ler_string(nome, TAM_AUTOR));
        if(string_vazia(nome)) return 0;

        int posicao = -1;

        for(int i = 0; i < total_usuarios; i++) {
            if(strcmp(nome, usuario[i].nome) == 0) {
                posicao = i;
                break;
            }
        }

        if(posicao == -1) {
            printf("Usuario nao existe\n" VOLTAR_APAGAR);
            return 0;
        }

        int tent = 0;
        while(tent < 3) {
        printf("Digite sua senha (ou deixe vazio para cancelar):\n");
        while(ler_senha(senha));
        if(string_vazia(senha)) return 0;

        if(strcmp(senha, usuario[posicao].senha) == 0) {
            printf("Seja bem vindo(a) %s\n", usuario[posicao].nome);
            menu(posicao);
            return 1;
        }

        tent++;
        printf("Senha incorreta. Tentativas restantes: %d\n", 3 - tent);
    }

    printf("Numero maximo de tentativas excedido.\n");
    return 0;

    } else if (resposta == 3) {
        cadastro_usuario();
    } else {
        printf("Saindo do Sistema...");
        return 0;
    }

}

int cadastro(){ // so para o proprietario
    printf("**=======================**\n");
    printf("     CADASTRO DE LIVROS    \n");
    printf("**=======================**\n");
    do {
    printf("Digite as informacões sobre o novo livro:\n");
    ler_livro(&livro[total_livros]);
    total_livros++;
    printf("Fazer o cadastro de um novo livro?\n");
    } while (sim());

    return 0;
}

int listagem(){

}

int consulta(){

}

int emprestimo(){

}

int devolucao(){

}