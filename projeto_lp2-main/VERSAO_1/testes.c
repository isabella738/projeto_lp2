#include <stdio.h>
#include <string.h>

int remover_espacos(char texto[]){
    char novo[strlen(texto)];
    int n = 0;

    if(texto[strlen(texto)-1] == '\n') texto[strlen(texto)-1] = '\0';

    for(int i=0; i<strlen(texto)-1; i++){
        if(texto[i] == ' ' && (texto[i+1] == ' ' || texto[i+1] == '\0')) continue;
        else{ novo[n] = texto[i]; n++;}
    }

    novo[n] = '\0';
    if(novo[0] == ' ') for(int i=0; i<n; i++) novo[i] = novo[i+1];

    strcpy(texto, novo);
}

#define VOLTAR_APAGAR "\033[F\r\033[2K\r"

int main(){
    
    printf("linha1\nlinha2\nlinha3"VOLTAR_APAGAR);
    printf("?\n\n\n");
    return 0;
}