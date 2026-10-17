/*

Estas funcoes fazem pequenas verificacoes/ações curtas e objetivas, somente para auxiliar.
Sao genericas, portanto, quando possivel, não devem usar as variaveis globais diretamente.

*/

#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "input_verification.h"

//
//Edicao de texto e estetica do terminal

void resetar_buffer(){
    while(getchar() != '\n'); 
}

void pausa(){
    printf("\nPressione qualquer tecla para continuar.\n");
    resetar_buffer();
}

void limpar_tela(){
    printf("\033[1J\033[H");
}

int sim(){
    printf("[s/n] ");
    char c; scanf(" %c", &c); resetar_buffer();

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

void tirar_enter(char string[]){
    string[strcspn(string, "\n")] = '\0';
}

int remover_espacos(char string[]){
    char novo[strlen(string)+1];
    int n = 0;

    tirar_enter(string);

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

int strstr_noCS(char string1[], char string2[], int margem){
    char novo1[TAM_STRING], novo2[TAM_STRING];
    strcpy(novo1, string1);
    strcpy(novo2, string2);
    letras_minusculas(novo1); letras_minusculas(novo2);

    int contador=0;
    double razao=0;
    for(int i=0; i<strlen(novo1); i++){
        contador = 0; razao=0;

        for(int j=0; j<strlen(novo2); j++){
            if(novo2[j] == novo1[i+j])contador++;
        }

        razao = ((float)margem/100)*(strlen(novo2));
        if(contador >= razao) return 1;
    }

    return 0;
}

//
//Outros

int livro_duplicado(Livros l){
    for(int i=0; i<total_livros; i++){
        int correspondencias = 0;

        if(strcmp_noCS(l.titulo, livro[i].titulo) == 0) correspondencias++;
        if(strcmp_noCS(l.autor, livro[i].autor) == 0) correspondencias++;
        if(strcmp_noCS(l.editora, livro[i].editora) == 0) correspondencias++;

        if(correspondencias == 3) return i;
    }
    return -1;
}

int erro(int i){
    switch(i){
        case 1: //sem livros 
            if(total_livros == 0){
                printf("Voce nao pode realizar esta acao pois nao existem livros cadastrados no sistema." VOLTAR_APAGAR);
                return 1;
            }
            return 0;
        case 2: //sem usuarios
            if(total_usuarios == 0){
                printf("Voce nao pode realizar esta acao pois nao existem usuarios cadastrados no sistema." VOLTAR_APAGAR);
                return 1;
            }
            return 0;
        case 3:
            if(user == NULL){
                printf("Ocorreu um erro ao acessar o usuario. Feche o programa e tente novamente." VOLTAR_APAGAR);
                return 1;
            }
            return 0;
        case 4: //usuario bloqueado
            if(erro(3)) return 1;
            if(user->suspenso){
                printf("Voce alcancou o limite toleravel de devolucoes atrasadas. Voce esta bloqueado de realizar esta acao ate resolver suas pendencias.");
                printf(VOLTAR_APAGAR);
                return 1;
            }
            return 0;
    }
}

void passagem_de_tempo(){

    for(int i=0; i<total_usuarios; i++){
        int x=0;
        for(int j=0; j<usuario[i].qtd_emp; j++){
            Emprestimos *e = &usuario[i].emprestimo[j];

            int dias = dia_de_hoje - e->tempo_inicio;

            if(dias > e->prazo){
                usuario[i].emprestimo[j].atrasado = 1;
                x++;
            }

        }

        if(x >= LIM_ATRASOS) usuario[i].suspenso = 1;
        else if(x == 0) usuario[i].suspenso = 0;
    }
}

int qtd_atrasos(Usuarios u){
    int q=0;
    for(int i=0; i< u.qtd_emp; i++){
        if(u.emprestimo[i].atrasado) q++;
    }
    return q;
}

int busca_codigo(Livros lista[], int tam, char codigo[]){
    for(int i=0; i<tam; i++){
        if(strcmp(lista[i].codigo, codigo) == 0) return i;
    }
    return -1;
}

int busca_rapida(){
    printf("\nInsira um codigo para ver mais detalhes ou deixe vazio para cancelar.\n");

    char codigo[TAM_CODIGO];
    int i;
    while(ler_codigo_existente(codigo, &i));
    if(string_vazia(codigo)) return 0;

    limpar_tela();
    exibir_info_livro(livro[i]);
    pausa();
    
    return 1;
}

//
//Impressão de informações

void exibir_info_livro(Livros livro){
    printf("Titulo: %s\n", livro.titulo);
    printf("Autor: %s\n", livro.autor);
    printf("Codigo: %s\n", livro.codigo);
    printf("Editora: %s\n", livro.editora);
    printf("Ano de publicacao: %d\n", livro.ano);
    printf("Edicao: %da\n", livro.edicao);
    printf("Exemplares disponiveis: %d\n", livro.qtdDisponiveis);
}

void exibir_info_rapida(Livros livro){
    printf("[%s] %s - %s\n", livro.codigo, livro.titulo, livro.autor);
}

void imprimir_lista_livros(Livros vetor[], int max){
    for(int i=0; i<max; i++){
        printf("\n");
        exibir_info_rapida(vetor[i]);
    }
}

void imprimir_info_usuario(Usuarios u){
    printf("Nome: %s\n", u.nome);
    printf("Emprestimos ativos: %d\n", u.qtd_emp);
    printf("Emprestimos atrasados: %d\n", qtd_atrasos(u));
    printf("Situacao da conta: ");
    u.suspenso ? printf("suspensa.\n") : printf("regular.\n");
}

//
//Relacionados ao vetor

void apagar_livro(Livros vetor[], int x, int *tam){
    for(int i=x; i<(*tam) - 1; i++){
        vetor[i] = vetor[i+1];
    }
    (*tam)--;
}

void apagar_usuario(Usuarios vetor[], int x, int *tam){
    for(int i=x; i<(*tam) - 1; i++){
        vetor[i] = vetor[i+1];
    }
    (*tam)--;
}

void swap_livros(Livros *livro1, Livros *livro2){
    Livros temp = *livro1;
    *livro1 = *livro2;
    *livro2 = temp;
}

//
//Leitura de dados do programa

void avancar_linha(FILE *arquivo) {
    int c;
    while ((c = fgetc(arquivo)) != '\n' && c != EOF);
}

void ARQ_lerString(FILE *arquivo, int tam, char string[]){
    fgets(string, tam, arquivo);

    char *p = strchr(string, '\n');
    /*
        p indica se o \n foi 'consumido' pela string ou nao, porque, se nao foi 
        (exemplo, string com exatamente 99 caracteres), o proximo fgets vai ler 
        este \n e todo o resto vai ficar armazenado errado
    */

    if (p != NULL) *p = '\0'; //se \n foi consumido pela string
    else avancar_linha(arquivo); //se \n foi mantido no arquivo (tamanho maximo de string)
}

void ARQ_lerInt(FILE *arquivo, int *n){
    fscanf(arquivo, "%d", n); 
    avancar_linha(arquivo); //para tirar o \n que deixa o scanf
}

int carregar_dados(){
    FILE *arquivo;

    //Leitura de Usuarios
    arquivo = fopen("dados_programa/usuarios.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao carregar usuarios. O programa iniciara sem usuarios cadastrados.\n");
    }
    else{
        ARQ_lerInt(arquivo, &total_usuarios);

        for(int i=0; i<total_usuarios; i++){
            ARQ_lerString(arquivo, TAM_STRING, usuario[i].nome);
            ARQ_lerString(arquivo, TAM_SENHA, usuario[i].senha);

            ARQ_lerInt(arquivo, &usuario[i].qtd_emp);
            ARQ_lerInt(arquivo, &usuario[i].suspenso);

            for(int j=0; j<usuario[i].qtd_emp; j++){
                ARQ_lerString(arquivo, TAM_CODIGO, usuario[i].emprestimo[j].codigo);

                ARQ_lerInt(arquivo, &usuario[i].emprestimo[j].prazo);
                ARQ_lerInt(arquivo, &usuario[i].emprestimo[j].atrasado);
                fscanf(arquivo, "%ld", &usuario[i].emprestimo[j].tempo_inicio); avancar_linha(arquivo);
            }
        }
        fclose(arquivo);
    }

    //Leitura de Livros
    arquivo = fopen("dados_programa/livros.txt", "r");
    if(arquivo == NULL){
        printf("Erro ao carregar livros. O programa iniciara sem livros cadastrados.\n");
    }
    else{
        ARQ_lerInt(arquivo, &total_livros);

        for(int i=0; i<total_livros; i++){
            ARQ_lerString(arquivo, TAM_CODIGO, livro[i].codigo);
            ARQ_lerString(arquivo, TAM_STRING, livro[i].titulo);
            ARQ_lerString(arquivo, TAM_STRING, livro[i].autor);
            ARQ_lerString(arquivo, TAM_STRING, livro[i].editora);

            ARQ_lerInt(arquivo, &livro[i].ano);
            ARQ_lerInt(arquivo, &livro[i].quantidade);
            ARQ_lerInt(arquivo, &livro[i].qtdDisponiveis);
            ARQ_lerInt(arquivo, &livro[i].edicao);
        }
        fclose(arquivo);
    }

    return 1;
}

int salvar_dados(){
    FILE *arquivo;

    //Salvar Usuarios
    arquivo = fopen("dados_programa/usuarios.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao salvar usuarios. Arquivo nao encontrado.\nDeseja sair do programa mesmo assim? ");
        if(!sim()) return 0;
    }
    fprintf(arquivo, "%d\n", total_usuarios);
    for(int i=0; i<total_usuarios; i++){
        fprintf(arquivo, "%s\n", usuario[i].nome);
        fprintf(arquivo, "%s\n", usuario[i].senha);
        fprintf(arquivo, "%d\n", usuario[i].qtd_emp);
        fprintf(arquivo, "%d\n", usuario[i].suspenso);

        for(int j=0; j<usuario[i].qtd_emp; j++){
            fprintf(arquivo, "%s\n", usuario[i].emprestimo[j].codigo);
            fprintf(arquivo, "%d\n", usuario[i].emprestimo[j].prazo);
            fprintf(arquivo, "%d\n", usuario[i].emprestimo[j].atrasado);
            fprintf(arquivo, "%ld\n", usuario[i].emprestimo[j].tempo_inicio);
        }
    }
    fclose(arquivo);

    //Salvar livros
    arquivo = fopen("dados_programa/livros.txt", "w");
    if(arquivo == NULL){
        printf("Erro ao salvar livros. Arquivo nao encontrado.\nDeseja sair do programa mesmo assim? ");
        if(!sim()) return 0;
    }
    fprintf(arquivo, "%d\n", total_livros);
    for(int i=0; i<total_livros; i++){
        fprintf(arquivo, "%s\n", livro[i].codigo);
        fprintf(arquivo, "%s\n", livro[i].titulo);
        fprintf(arquivo, "%s\n", livro[i].autor);
        fprintf(arquivo, "%s\n", livro[i].editora);

        fprintf(arquivo, "%d\n", livro[i].ano);
        fprintf(arquivo, "%d\n", livro[i].quantidade);
        fprintf(arquivo, "%d\n", livro[i].qtdDisponiveis);
        fprintf(arquivo, "%d\n", livro[i].edicao);
    }
    fclose(arquivo);
    
    return 1;
}

