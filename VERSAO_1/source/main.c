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
#include <time.h>
#include "settings.h"
#include "input_verification.h"
#include "auxiliary_functions.h"
#include "main.h"

//
/*
    > ACOES DE USUARIO
    Em todas as seguintes funcoes vale a seguinte regra:

    return 1 = volta pra mesma funcao (loop)
    return 0 = volta para a funcao MENU
*/

int listagem(){
    if(erro(1)) return 0;
    /*
        Ordena por:
        - Adicionados recentemente
        - Ordem alfabetica
        - Ano de publicacao (+ recentes)
        - Ano de publicacao (+ antigos)

        Consiste em: copiar o vetor de livros para uma nova variavel, e entao organizar os livros
        nesta nova variavel. O vetor original fica intacto
    */
    
    int n;
    Livros lista[total_livros];//onde fica a nova organizacao

    limpar_tela();
    printf(
        "**=======================**\n"
        "          LISTAGEM         \n"
        "**=======================**\n"
        "\n"
        "Ordenar por:\n"
        "(1) Adicionados recentemente\n"
        "(2) Ordem alfabetica (titulo)\n"
        "(3) Ano de publicacao (+ recentes primeiro)\n"
        "(4) Ano de publicacao (+ antigos primeiro)\n"
        "(0) Sair\n"
    );

    while(ler_int(&n, 0, 4));
    if(!n) return 0;

    memcpy(lista, livro, sizeof(Livros)* total_livros);

    if(n == 1){
        for(int i=0; i<total_livros; i++){
            lista[total_livros - 1 - i] = livro[i];
        }
    }
    else if(n == 2){//exibe em ordem alfabetica (pelo titulo)
        for(int i=0; i<total_livros; i++){
            for(int j=i+1; j<total_livros; j++){

                char string1[strlen(lista[i].titulo)+1], string2[strlen(lista[j].titulo)+1];
                int a=0, b=0;

                strcpy(string1, lista[i].titulo); letras_minusculas(string1);
                strcpy(string2, lista[j].titulo); letras_minusculas(string2);

                for(int k=0; k<strlen(string1) && k<strlen(string2); k++){
                    if(string1[k] != string2[k]){ //a primeira ocorrencia de divergencia de caracteres entre as duas strings
                        a = string1[k]; b = string2[k];
                        break;
                    }
                }

                if(b < a || (a == b && strlen(string2) < strlen(string1))){
                    /*
                        Ou seja:
                        Se o caractere b vir antes do a, a string2 vem antes de string1
                        Ou então, se não houver divergencias entre string1 e string2, mas a segunda
                        for menor que a primeira (substring), então ela vem antes
                    */
                    swap_livros(&lista[i], &lista[j]);
                }
            }
        }
    }
    else if(n == 3){//ano de publicacao, mais recentes
        for(int i=0; i<total_livros; i++){
            for(int j=i+1; j<total_livros; j++){

                if(lista[j].ano > lista[i].ano){
                    swap_livros(&lista[i], &lista[j]);
                }

            }
        }
    }
    else if(n == 4){//ano de publicacao, mais antigos
        for(int i=0; i<total_livros; i++){
            for(int j=i+1; j<total_livros; j++){

                if(lista[j].ano < lista[i].ano){
                    swap_livros(&lista[i], &lista[j]);
                }

            }
        }
    }

    do{
        limpar_tela();
        imprimir_lista_livros(lista, total_livros);

    }while(busca_rapida());
    
    return 1;
}

