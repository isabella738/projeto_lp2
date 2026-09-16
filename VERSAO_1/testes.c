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

int main(){
    char texto[100];
    fgets(texto, 100, stdin);
    remover_espacos(texto);
    printf("%s.", texto);
    return 0;
}