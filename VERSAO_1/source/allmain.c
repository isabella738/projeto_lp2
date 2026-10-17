#include <stdio.h>
#include <time.h>
#include "main.h"
#include "auxiliary_functions.h"
#include "settings.h"

int main(){
    limpar_tela();

    carregar_dados();
    
    time(&dia_de_hoje);
    passagem_de_tempo();

    do{
        printf("Biblioteca [INSIRA UM NOME MANEIRO AQUI]\n\n");

        printf("Escolha uma acao:\n");
        printf("[1] Entrar como Proprietário\n");
        printf("[2] Entrar como Usuario\n");
        printf("[3] Cadastrar novo usuario\n");
        printf("[4] Salvar e Sair\n\n");

        int x = entrada_usuario();

        switch(x){
            case 1:
                while(menu_proprietario());
                break;
            case 2:
                while(menu());
                break;
            case 3:
                while(cadastro_usuario());
                break;
            case 4:
                if(salvar_dados()){
                    printf("\nOs dados foram salvos com sucesso. Saindo do Sistema...\n");
                    return 0;
                }
                break;
        }
        limpar_tela();
    }while(1);
    
    return 0;
}