int busca(){
    if(erro(1)) return 0;
    /*
        Procura por:
        - Titulo
        - Autor
        - Editora
        - Codigo
    */

    int n, contador = 0;
    int indices[total_livros]; //guarda o indice do livro que corresponder à busca p facilitar a impressao depois
    char busca[TAM_STRING]; 

    limpar_tela();
    printf(
        "**=======================**\n"
        "           BUSCA           \n"
        "**=======================**\n"
        "\n"
        "Buscar por titulo (1), nome do autor (2), editora (3) ou codigo (4)?\n"
    );

    while(ler_int(&n, 0, 4));
    if(!n) return 0;

    printf(
        "\n"
        "-----------------\n"
        "Insira sua busca:\n"
    );

    //Leitura do codigo (exibe 1 unico resultado)
    if(n == 4){
        busca_rapida();
        return 1;
    }

    //Leitura de uma busca generica
    while(ler_string(busca, TAM_STRING));
    if(string_vazia(busca)) return 0;
    printf("\n");

    //Busca de fato
    for(int i=0; i<total_livros; i++){
        int achou = 0;

        switch(n){
            case 1:
                achou = strstr_noCS(livro[i].titulo, busca, 80); break;
            case 2:
                achou = strstr_noCS(livro[i].autor, busca, 80); break;
            case 3:
                achou = strstr_noCS(livro[i].editora, busca, 80); break;
        }
        
        if(achou){
            indices[contador] = i;
            contador++;
        }
    }

    //Exibição dos resutlados
    if(!contador){
        printf("Nao foram encontrados resultados para esta busca.\n");
        pausa();
    }
    else{ 
        do{
            limpar_tela();
            printf("Foram encontrados %d resultados para esta busca:\n\n", contador);
        
            for(int i=0; i<contador; i++){
                exibir_info_rapida(livro[indices[i]]);
            }
        }while(busca_rapida());
    }

    return 1;
}

int consulta(){ // fazer apenas os livros do usuario
    limpar_tela();
    return 0;
}

int emprestimo(){
    if(erro(1)) return 0;
    if(erro(4)) return 0;

    int x;
    char cod[TAM_CODIGO];

    limpar_tela();
    printf(
        "**=======================**\n"
        "        EMPRESTIMO         \n"
        "**=======================**\n"
        "\n"
        "Digite o codigo do livro desejado:\n"
    );

    ler_codigo_existente(cod, &x);
    if(string_vazia(cod)) return 0;
    printf(APAGAR_LINHA);

    //agora q achou vai pegar emprestado
    printf("\nLivro encontrado!\n\n");
    exibir_info_livro(livro[x]);

    if(livro[x].qtdDisponiveis > 0 && user->qtd_emp < LIM_EMPRESTIMOS){//compara lim_emprestimos p n acessar posicao inexistente
        printf("\nDeseja fazer um empréstimo? "); 
        
        if(sim()){
            livro[x].qtdDisponiveis --;
            
            int *q = &user->qtd_emp;
            Emprestimos *e = &user->emprestimo[*q]; //só pra encurtar o nome nas proximas linhas

            strcpy(e->codigo, livro[x].codigo);
            time(&e->tempo_inicio);
            e->prazo = DIAS_EMPRESTIMO;
            e->atrasado = 0;
            (*q)++;//incrementa a posicao disponivel pro proximo emprestimo

            printf("\nEmprestimo realizado com sucesso!\n");
        }else{
            return 1;
        }
    }else if(user->qtd_emp >= LIM_EMPRESTIMOS){
        printf("\nVoce atingiu o limite de emprestimos.\nFaca uma devolucao.");
    }else{
        printf("\nNao ha exemplares disponiveis no momento.");
    }

    pausa();
    return 1;
}

int devolucao(){
    limpar_tela();
    printf("**=======================**\n");
    printf("         DEVOLUCAO         \n");
    printf("**=======================**\n");

    //to usando o codespace no tablet pq o pc deu pau mas eh uma bos ta
    
    //listagem meus livros
    //digite o codigo o livro a ser devolvido:
    //compara com os codigos da lista
    //y = posicao_codigo_minhaLista;
    //livro[y].qtdDisponiveis++;
    //user->emprestimo[y]=0;
    //for(int i=y; i<LIM_EMPRESTIMOS; i++){
    //reorganiza a lista de emprestimo p n ficar buraco em y
    //}
    //printf("Devolucao concluida com sucesso!");

    pausa();
    return 1;
}

