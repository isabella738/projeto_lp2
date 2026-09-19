/*

As funcoes retornam 1 caso o usuario queira fazer um novo processo dentro da mesma funcao.
Exemplo de uso:
    while(cadastro());

*/

#include <stdio.h>
#include "settings.h"
#include "input_verification.h"
#include "auxiliary_functions.h"

int cadastro(){
    /*
        cadastro
    */

    printf("Fazer o cadastro de um novo livro? ");
    if(sim()) return 1;
    
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