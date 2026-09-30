#include <stdio.h>
#include <string.h>

#define VOLTAR_APAGAR "\033[F\r\033[2K\r"

int main(){
    char palavra[10];
    int p=0;
    do{
        char c = getchar();
        fflush(stdout);
        printf("\033[1D*");
        palavra[p] = c;

    }while(1);
    printf("%s\n", palavra);

    return 0;
}