int editar_conta(){
    if(erro(3)) return 0;

    int x, sucesso=0;

    limpar_tela();
    printf(
        "**=======================**\n"
        "      GERENCIAR CONTA      \n"
        "**=======================**\n"
        "\n"
    ); imprimir_info_usuario(*user);

    printf(
        "\n"
        "Escolha uma acao:\n"
        "[1] Editar Nome\n"
        "[2] Redefinir senha\n"
        "[3] Excluir conta\n"
        "[0] Sair\n"
    );

    while(ler_int(&x, 0, 3));
    if(!x) return 0;

    printf("\n-----------------\n");
    if(x == 1){// editar nome
        char novo[TAM_STRING];
        printf("Insira o novo nome:\n");

        while(ler_novo_nome(novo));
        if(string_vazia(novo)) return 1;

        printf(
            "\nA seguinte modificacao sera feita:\n"
            "%s -> %s\n"
            "\nContinuar? ",
            user->nome, novo
        );

        if(sim()){
            strcpy(user->nome, novo);
            sucesso = 1;
        }
    }
    else if(x == 2){ // redefinir senha
        char novo[TAM_SENHA] = {0}, confrm[TAM_SENHA];

        printf("Insira a senha atual:\n");
        do{
            while(ler_senha(confrm));
            if(string_vazia(confrm)) return 1;

            if(strcmp(confrm, user->senha)){
                printf("Senha incorreta. Tente novamente." VOLTAR_APAGAR);
            }
            else break;
        }while(1);
        printf(APAGAR_LINHA);
        
        printf("Insira a nova senha:\n");
        ler_nova_senha(novo);
        if(string_vazia(novo)) return 1;

        strcpy(user->senha, novo);
        sucesso = 1;
    }
    else if(x == 3){ //excluir conta

        if(user->qtd_emp > 0){
            printf(
                "Voce nao pode excluir sua conta enquanto possuir emprestimos ativos.\n"
                "Devolva os livros pendentes para realizar esta acao."
            );
            pausa();
            return 1;
        }

        printf("Voce tem certeza de que deseja prosseguir? Esta acao nao pode ser desfeita. ");
        if(sim()){
            apagar_usuario(usuario, user_ativo, &total_usuarios);
            printf("Acao bem sucedida.\n");
            pausa();

            return -1;//volta para a entrada de usuario
        }
    }

    if(sucesso) printf("\nModificacao bem sucedida.");
    else printf("\nAcao cancelada.");
    pausa();

    return 1;
}

//
/*
    > ACOES DO PROPRIETARIO
    Em todas as seguintes funcoes vale a seguinte regra:

    return 1 = volta pra mesma funcao (loop)
    return 0 = volta para a funcao MENU_PROPRIETARIO
*/

int cadastro(){
    if(erro(5)) return 0; // dps a gente tira com a alocacao dinamica 

    Livros l;
    int x, salvar = 1;

    limpar_tela();
    printf(
        "**=======================**\n"
        "     CADASTRO DE LIVROS    \n"
        "**=======================**\n"
        "\n" 
        "Digite as informacões sobre o novo livro:\n"
    );

    if(!ler_livro(&l)) return 0;
    
    x = livro_duplicado(l);

    if(x >= 0){
        printf("\nAtencao: encontramos um livro ja cadastrado no sistema com informacoes semelhantes a este:\n");
        exibir_info_livro(livro[x]);
        printf("\nDeseja continuar mesmo assim? ");
        salvar = sim();
    }

    if(salvar) {
        livro[total_livros] = l;
        total_livros++;
        printf("Cadastro realizado com sucesso!\n");
    }
    else {
        printf("Acao cancelada.\n");
    }

    printf("\nFazer o cadastro de um novo livro?\n");
    if(sim()) return 1;
    return 0;
}

