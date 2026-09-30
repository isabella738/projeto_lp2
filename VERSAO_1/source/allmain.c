#include <stdio.h>
#include "main.h"
#include "auxiliary_functions.h"
#include "settings.h"

int main(){
    do{
        limpar_tela();
        printf("Biblioteca [INSIRA UM NOME MANEIRO AQUI]\n\n");

        printf("Entrar como:\n");
        printf("[1] Proprietário\n");
        printf("[2] Usuario\n");
        printf("[3] Cadastrar novo usuario\n");
        printf("[4] Sair\n\n");

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
                printf("Saindo do Sistema...");
                return 0;
        }
    }while(1);
    
    return 0;
}