#include <stdio.h>
#include <string.h>
#include <time.h>

#define VOLTAR_APAGAR "\033[F\r\033[2K\r"

int main(){

    //char novo1[] = "Dostoyevski";
    //char novo2[] = "Dostoievski";
    //char novo2[] = "Caza";
    char novo1[] = "Casamento";
    char novo2[] = "b";

    int margem = 90;
    double n;

    int contador=0;
    for(int i=0; i<strlen(novo1); i++){
        contador = 0, n=0;

        for(int j=0; j<strlen(novo2); j++){
            if(novo2[j] == novo1[i+j])contador++;
        }

        n = ((float)margem/100)*(strlen(novo2));

        if(contador >= n){
            printf("%d.00 >= %.2lf sao equivalentes\n", contador, n);
            return 0;
        }
    }
    printf("%d/%.2lf nao sao equivalentes\n", contador, n);



    
    time_t data_atual;//basicamente um long int

    time(&data_atual);//retorna o tempo em segundos desde 1o de janeiro de 1970 (a "Era Unix") até hoje

    printf("%ld\n", data_atual);

    //printf("%ld\n", data_atual/(3600*24*365));//isso da 56 (2026-1970)
    

    return 0;
}

/*
rascunho

dia inicio
prazo
dia atual

prazo -= (dia_atual - dia_inicio)

if(prazo == 0)atrasado

*/