int editar_livro(){
    if(erro(1)) return 0;

    char codigo[TAM_CODIGO];
    int x;

    limpar_tela(); 
    printf(
        "**=======================**\n"
        "       EDITAR LIVROS       \n"
        "**=======================**\n"
        "\n"
        "Insira o código do livro:\n"
    );

    while(ler_codigo_existente(codigo, &x));
    if(string_vazia(codigo)) return 0;
    printf(APAGAR_LINHA);

    //loop para edicoes no livro escolhido
    do{
        limpar_tela();

        printf("Livro selecionado:\n"); 
        exibir_info_livro(livro[x]);

        printf(
            "\n"
            "Escolha uma acao:\n"
            "[1] Editar Titulo\n"
            "[2] Editar Autor\n"
            "[3] Alterar ano de publicacao\n"
            "[4] Alterar Editora\n"
            "[5] Alterar Edicao\n"
            "[6] Ajustar numero de exemplares disponiveis\n"
            "[7] Excluir Livro\n"
            "[0] Sair\n"
        );

        int escolha; while(ler_int(&escolha, 0, 7));
        if(!escolha) break;

        printf("\n-----------------\n");

        int sucesso=0;
        char novo[TAM_STRING]; int n;

        if(escolha == 1){//titulo
            printf("Novo titulo:\n"); while(ler_string(novo, TAM_STRING));
            if(!string_vazia(novo)){

                printf("A seguinte mudanca sera feita:\n");
                printf("\n%s -> %s\n", livro[x].titulo, novo);
                printf("\nContinuar? ");

                if(sim()){
                    strcpy(livro[x].titulo, novo);
                    sucesso=1;
                }
            }
        }
        else if(escolha == 2){//autor
            printf("Novo autor:\n"); while(ler_string(novo, TAM_STRING));
            if(!string_vazia(novo)){

                printf("A seguinte mudanca sera feita:\n");
                printf("\n%s -> %s\n", livro[x].autor, novo);
                printf("\nContinuar? ");

                if(sim()){
                    strcpy(livro[x].autor, novo);
                    sucesso=1;
                }                    
            }
        }
        else if(escolha == 3){//ano
            printf("Insira o ano de publicacao:\n");
            while(ler_int(&n, 0, ANO_ATUAL));

            livro[x].ano = n;
            sucesso=1;
        }
        else if(escolha == 4){//editora
            printf("Nova editora:\n"); while(ler_string(novo, TAM_STRING));
            if(!string_vazia(novo)){

                printf("A seguinte mudanca sera feita:\n");
                printf("\n%s -> %s\n", livro[x].editora, novo);
                printf("\nContinuar? ");

                if(sim()){
                    strcpy(livro[x].editora, novo);
                    sucesso=1;
                }
                
            }
        }
        else if(escolha == 5){//edicao
            printf("Insira a edicao:\n");
            while(ler_int(&n, 1, 100));
            //sei la, 100 é um numero qualquer, nao acho relevante criar uma macro so pra isso.
            //nao vai existir um livro com mais de CEM edicoes... ne?

            livro[x].edicao = n;
            sucesso=1;
        }
        else if(escolha == 6){//exemplares
            printf("Insira o numero de exemplares:\n");
            while(ler_int(&n, 0, ANO_ATUAL));

            livro[x].edicao = n;
            sucesso=1;
        }
        else if(escolha == 7){//excluir
            printf("Esta acao nao pode ser desfeita. Tem certeza de que quer continuar? ");

            if(sim()){
                apagar_livro(livro, x, &total_livros);
                printf("Remocao bem sucedida.\n");
                return 0;//volta para o menu do proprietario
            }
        }
                    
        if(sucesso) printf("Acao bem sucedida.\n");
        else printf("Acao cancelada.\n");

        pausa();
    }while(1);

    return 1;
}

int visualizar_emprestimos(){
    if(erro(2)) return 0;


    limpar_tela();
}

//
/*
    > LOGIN
    Em todas as seguintes funcoes vale a seguinte regra:

    return 1 = volta pra mesma funcao (loop)
    return 0 = volta para a funcao ENTRADA_USUARIO
*/

int menu_proprietario() {

    limpar_tela();
    printf(
        "**=======================**\n"
        "    AREA DO PROPRIETARIO   \n"
        "**=======================**\n"
        "\n"
        "[1] Cadastrar livro\n"
        "[2] Editar livro\n"
        "[3] Emprestimos ativos\n"
        "[0] Voltar\n"
        "\n"
        "Digite a opcao que deseja:\n"
    );

    int r;
    while(ler_int(&r, 0, 3));

    switch(r) {
        case 1: while(cadastro()); break;
        case 2: while(editar_livro()); break;
        case 3: while(visualizar_emprestimos()); break;
        case 0: return 0;
    } 

    return 1;
}

int cadastro_usuario() {
    if(erro(6)) return 0; // tirar dps da alocacao dinamica

    char nome[TAM_STRING], senha[TAM_SENHA] = {0};

    limpar_tela();
    printf(
        "**=======================**\n"
        "    CADASTRO DE USUARIO    \n"
        "**=======================**\n"
    );

    printf("\nDigite seu nome:\n"); 
    while(ler_novo_nome(nome));
    if(string_vazia(nome)) return 0;

    printf("\nCrie uma senha de (%d caracteres):\n", TAM_SENHA-1);
    while(ler_nova_senha(senha));
    if(string_vazia(senha)) return 0;

    strcpy(usuario[total_usuarios].nome, nome);
    strcpy(usuario[total_usuarios].senha, senha);
    usuario[total_usuarios].qtd_emp = 0;
    usuario[total_usuarios].suspenso = 0;
    total_usuarios++;

    printf("\nCadastro bem sucedido.\n");

    printf("\nCadastrar outro usuario?\n");
    if(sim()) return 1;
    return 0;
}

