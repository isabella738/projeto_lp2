/*

As funcoes retornam 1 caso o usuario queira fazer um novo processo dentro da mesma funcao.
Exemplo de uso:
    while(cadastro());

Obs: o codigo contem um mecanismo de "cancelar acao", que consiste em digitar uma string vazia
(se o programa requerir uma string) ou inserir 0 (se o programa requerir um inteiro).
Apos toda entrada deve-se fazer uma verificacao para os respectivos casos, e retornar 0 (ou break) 
caso verdadeiro, para sair do loop.
*É por isso tambem que nao existe verificacao de string vazia em ler_string

Exemplos de uso:
    char titulo[x];
    while(ler_string(titulo, x));
    if(string_vazia(titulo)) return 0;

    //

    int escolha;
    while(ler_int(&escolha, 0, 10));
    if(!escolha) return 0;
*/

#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "input_verification.h"
#include "auxiliary_functions.h"
#include "main.h"

int cadastro_usuario() {
    printf("**=======================**\n");
    printf("    CADASTRO DE USUARIO    \n");
    printf("**=======================**\n");

    do {
        char nome[TAM_STRING], senha[TAM_SENHA];
        if(total_usuarios >= TAM_USUARIOS) { // tirar dps da alocacao dinamica
            printf("Limite de usuarios atingido.\n");
            break;
        }

        int repetido;
        do {
            printf("Digite seu nome:\n"); 
            while(ler_string(nome, TAM_STRING));
            if(string_vazia(nome)) return 0;
            repetido = 0;
            for(int i = 0; i < total_usuarios; i++) {
                if(strcmp(nome, usuario[i].nome)==0) {
                    repetido = 1;
                    break;
                }
            }
            if (repetido) {
                printf("Ja existe um usuario com esse nome. Tente novamente.\n");
            }
        } while(repetido);
        printf("Crie uma senha de (%d caracteres):\n", TAM_SENHA-1); 
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

int cadastro(){ // so para o proprietario
    printf("**=======================**\n");
    printf("     CADASTRO DE LIVROS    \n");
    printf("**=======================**\n");

    if(total_livros >= MAX_LIVROS) {
        printf("Limite de livros atingido!"); // dps a gente tira com a alocacao dinamica
    }

    Livros l;
    printf("Digite as informacões sobre o novo livro:\n");
    if(!ler_livro(&l)) return 0;
    
    int x = livro_duplicado(l);
    int salvar = 1;

    if(x >= 0){
        printf("Encontramos um livro ja cadastrado com informacoes semelhantes a este:\n");
        exibir_info_livro(livro[x]);
        printf("Deseja cadastrar mesmo assim? ");
        salvar = sim();
    }

    if(salvar) {
        livro[total_livros] = l;
        total_livros++;
        printf("Cadastro realizado com sucesso!");
    }
    else {
        printf("Acao cancelada.\n");
    }

    printf("Fazer o cadastro de um novo livro?\n");
    if(sim()) return 1;
    return 0;
}

int listagem(){
    /*
        Ordena por:
        - Adicionados recentemente
        - Ordem alfabetica
        - Ano de publicacao (+ recentes)
        - Ano de publicacao (+ antigos)

        Consiste em: copiar o vetor de livros para uma nova variavel, e entao organizar os livros
        nesta nova variavel. O vetor original fica intacto

        Obs: fiz alguns testes e acredito que a organizacao por ordem alfabetica esteja
        funcionando, mas nao tenho certeza...
    */

    printf("**=======================**\n");
    printf("          LISTAGEM         \n");
    printf("**=======================**\n");

    printf("Ordenar por:\n");
    printf("(1) Adicionados recentemente\n");
    printf("(2) Ordem alfabetica (titulo)\n");
    printf("(3) Ano de publicacao (+ recentes primeiro)\n");
    printf("(4) Ano de publicacao (+ antigos primeiro)\n");
    printf("(0) Sair\n");
    int n; while(ler_int(&n, 0, 4));
    if(!n) return 0;

    if(total_livros == 0) {
        printf("Nenhum livro cadastrado\n");
        return 0;
    }
    Livros lista[total_livros];//onde fica a nova organizacao
    memcpy(lista, livro, sizeof(Livros)* total_livros);

    switch(n){
        case 1: //Imprimir livros simplesmente como eles aparecem no vetor
            break;
        case 2: //exibe em ordem alfabetica (pelo titulo)
            for(int i=0; i<total_livros; i++){
                for(int j=i+1; j<total_livros; j++){

                    char string1[strlen(lista[i].titulo)], string2[strlen(lista[i].titulo)];
                    int soma1=0, soma2=0;

                    strcpy(string1, lista[i].titulo); letras_minusculas(string1);
                    strcpy(string2, lista[j].titulo); letras_minusculas(string2);

                    for(int k=0; k<strlen(string1) && k<strlen(string2); k++){
                        soma1 += string1[k];
                        soma2 += string2[k];

                        if(soma1 != soma2) break;
                    }

                    if(soma1 > soma2 || (soma1 == soma2 && strlen(string2) < strlen(string1))){
                        /*
                            Ou seja:
                            Se a "soma" dos primeiros caracteres de string 2 for menor que de string1,
                            ou as somas são iguais, mas string2 é menor que string1 (substring)
                        */

                        swap_livros(&lista[i], &lista[j]);
                    }
                }
            }
            break;
        case 3: //ano de publicacao, mais recentes
            for(int i=0; i<total_livros; i++){
                for(int j=i+1; j<total_livros; j++){

                    if(lista[j].ano > lista[i].ano){
                        swap_livros(&lista[i], &lista[j]);
                    }

                }
            }
            break;
        case 4: //ano de publicacao, mais antigos
            for(int i=0; i<total_livros; i++){
                for(int j=i+1; j<total_livros; j++){

                    if(lista[j].ano < lista[i].ano){
                        swap_livros(&lista[i], &lista[j]);
                    }

                }
            }
            break;
    }

    imprimir_lista_livros(lista, total_livros);

    printf("Fazer outra listagem?\n");
    if(sim()) return 1;
    return 0;
}

int consulta(){
    return 0;
}

int emprestimo(){
    return 0;
}

int devolucao(){
    return 0;
}

int busca(){
    /*
        Procura por:
        - Titulo
        - Autor
        - Editora

        Imprime na tela a medida que for encontrando correspondencias. A lista nao e
        armazenada em nenhum lugar real e é meramente visual
    */

    printf("**=======================**\n");
    printf("           BUSCA           \n");
    printf("**=======================**\n");

    int n, contador = 0;

    printf("Buscar por titulo (1), nome do autor (2) ou editora (3)?\n");
    while(ler_int(&n, 0, 3));
    if(!n) return 0;

    char busca[TAM_STRING]; 
    printf("Insira sua busca.\n"); while(ler_string(busca, TAM_STRING));
    if(string_vazia(busca)) return 0;

    for(int i=0; i<total_livros; i++){
        int achou = 0;

        switch(n){
            case 1:
                achou = strstr_noCS(livro[i].titulo, busca); break;
            case 2:
                achou = strstr_noCS(livro[i].autor, busca); break;
            case 3:
                achou = strstr_noCS(livro[i].editora, busca); break;
        }
        
        if(achou){
            contador++;
            exibir_info_rapida(livro[i]);
        }
    }

    if(!contador){
        printf("Nao foram encontrados resultados para esta busca.\n");
    }
    else printf("Foram encontrados %d resultados para esta busca.\n", contador);

    printf("\nRealizar nova busca?");
    if(sim())return 1;
    return 0;
}

int menu (int posicao) {
    int r;
    do {
    printf("**=======================**\n");
    printf("           MENU            \n");
    printf("**=======================**\n");
    printf("[1] Listagem de livros\n[2] Busca de livros\n[3] Emprestimo\n[4] Devolucao\n[5] Consulta de livros\n[6] Voltar\n"); 
    printf("Digite a opcao que deseja: ");
    while(ler_int(&r, 1, 6));
    switch(r) {
        case 1:
            while(listagem());
            break;
        case 2: 
            while(busca());
            break;
        case 3: 
            while(emprestimo());
            break;
        case 4:
            while(devolucao());
            break;
        case 5:
            while(consulta());
            break;
        default:
            entrada_usuario();
            break;
    }
    } while (r != 6);
    return 0;
}

int menu_proprietario() { // ideiaaa: proprietario poder remover livros e ver o emprestimo da glr
    int r;
    do {
    printf("**=======================**\n");
    printf("    AREA DO PROPRIETARIO   \n");
    printf("**=======================**\n");  
    printf("[1] Cadastrar livro\n[2] Remover livro\n[3] Emprestimos ativos\n[4] Voltar\n");
    printf("Digite a opcao que deseja: ");
    while(ler_int(&r, 1, 4));
    switch(r) {
        case 1: while(cadastro()); break;
        case 2: break;
        case 3: break;
    } 
    } while (r != 4);

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
                menu_proprietario();
                return 1;
            }

            printf("Codigo invalido, deseja tentar novamente?\n");
        } while (sim());

    } else if (resposta == 2) { //login usuario
        char nome[TAM_STRING], senha[TAM_SENHA];

        printf("Digite seu nome (ou deixe vazio para cancelar):\n"); 
        while(ler_string(nome, TAM_STRING));
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

    } else if (resposta == 3) { //cadastro de novo usuario
        cadastro_usuario();
    } else {
        printf("Saindo do Sistema...");
        return 0;
    }

}