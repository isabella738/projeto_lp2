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

//
/*
    > ACOES DE USUARIO
    Em todas as seguintes funcoes vale a seguinte regra:

    return 1 = volta pra mesma funcao (loop)
    return 0 = volta para a funcao MENU
*/

int listagem(){
    /*
        Ordena por:
        - Adicionados recentemente
        - Ordem alfabetica
        - Ano de publicacao (+ recentes)
        - Ano de publicacao (+ antigos)

        Consiste em: copiar o vetor de livros para uma nova variavel, e entao organizar os livros
        nesta nova variavel. O vetor original fica intacto
    */

    printf("**=======================**\n");
    printf("          LISTAGEM         \n");
    printf("**=======================**\n");

    if(total_livros == 0) {
        printf("Nenhum livro cadastrado\n");
        return 0;
    }

    printf("Ordenar por:\n");
    printf("(1) Adicionados recentemente\n");
    printf("(2) Ordem alfabetica (titulo)\n");
    printf("(3) Ano de publicacao (+ recentes primeiro)\n");
    printf("(4) Ano de publicacao (+ antigos primeiro)\n");
    printf("(0) Sair\n");
    int n; while(ler_int(&n, 0, 4));
    if(!n) return 0;

    Livros lista[total_livros];//onde fica a nova organizacao
    memcpy(lista, livro, sizeof(Livros)* total_livros);

    if(n == 1){
        //Imprimir livros simplesmente como eles aparecem no vetor
    }
    else if(n == 2){//exibe em ordem alfabetica (pelo titulo)
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
                        ou as somas são iguais, mas string2 é menor que string1 (substring), a 
                        string2 vai estar alfabeticamente antes de string1
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

    imprimir_lista_livros(lista, total_livros);

    printf("Fazer outra listagem?\n");
    if(sim()) return 1;
    return 0;
}

int busca(){
    /*
        Procura por:
        - Titulo
        - Autor
        - Editora
        - Codigo

        Imprime na tela a medida que for encontrando correspondencias. A lista nao e
        armazenada em nenhum lugar real e é meramente visual
    */

    printf("**=======================**\n");
    printf("           BUSCA           \n");
    printf("**=======================**\n");

    int n, contador = 0;

    printf("Buscar por titulo (1), nome do autor (2), editora (3) ou codigo(4)?\n");
    while(ler_int(&n, 0, 4));
    if(!n) return 0;

    char busca[TAM_STRING]; 
    printf("Insira sua busca.\n"); 

    while(ler_string(busca, TAM_STRING));
    if(string_vazia(busca)) return 0;

    if(n == 4){
        int x = busca_codigo(livro, total_livros, busca);
        if(x >= 0) exibir_info_livro(livro[x]);
        else printf("Nao foram encontrados livros com este codigo.\n");
        return 1;
    }

    for(int i=0; i<total_livros; i++){
        int achou = 0;

        switch(n){
            case 1:
                achou = strstr_noCS(livro[i].titulo, busca); break;
            case 2:
                achou = strstr_noCS(livro[i].autor, busca); break;
            case 3:
                achou = strstr_noCS(livro[i].editora, busca); break;
            case 4: 
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

int consulta(){ // fazer apenas os livros do usuario
    return 0;
}

int emprestimo(){

    printf("**=======================**\n");
    printf("        EMPRESTIMO         \n");
    printf("**=======================**\n");

    if(total_livros == 0){
        printf("Nao existem livros cadastrados no sistema. Fale com o proprietario para que ele adicione livros.\n");
        return 0;
    }

    //busca por codigo p ser exato
    int x;
    printf("\nDigite o codigo do livro desejado: ");
    char cod[TAM_CODIGO];

    do{
        while(ler_codigo(cod));
        if(string_vazia(cod)) return 0;

        x = busca_codigo(livro, total_livros, cod);
        
        if(x < 0) printf("O livro nao existe.\n" VOLTAR_APAGAR);

    }while(x < 0);
    printf(APAGAR_LINHA);

    //agora q achou vai pegar emprestado
    printf("\nLivro encontrado!\n\n");
    exibir_info_livro(livro[x]);

    if(livro[x].qtdDisponiveis > 0){
        printf("\nDeseja fazer um empréstimo? "); 
        
        if(sim()){
            livro[x].qtdDisponiveis = livro[x].qtdDisponiveis - 1;
            
            int *q = &usuario[user_ativo].qtd_emp;
            Emprestimos *e = &usuario[user_ativo].emprestimo[*q]; //só pra encurtar o nome nas proximas linhas

            strcpy(e->codigo, livro[x].codigo);
            e->dias_emprestimo = DIAS_EMPRESTIMO;
            e->atrasado = 0;
            (*q)++;

            printf("\nEmprestimo realizado com sucesso!\n");
        }else{
            return 0;
        }
    }else{
        printf("\nNao ha exemplares disponiveis no momento.");
    }

    return 0;
}

int devolucao(){

    printf("**=======================**\n");
    printf("         DEVOLUCAO         \n");
    printf("**=======================**\n");

    return 0;
}

int editar_conta(){

    printf("**=======================**\n");
    printf("      GERENCIAR CONTA      \n");
    printf("**=======================**\n");

    printf("\n");
    imprimir_info_usuario(*user);

    printf("\nEscolha uma acao:\n");
    printf("[1] Editar Nome\n");
    printf("[2] Redefinir senha\n");
    printf("[3] Excluir conta\n");
    printf("[0] Sair\n");

    int x; while(ler_int(&x, 0, 3));
    if(!x) return 0;

    int sucesso = 0;
    if(x == 1){
        char novo[TAM_STRING];
        printf("Insira o novo nome:\n");

        while(ler_novo_nome(novo));
        if(string_vazia(novo)) return 1; //return 1 = volta pra esse mesmo menu

        printf("A seguinte modificacao sera feita:\n");
        printf("%s -> %s\n", user->nome, novo);
        printf("Continuar? ");

        if(sim()){
            strcpy(user->nome, novo);
            sucesso = 1;
        }
    }
    else if(x == 2){
        char novo[TAM_SENHA] = {0};
        
        printf("Insira a nova senha:\n");
        ler_nova_senha(novo);
        if(string_vazia(novo)) return 1;

        strcpy(user->senha, novo);
        sucesso = 1;
    }
    else if(x == 3){
        printf("Voce tem certeza de que deseja prosseguir? Esta acao nao pode ser desfeita. ");

        if(sim()){
            apagar_usuario(usuario, user_ativo, &total_usuarios);
            printf("Acao bem sucedida.\n");
            return -1;
        }
    }

    if(sucesso) printf("Modificacao bem sucedida.\n");
    else printf("Acao cancelada.\n");

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
    printf("**=======================**\n");
    printf("     CADASTRO DE LIVROS    \n");
    printf("**=======================**\n");

    if(total_livros >= MAX_LIVROS) {
        printf("Limite de livros atingido!"); // dps a gente tira com a alocacao dinamica
        printf(VOLTAR_LINHA);
        return 0;
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

int editar_livro(){
    printf("**=======================**\n");
    printf("       EDITAR LIVROS       \n");
    printf("**=======================**\n");

    if(total_livros == 0){
        printf("Nao existem livros cadastrados no sistema. Digite 1 para iniciar um novo cadastro.\n");
        printf(VOLTAR_LINHA);
        return 0;
    }

    char codigo[TAM_CODIGO];
    int x;
    printf("Insira o código do livro: \n"); 
    
    //loop para escolha de um livro
    do{
        while(ler_codigo(codigo));
        if(string_vazia(codigo)) return 0;
        
        x = busca_codigo(livro, total_livros, codigo);
        if(x < 0){
            printf("Nao existe um livro cadastrado com este codigo. Tente novamente.\n"VOLTAR_APAGAR);
            continue;
        }
        printf(APAGAR_LINHA);

    }while(x < 0);

    //loop para edicoes no livro escolhido
    do{
        printf("\n------------------\n");
        printf("Livro selecionado:\n"); exibir_info_livro(livro[x]);

        printf("\nEscolha uma acao:\n");
        printf("[1] Editar Titulo\n");
        printf("[2] Editar Autor\n");
        printf("[3] Alterar ano de publicacao\n");
        printf("[4] Alterar Editora\n");
        printf("[5] Alterar Edicao\n");
        printf("[6] Ajustar numero de exemplares disponiveis\n");
        printf("[7] Excluir Livro\n");
        printf("[0] Sair\n\n");

        int escolha; while(ler_int(&escolha, 0, 7));
        if(!escolha) return 0;

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
            while(ler_int(&n, 0, 100));
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
                return 0;
            }
        }
                    
        if(sucesso) printf("Acao bem sucedida.\n");
        else printf("Acao cancelada.\n");

    }while(1);

    printf("Fazer edicoes para outro livro? ");
    if(sim()) return 1;
    return 0;
}

int vizualizar_emprestimos(){
}

/*
    > LOGIN
    Em todas as seguintes funcoes vale a seguinte regra:

    return 1 = volta pra mesma funcao (loop)
    return 0 = volta para a funcao ENTRADA_USUARIO
*/

int menu_proprietario() {
    /*
        return 1 = volta pra esse mesmo menu
        return 0 = volta para a entrada de usuario
    */
    limpar_tela();
    printf("**=======================**\n");
    printf("    AREA DO PROPRIETARIO   \n");
    printf("**=======================**\n");  
    printf("\n[1] Cadastrar livro\n[2] Editar livro\n[3] Emprestimos ativos\n[4] Voltar\n");
    printf("Digite a opcao que deseja:\n");

    int r;
    while(ler_int(&r, 1, 4));

    switch(r) {
        case 1: while(cadastro()); break;
        case 2: while(editar_livro()); break;
        case 3: while(vizualizar_emprestimos()); break;
        case 4: return 0;
    } 

    return 1;
}

int cadastro_usuario() {
    /*
        return 1 = volta pra esse mesmo menu
        return 0 = volta para a entrada de usuario
    */

    limpar_tela();
    printf("**=======================**\n");
    printf("    CADASTRO DE USUARIO    \n");
    printf("**=======================**\n");

    char nome[TAM_STRING], senha[TAM_SENHA] = {0};
    senha[0] = '\0'; 

    if(total_usuarios >= TAM_USUARIOS) { // tirar dps da alocacao dinamica
        printf("Limite de usuarios atingido.\n");
        return 0;
    }

    printf("Digite seu nome:\n"); 
    while(ler_novo_nome(nome));
    if(string_vazia(nome)) return 0;

    printf("Crie uma senha de (%d caracteres):\n", TAM_SENHA-1);
    while(ler_nova_senha(senha));
    if(string_vazia(senha)) return 0;

    strcpy(usuario[total_usuarios].nome, nome);
    strcpy(usuario[total_usuarios].senha, senha);
    usuario[total_usuarios].qtd_emp = 0;
    total_usuarios++;

    printf("Cadastrar outro usuario?\n");
    if(sim()) return 1;
    return 0;
}

int menu () {//menu comum

    limpar_tela();
    printf("**=======================**\n");
    printf("           MENU            \n");
    printf("**=======================**\n");
    printf("[1] Listagem de livros\n");
    printf("[2] Busca de livros\n");
    printf("[3] Emprestimo\n");
    printf("[4] Devolucao\n");
    printf("[5] Meus livros\n");
    printf("[6] Gerenciar conta\n");
    printf("[0] Sair\n\n");
    
    printf("Digite a opcao que deseja: ");
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
            while((x = editar_conta()) > 0);//significa que o usuario foi apagado
            if(x < 0) return 0;
            break;
        default:
            printf("Voce sera redirecionado para a tela de login. Continuar? ");
            if(sim()) return 0;
            break;
    }
    return 1;
}

//
//Entrada de Usuario

int entrada_usuario() {
    int resposta;
    while(ler_int(&resposta, 1, 4));

    if(resposta == 1) { // proprietario
        char prop[TAM_CODIGO];

        //Loop de validacao do codigo de acesso
        printf("Digite o codigo de acesso:\n");
        do {
            while(ler_codigo(prop));
            if(string_vazia(prop)) return 0;

            if(strcmp(prop, CODIGO_PROP) == 0) {//sucesso
                break;
            }

            printf("Codigo invalido, deseja tentar novamente? ");
            if(!sim()) return 0;
            printf(VOLTAR_LINHA VOLTAR_LINHA APAGAR_LINHA);
        } while (1);
        printf(APAGAR_LINHA);

    } else if (resposta == 2) { //login usuario
        char nome[TAM_STRING], senha[TAM_SENHA];

        if (total_usuarios <= 0) {
            printf("Nao exitem usuarios cadastrados. Entre como proprietario ou inicie um novo 2cadastro.\n");
            printf(VOLTAR_LINHA);//isso garante que a mensagem apareca mesmo quando a tela for limpa no main
            return 0; 
        }

        //
        //Leitura do nome
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
            printf(VOLTAR_LINHA);
            return 0;
        }

        //
        //Validacao da senha
        int tent = 0;
        while(tent < 3) {
            printf("Digite sua senha (ou deixe vazio para cancelar):\n");
            while(ler_senha(senha));
            if(string_vazia(senha)) return 0;

            if(strcmp(senha, usuario[posicao].senha) == 0) {
                break;
            }

            tent++;
            printf("Senha incorreta. Tentativas restantes: %d\n", 3 - tent);
        }

        if(tent >= 3){ 
            printf("Numero maximo de tentativas excedido.\n");
            printf(VOLTAR_LINHA);
            return 0;
        }
        else{
            user_ativo = posicao;
            user = &usuario[user_ativo];

            limpar_tela();
            printf("Seja bem vindo(a) %s\n", user->nome);
        }
    }

    return resposta;
}