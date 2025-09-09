#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "PilhaDin.h" //inclui os Prot�tipos

//Defini��o do tipo Pilha
struct elemento{
    struct aluno dados;
    struct elemento *prox;
};

struct numero{
    struct numeros num;
    struct numero *prox;
};

struct elemento_char{
    char dado;
    struct elemento_char *prox;
};

typedef struct elemento Elem;
typedef struct numero Num;
typedef struct elemento_char Elem_char;

Pilha* cria_Pilha(){
    Pilha* pi = (Pilha*) malloc(sizeof(Pilha));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

void libera_Pilha(Pilha* pi){
    if(pi != NULL){
        Elem* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int consulta_topo_Pilha(Pilha* pi, struct aluno *al){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    *al = (*pi)->dados;
    return 1;
}

int insere_Pilha(Pilha* pi, struct aluno al){
    if(pi == NULL)
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int remove_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    if((*pi) == NULL)
        return 0;
    Elem *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

int tamanho_Pilha(Pilha* pi){
    if(pi == NULL)
        return 0;
    int cont = 0;
    Elem* no = *pi;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int Pilha_cheia(Pilha* pi){
    return 0;
}

int Pilha_vazia(Pilha* pi){
    if(pi == NULL)
        return 1;
    if(*pi == NULL)
        return 1;
    return 0;
}

void imprime_Pilha(Pilha* pi){
    if(pi == NULL)
        return;
    Elem* no = *pi;
    while(no != NULL){
        printf("Matricula: %d\n",no->dados.matricula);
        printf("Nome: %s\n",no->dados.nome);
        printf("Notas: %f %f %f\n",no->dados.n1,
                                   no->dados.n2,
                                   no->dados.n3);
        printf("-------------------------------\n");
        no = no->prox;
    }
}

int push2(Pilha* pi, struct aluno al1, struct aluno al2){
    if(pi == NULL) // Verifica se a pilha est� vazia
        return 0;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al1;
    no->prox = (*pi);
    *pi = no;

    no = NULL;
    no = (Elem*) malloc(sizeof(Elem));
    if(no == NULL)
        return 0;
    no->dados = al2;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int pop2(Pilha* pi){
    if(pi == NULL) // Verifica se a pilha est� vazia
        return 0;
    if((*pi) == NULL) // Verifica se o �ltimo elemento da pilha est� vazio
        return 0;
    Elem* no = *pi; // Cria um elemento para armazenar o primeiro
    *pi = no->prox; // Passa apontar para o pen�ltimo elemento
    free(no); // Libera o �ltimo elemento
    if((*pi) == NULL) // Verifica se o pen�ltimoest� vazio
        return 0;
    no = *pi;
    *pi = no->prox; // Passa a apontar para o antepen�ltimo
    free(no); // Libera o pen�ltimo
    return 1;
}

int popN(Pilha* pi, int n){
    if(pi == NULL) // Verifica se a pilha est� vazia
        return 0;
    for(int i = 0; i < n; i++){
        Elem* no = *pi; // Cria um elemento para armazenar o primeiro
        *pi = no->prox; // Passa apontar para o pr�ximo elemento
        free(no);
    }
    return 1;
}

Pilha *pilha_copia(Pilha *pi){
    if(pi == NULL) // Verifica se a pilha est� vazia
        return NULL;

    Pilha *pi_aux = cria_Pilha(); // Cria uma pilha auxiliar
    Pilha *copia = cria_Pilha(); // Cria a pilha c�pia

    Elem  *no = *pi; // Cria o n�
    struct aluno al;
    while(pi != NULL){
        consulta_topo_Pilha(pi, &al);
        remove_Pilha(pi);
        insere_Pilha(pi_aux, al);
    }
    no = *pi_aux; // N� recebe a pilha auxiliar
    while(no != NULL){
        consulta_topo_Pilha(pi_aux, &al);
        remove_Pilha(pi_aux);
        insere_Pilha(copia, al);
        insere_Pilha(pi, al);
    }
    libera_Pilha(pi_aux); // Libera a pilha auxiliar
    return copia; // Retorna a cópia
}

Pilha_num *cria_Pilha_num(){
    Pilha_num* pilha = (Pilha_num*) malloc(sizeof(Pilha_num));
    if(pilha != NULL)
        *pilha = NULL;
    return pilha;
}

int insere_Pilha_num(Pilha_num* pi, float n){
    if(pi == NULL)
        return 0;
    Num* no = (Num*) malloc(sizeof(Num));
    if(no == NULL)
        return 0;
    no->num = n;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int maior_menor_media(Pilha_num *pi){
    if (Pilha_num_vazia(pi)) {
        printf("A pilha esta vazia. Nao e possivel calcular.\n");
        return 0;
    }

    Pilha_num* pi_aux = cria_Pilha_num();
    float maior, menor, soma = 0;
    int count = 0;
    float temp_num;

    // Primeiro passo: Desempilha da pilha original e encontra maior, menor e a soma
    consulta_topo_Pilha_num(pi, &temp_num);
    maior = temp_num;
    menor = temp_num;

    while(!Pilha_num_vazia(pi)){
        consulta_topo_Pilha_num(pi, &temp_num);
        if(temp_num > maior)
            maior = temp_num;
        if(temp_num < menor)
            menor = temp_num;
        soma += temp_num;
        count++;
        remove_Pilha_num(pi);
        insere_Pilha_num(pi_aux, temp_num);
    }

    // Segundo passo: Restaura a pilha original
    while(!Pilha_num_vazia(pi_aux)){
        consulta_topo_Pilha_num(pi_aux, &temp_num);
        remove_Pilha_num(pi_aux);
        insere_Pilha_num(pi, temp_num);
    }

    // Libera a pilha auxiliar e imprime os resultados
    libera_Pilha_num(pi_aux);

    printf("\n--- Resultados ---\n");
    printf("Maior: %.2f\n", maior);
    printf("Menor: %.2f\n", menor);
    printf("Media: %.2f\n", soma / count);
    printf("--------------------\n");

    return 1;
}

int comparar_pilha(Pilha* pi1, Pilha* pi2){
    if(pi1 == NULL && pi2 == NULL) // Se as duas forem nulas, s�o iguais
        return 1;
    if(pi1 == NULL || pi2 == NULL) // Se uma das duas for nula, s�o diferentes
        return 0;
    if(tamanho_Pilha(pi1) > tamanho_Pilha(pi2) || tamanho_Pilha(pi1) < tamanho_Pilha(pi2)) // Se o tamanho delas for diferente, s�o diferentes
        return 0;

    Elem *no1 = *pi1; // N� da primeira
    Elem *no2 = *pi2; // N� da segunda
    while(no1 != NULL && no2 != NULL){
        if(no1->dados.matricula != no2->dados.matricula || no1->dados.nome != no2->dados.nome)
            break;
        return 0;
    }
    return 1;
}

Pilha_char* cria_Pilha_char(){
    Pilha_char* pi = (Pilha_char*) malloc(sizeof(Pilha_char));
    if(pi != NULL)
        *pi = NULL;
    return pi;
}

void libera_Pilha_char(Pilha_char* pi){
    if(pi != NULL){
        Elem_char* no;
        while((*pi) != NULL){
            no = *pi;
            *pi = (*pi)->prox;
            free(no);
        }
        free(pi);
    }
}

int insere_Pilha_char(Pilha_char* pi, char dado){
    if(pi == NULL)
        return 0;
    Elem_char* no = (Elem_char*) malloc(sizeof(Elem_char));
    if(no == NULL)
        return 0;
    no->dado = dado;
    no->prox = (*pi);
    *pi = no;
    return 1;
}

int remove_Pilha_char(Pilha_char* pi){
    if(pi == NULL || (*pi) == NULL)
        return 0;
    Elem_char *no = *pi;
    *pi = no->prox;
    free(no);
    return 1;
}

int consulta_topo_Pilha_char(Pilha_char* pi, char *dado){
    if(pi == NULL || (*pi) == NULL)
        return 0;
    *dado = (*pi)->dado;
    return 1;
}

int Pilha_char_vazia(Pilha_char* pi){
    if(pi == NULL || *pi == NULL)
        return 1;
    return 0;
}

void conta_par_impar(Pilha_num* pi) {
    if (Pilha_num_vazia(pi)) {
        printf("A pilha esta vazia.\n");
        return;
    }

    Pilha_num* pi_aux = cria_Pilha_num();
    int count_par = 0;
    int count_impar = 0;
    float temp_num;

    while (!Pilha_num_vazia(pi)) {
        consulta_topo_Pilha_num(pi, &temp_num);
        remove_Pilha_num(pi);
        insere_Pilha_num(pi_aux, temp_num);

        // Verifica se o número é par ou ímpar
        if ((int)temp_num % 2 == 0) {
            count_par++;
        } else {
            count_impar++;
        }
    }

    // Restaura a pilha original
    while (!Pilha_num_vazia(pi_aux)) {
        consulta_topo_Pilha_num(pi_aux, &temp_num);
        remove_Pilha_num(pi_aux);
        insere_Pilha_num(pi, temp_num);
    }

    libera_Pilha_num(pi_aux);

    printf("\n--- Contagem Par/Impar ---\n");
    printf("Numeros pares: %d\n", count_par);
    printf("Numeros impares: %d\n", count_impar);
    printf("---------------------------\n");
}

int verifica_forma(char* str) {
    Pilha_char* pi = cria_Pilha_char();
    int i = 0;

    // Empilha a parte 'x' da string
    while (str[i] != '\0' && str[i] != 'C') {
        insere_Pilha_char(pi, str[i]);
        i++;
    }

    // Verifica se o 'C' foi encontrado
    if (str[i] == '\0') {
        libera_Pilha_char(pi);
        return 0; // 'C' não encontrado
    }
    i++; // Pula o 'C'

    // Desempilha e compara com a parte 'y'
    while (str[i] != '\0' && !Pilha_char_vazia(pi)) {
        char topo_char;
        consulta_topo_Pilha_char(pi, &topo_char);
        remove_Pilha_char(pi);
        if (topo_char != str[i]) {
            libera_Pilha_char(pi);
            return 0; // Caracteres não batem
        }
        i++;
    }

    // A forma é válida se a string e a pilha terminarem ao mesmo tempo
    int resultado = (str[i] == '\0' && Pilha_char_vazia(pi));
    libera_Pilha_char(pi);
    return resultado;
}

void inverso_e_verificar(char* texto) {
    if (texto == NULL) return;

    Pilha_char* pi_char = cria_Pilha_char();
    char temp_char;
    int i = 0, j = 0;
    char texto_limpo[strlen(texto) + 1];

    printf("\nTexto na ordem inversa: ");
    for (i = 0; texto[i] != '\0'; i++) {
        insere_Pilha_char(pi_char, texto[i]);
    }

    i = 0;
    while (!Pilha_char_vazia(pi_char)) {
        consulta_topo_Pilha_char(pi_char, &temp_char);
        remove_Pilha_char(pi_char);
        printf("%c", temp_char);

        if (isalnum(temp_char)) {
            texto_limpo[j++] = tolower(temp_char);
        }
    }
    texto_limpo[j] = '\0';
    printf("\n\n");

    Pilha_char* pi_char_limpo = cria_Pilha_char();
    for (i = 0; texto_limpo[i] != '\0'; i++) {
        insere_Pilha_char(pi_char_limpo, texto_limpo[i]);
    }

    i = 0;
    int e_palindromo = 1;
    while (!Pilha_char_vazia(pi_char_limpo)) {
        consulta_topo_Pilha_char(pi_char_limpo, &temp_char);
        remove_Pilha_char(pi_char_limpo);
        if (temp_char != texto_limpo[i]) {
            e_palindromo = 0;
            break;
        }
        i++;
    }

    if (e_palindromo) {
        printf("O texto E um palindromo.\n");
    } else {
        printf("O texto NAO e um palindromo.\n");
    }

    libera_Pilha_char(pi_char);
    libera_Pilha_char(pi_char_limpo);
}

void converter_binario(int decimal) {
    Pilha_num* pi_bin = cria_Pilha_num();
    int resto;

    if (decimal == 0) {
        printf("0 em binario: 0\n");
        libera_Pilha_num(pi_bin);
        return;
    }

    while (decimal > 0) {
        resto = decimal % 2;
        insere_Pilha_num(pi_bin, resto);
        decimal = decimal / 2;
    }

    printf("Em binario: ");
    while (!Pilha_num_vazia(pi_bin)) {
        consulta_topo_Pilha_num(pi_bin, &resto);
        printf("%d", resto);
        remove_Pilha_num(pi_bin);
    }

    libera_Pilha_num(pi_bin);
}

void menu(){
    printf("1-Inicializa pilha.\n");
    printf("2-Verifica se a pilha e vazia.\n");
    printf("3-Verifica se a pilha e cheia.\n");
    printf("4-Empilha o elemento na pilha.\n");
    printf("5-Desempilha elemento da pilha.\n");
    printf("6-Le topo de um pilha.\n");
    printf("7-Converte um numero decimal em binario.\n");
    printf("8-Sair.\n");
}

int questoes(){
    int opcao;
    printf("1 - Questao 1.\n");
    printf("2 - Questao 2.\n");
    printf("3 - Questao 3.\n");
    printf("4 - Questao 4.\n");
    printf("5 - Questao 5.\n");
    printf("6 - Questao 6.\n");
    printf("7 - Questao 7.\n");
    printf("8 - Questao 8.\n");
    printf("9 - Questao 9.\n");
    printf("0 - Sair.\n\n");
    printf("Escolha uma das opcoes acima: ");
    scanf("%d", &opcao);
    return opcao;
}
