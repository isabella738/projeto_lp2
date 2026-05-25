#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_CHAR 10

int main(){

    int flag=1, opcao, i=0, tam;
    char atividade[50][MAX_CHAR];

    while(flag==1){
        printf("===============================");
        printf("\n             MENU              ");
        printf("\n===============================");
        printf("\n\n1 - Cadastrar nova atividade\n2 - Listagem das atividades\n3 - Movimentacao das atividades\n4 - Quantidade de atividades\n5 - Busca de atividade\n");
        do{
            printf("\nDigite o numero da opcao desejada: ");
            scanf("%d", &opcao);

            int c;//limpa o buffer do teclado pq o fgets estava lendo o \n
            while((c=getchar()) != '\n' && c !=EOF);

            if(opcao<1 || opcao>5){
                printf("\nOpcao invalida!");
            }
        }while(opcao<1 || opcao>5);//repete o scanf ate a opcao ser valida

        switch(opcao){
            case 1:
                printf("===============================");
                printf("\n     CADASTRO DE ATIVIDADE     ");
                printf("\n===============================");
                do{
                    printf("\n\nNome da atividade(max 100 caracteres): ");
                    fgets(atividade[i], MAX_CHAR, stdin);//ainda nao funciona, nao eh pra ler do teclado
                    puts(atividade[i]);
                    i++;
                    printf("\nCadastrar outra atividade?\n1 - sim\n2 - nao\n");
                    scanf("%d", &flag);
                    int c;//limpa o buffer do teclado pq o fgets estava lendo o \n
                    while((c=getchar()) != '\n' && c !=EOF);
                }while(flag==1);//terminar isso aqui, p verificar se o tamanho da atividade cabe
                break;
            case 2:
                printf("===============================");
                printf("\n    LISTAGEM DE ATIVIDADES     ");
                printf("\n===============================");
                printf("\nA FAZER:");
                /////
                printf("\nEM ANDAMENTO:");
                /////
                printf("\nCONCLUIDO:");
                /////

                break;
            case 3:
                printf("===============================");
                printf("\n   MOVIMENTACAO DE ATIVIDADES  ");
                printf("\n===============================");
                printf("\nEscolha a atividade que deseja movimentar: ");

                break;
            case 4:
                printf("===============================");
                printf("\n   QUANTIDADE DE ATIVIDADES    ");
                printf("\n==============================");
                break;
            case 5:
                printf("===============================");
                printf("\n      BUSCA DE ATIVIDADE       ");
                printf("\n===============================");
                break;
        }

        do{
            printf("\n\nDeseja continuar?\n\n1 - sim\n2 - nao\n");
            scanf("%d", &flag);
            if(flag<1 || flag>2){
                printf("\nOpcao invalida!");
            }
        }while(flag<1 || flag>2);//repete o scanf ate a opcao ser valida
    }

    return 0;

}
