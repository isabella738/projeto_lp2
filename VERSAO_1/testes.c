#include <stdio.h>
#include <string.h>
#include <time.h>

#define VOLTAR_APAGAR "\033[F\r\033[2K\r"

int main(){
    time_t data_atual;//basicamente um long int

    time(&data_atual);//retorna o tempo em segundos desde 1o de janeiro de 1970 (a "Era Unix") até hoje

    printf("%ld\n", data_atual/(3600*24*365));//isso da 56 (2026-1970)

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