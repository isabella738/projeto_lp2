int string_vazia(char texto[]);

int sim();//imprime [s/n] e espera um caractere

int remover_espacos(char texto[]);//remove espacos e o enter do fgets 

int somente_numeros(char texto[]);

int letras_minusculas(char string[]);//aviso: a funcao altera diretamente a string

int strcmp_noCS(char string1[], char string2[]);//strcmp sem Case Sensitive. Retorna 0 (iguais) ou 1 (diferentes)

int strstr_noCS(char string1[], char string2[]);//strstr sem Case Sentsitive. Retorna 1 se string2 for substring de string1

int busca_codigo(Livros livro[], int tam, char codigo[]);//retorna a posicao no array do livro dado pelo codigo

void exibir_info_livro(Livros livro);//imprime todas as informacoes do livro

void exibir_info_rapida(Livros livro);//exibe codigo, titulo e autor somente

void imprimir_lista_livros(Livros vetor[], int max);//imprime qualquer vetor do tipo Livros com informacoes rapidas

void swap_livros(Livros *livro1, Livros *livro2);

int livro_duplicado(Livros l);//verifica se existe um ja existe um livro com o mesmo titulo, autor, editora, e edicao de 'l' cadastrado no sistema

void apagar_livro(Livros lista[], int x, int *tam);//apaga o livro x de uma lista do tipo Livros