int menu () {//menu comum
    if(erro(3)) return 0;

    limpar_tela();
    printf(
        "Seja bem vindo(a) %s\n"
        "Voce tem %d pendencias.\n"
        "\n"
        "**=======================**\n"
        "           MENU            \n"
        "**=======================**\n"
        "\n"
        "[1] Listagem de livros\n"
        "[2] Busca de livros\n"
        "[3] Emprestimo\n"
        "[4] Devolucao\n"
        "[5] Meus livros\n"
        "[6] Gerenciar conta\n"
        "[0] Sair\n"
        "\n"
        "Digite a opcao que deseja:\n",
        user->nome, qtd_atrasos(*user)
    );
    
    int r; while(ler_int(&r, 0, 6));
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
        case 6:
            int x;
            while((x = editar_conta()) > 0);
            if(x < 0) return 0; //significa que o usuario foi apagado
            break;
        default:
            printf("Voce sera redirecionado para a tela de login. Continuar? ");
            if(sim()) return 0;
            break;
    }
    return 1;
}

//
/*
    ENTRADA DE USUARIO
    return 0 = voltar ao menu inicial (allmain)
    return 1 = login como proprietario
    return 2 = login como usuario
    return 3 = cadastro de usuario
*/
int entrada_usuario() {
    int resposta;
    while(ler_int(&resposta, 1, 4));
    printf("\033[0J");//limpa tudo oq estiver abaixo do cursor, sem move-lo. 
    //algumas mensagens de erro, tipo de tentativas excedidas sao impressas muito embaixo e nao sao apagadas
    //depois de modo convencional, por isso precisa apagar a tela aqui
    
    if(resposta == 1) { // proprietario
        char prop[TAM_CODIGO];

        //Loop de validacao do codigo de acesso
        printf("\n--------------\n");
        printf("Digite o codigo de acesso:\n");
        do {
            while(ler_codigo(prop));
            if(string_vazia(prop)) return 0;

            if(strcmp(prop, CODIGO_PROP) == 0) {//sucesso
                break;
            }

            printf("Codigo invalido, deseja tentar novamente? ");
            if(!sim()) return 0;
            printf(VOLTAR_APAGAR VOLTAR_APAGAR);
        } while (1);
        printf(APAGAR_LINHA);

    } else if (resposta == 2) { //login usuario
        char nome[TAM_STRING], senha[TAM_SENHA];
        int posicao = -1;

        if(erro(2)) return 0;

        //
        //Leitura do nome
        printf("\n--------------\n");
        printf("Digite seu nome (ou deixe vazio para cancelar):\n"); 
        do{
            while(ler_string(nome, TAM_STRING));
            if(string_vazia(nome)) return 0;

            for(int i = 0; i < total_usuarios; i++) {
                if(strcmp(nome, usuario[i].nome) == 0) {
                    posicao = i;
                    break;
                }
            }

            if(posicao == -1) {
                printf("Usuario nao existe." VOLTAR_APAGAR);
            }
            else break;
        }while(1);
        printf(APAGAR_LINHA);

        //
        //Validacao da senha
        int tent = 0;
        printf("\nDigite sua senha (ou deixe vazio para cancelar):\n");
        while(tent < 3) {
            while(ler_senha(senha));
            if(string_vazia(senha)) return 0;

            if(strcmp(senha, usuario[posicao].senha) == 0) {
                break;
            }

            tent++;
            printf("Senha incorreta. Tentativas restantes: %d"VOLTAR_APAGAR, 3 - tent);
        }
        printf(APAGAR_LINHA);

        if(tent >= 3){ 
            printf("Numero maximo de tentativas excedido.\n");
            printf(APAGAR_LINHA VOLTAR_LINHA VOLTAR_APAGAR);
            return 0;
        }
        else{
            user_ativo = posicao;
            user = &usuario[user_ativo];
        }
    }

    return resposta;
}

