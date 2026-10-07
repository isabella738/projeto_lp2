/*

Estas funcoes fazem pequenas verificacoes/ações curtas e objetivas, somente para auxiliar.
Sao genericas, portanto, quando possivel, não devem usar as variaveis globais diretamente.

*/

#include <stdio.h>
#include <string.h>
#include "settings.h"
#include "input_verification.h"

//
//De texto e de estetica do terminal

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

void pausa(){
    printf("\nPressione qualquer tecla para continuar.\n");
    char c[100]; fgets(c, 100, stdin); //tamanho grande p tentar não dar estouro de buffer
}

void limpar_tela(){
    printf("\033[1J\033[H");
}

//
//De impressão de informações

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

int qtd_atrasos(Usuarios u){
    int q=0;
    for(int i=0; i< u.qtd_emp; i++){
        if(u.emprestimo[i].atrasado) q++;
    }
    return q;
}

void imprimir_info_usuario(Usuarios u){
    printf("Nome: %s\n", u.nome);
    printf("Emprestimos ativos: %d\n", u.qtd_emp);
    printf("Emprestimos atrasados: %d\n", qtd_atrasos(u));
    printf("Situacao da conta: ");
    u.suspenso ? printf("suspensa.\n") : printf("regular.\n");
}

//
//Booleanos

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

int sem_livros(){
    if(total_livros == 0){
        printf("Voce nao pode realizar esta acao pois nao existem livros cadastrados no sistema." VOLTAR_APAGAR);
        return 1;
    }
    return 0;
}

int sem_usuarios(){
    if(total_usuarios == 0){
        printf("Voce nao pode realizar esta acao pois nao existem usuarios cadastrados no sistema." VOLTAR_APAGAR);
        return 1;
    }
    return 0;
}

int usuario_bloqueado(Usuarios u){
    if(u.suspenso){
        printf("Voce alcancou o limite toleravel de devolucoes atrasadas. Voce esta bloqueado de realizar esta acao ate resolver suas pendencias.");
        printf(VOLTAR_APAGAR);
        return 1;
    }
    return 0;
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
//Outros

void passagem_de_tempo(){
    int dias = (dia_de_hoje - ultimo_dia)/(3600*24);

    for(int i=0; i<total_usuarios; i++){
        int x=0;
        for(int j=0; j<usuario[i].qtd_emp; j++){

            if((usuario[i].emprestimo[j].prazo -= dias) <= 0){
                usuario[i].emprestimo[j].atrasado = 1;
                x++;
            }

        }

        if(x >= LIM_ATRASOS) usuario[i].suspenso = 1;
        else if(x == 0) usuario[i].suspenso = 0;
    }
}

/*int qtd_atrasos(Usuarios u){
    int q=0;
    for(int i=0; i< u.qtd_emp; i++){
        if(u.emprestimo[i].atrasado) q++;
    }
    return q;
}*/

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