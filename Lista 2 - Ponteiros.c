#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1 - Sendo p um ponteiro, qual a diferença entre:
//   • p++;
//   • (*p)++;
//   • *(p++);
//   • O que quer dizer *(p+10);

// Resposta: 

// p++: Está incrementando o ponteiro, considerando que p seja do tipo int,
// então p passa a apontar ao endereço 4 bytes a frente.

// (*p)++: Está incrementando o conteúdo que está sendo apontado, seja um
// x uma variável de valor 0, x = 0, após (*p)++ será incrementado 1 no 
// conteúdo apontado, sendo assim x passa a valer 1, x = 1.

// *(p++): Está incrementando o conteúdo que está sendo apontado, seja um
// v[] = {1, 2, 3, 4, 5} pertencente ao conjuntos dos inteiros, inicialmente
// o ponteiro estava apontando para v[0] e agora passa a apontar para v[1].

// *(p+10): Está acessando o conteúdo 10 posições na frente, no caso de
// ser um vetor de inteiros, como o int ocupa 4 bytes, ele está acessando
// o conteúdo localizados a 40 bytes a frente.  

// 2 - Escreva um comentário em cada comando de atribuição explicando o que
// ele faz e o valor da variável à esquerda do '=' após sua execução.
/* int main()
{
int y, *p, x;
y = 0; // y recebe o valor 0; y = 0
p = &y; // p passa a apontar para y; p -> y = 0
x = *p; // x recebe o conteúdo que p está apontando; x = *p -> y = 0, portanto x = 0
x = 4; // x recebe o valor 4; x = 4
(*p)++; // incrementa 1 no conteúdo de p; (*p)++ -> y++ -> y = 1 
x--; // decrementa o valor de x; x = 3
(*p) += x; // Adiciona ao conteúdo apontado o valor de x; p -> y = 4
printf ("y = %d\n", y); 
return(0);
}  */

// 3 - Verifique o programa abaixo. Encontre o seu erro e corrija-o para que
// escreva o número 10 na tela.
/* #include <stdio.h>
int main() {
 int x, *p, **q;
 p = &x;
 q = &p;
 x = 10;
 printf("\n%d\n", &q);
 return(0);
} */

// Resposta: 
/* #include <stdio.h>
int main() {
 int x, *p, **q;
 p = &x;
 q = &p;
 x = 10;
 printf("\n%d\n", **q); // Foi retirado "&" e adicionado "**" para imprimir o conteúdo de q
 return(0);
} */

// 4 - Crie um vetor V com n inteiros, onde n é um valor inteiro fornecido pelo
// usuário. O vetor só deve ser alocado na memória depois que o usuário
// fornecer o valor de n

/* 
int main() {
    int n, *V;
    scanf("%d", &n);
    V = (int *) malloc(sizeof(int) * n);
    return 0;
}
 */

/* 5 - Crie um programa para manipular vetores com ponteiros. O seu programa
deve implementar uma função chamada inverte_vetor, que recebe como
parâmetro dois vetores V1 e V2, ambos de tamanho N. A função deve copiar
os elementos de V1 para V2 na ordem inversa. Ou seja, se a função receber
V1 = {1,2,3,4,5}, a função deve copiar os elementos para V2 na seguinte
ordem: V2 = {5,4,3,2,1}. Além disso, a função também deve retornar o maior
valor encontrado em V1. A função deve obedecer ao seguinte protótipo: int
inverte_vetor(int *v1, int *v2, int n). */

/* int inverte_vetor(int *v1, int *v2, int n) {
    int maior_valor = v1[0];
    if (n <= 0) return 0; 

    for (int i = 0; i < n; i++) {
        v2[n - 1 - i] = v1[i];
        if (v1[i] > maior_valor) maior_valor = v1[i];
    }
    return maior_valor;
}

int main() {
    int n, *v1, *v2;
    
    printf("Digite o tamanho: \n");
    scanf("%d", &n);

    v1 = (int *) malloc(sizeof(int) * n);
    v2 = (int *) malloc(sizeof(int) * n);

    printf("Digite os valores: \n");
    for(int i = 0; i < n; i++) scanf("%d", &v1[i]);

    printf("Antes da inversao:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", v1[i]);
    }
    int maior_valor = inverte_vetor(v1, v2, n);
    printf("\nDepois da inversao:\n");
    for(int i = 0; i < n; i++) {
        printf("%d ", v2[i]);
    }
    printf("\nMaior valor: %d", maior_valor);

    free(v1);
    free(v2);
    return 0;
} */

/* 6- Escreva um programa em linguagem C que imprimam na tela a string s na
ordem inversa utilizando ponteiros.
char s[10] = "abcde";
char* cptr;
// Seu código começa aqui
        printf("String antes: %s\n", s);
        int tamanho = strlen(s); // Recebe o tamanho de string, nesse caso 5
        cptr = s + tamanho - 1; // O ponteiro passa a apontar para a última posição de s, - 1 para ser a posição anterior ao \0; cptr aponta para s[4] que tem o caractere "e"
        printf("String depois: ");
        while(cptr >= s) { // Enquanto não 
            printf("%c", *cptr); // Imprime o último caractere
            cptr--; // Vai para caractere anterior
        }
        return 0; // Considerei que estava dentro da main
    }
 */

/* 7- Escrever um programa que cadastre vários produtos em uma
estrutura/registro. Em seguida, imprima uma lista com o código e nome da
cada produto. Por último, consulte o preço de um produto através de seu
código

typedef struct { // Criada a struct
    char nome[255];
    int codigo;
    float preco;
} Produto;

int main() {
    int opcao, qtd = 0; // opcao para o do-while e qtd para quantidade de produtos cadastrados
    Produto *prod = (Produto *) malloc(sizeof(Produto)); // Instancia a struct e aloca ela dinâmicamente

    do {
        printf("\n1 - Cadastrar produto\n");
        printf("2 - Lista de produtos\n");
        printf("3 - Pesquisar preco do produto\n");
        printf("0 - Sair\n -----\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        switch(opcao) {
            case 1: {
                Produto *temp = realloc(prod, sizeof(Produto) * (qtd + 1)); 
                prod = temp;
                printf("Digite o nome do produto: ");
                scanf(" %[^\n]s", prod[qtd].nome);
                prod[qtd].codigo = qtd + 1; // Código do produto é a qtd + 1, pois o primeiro produto inicia com 1 como código, mas a qtd inicial é 0
                printf("Codigo do produto: %d\n", prod[qtd].codigo);
                printf("Digite o preco do produto: R$ ");
                scanf("%f", &prod[qtd].preco);
                qtd++; // Incrementa a quantidade de produtos
                break;
            }
            case 2:
                printf("Lista de produtos\n\n"); // Lista todos os produtos cadastrados
                for(int i = 0; i < qtd; i++) {
                    printf("Produto: %s\nCodigo: %d\n -----\n", prod[i].nome, prod[i].codigo);
                }
                break;
            case 3: {
                int codigo;
                printf("\nDigite o codigo do produto: ");
                scanf("%d", &codigo);
                if(qtd > 0) {
                    for(int i = 0; i < qtd; i++) {
                        if(codigo == prod[i].codigo) { // Compara o codigo digitado com cada codigo cadastrado
                            printf("O preco do produto %s: R$ %.2f", prod[i].nome, prod[i].preco);
                            break;
                        }
                    }
                } else {
                    printf("Nao tem produtos cadastrados!\n");
                }
                break;
            }
            case 0:
                break;
            default:
                printf("Tente novamente!\n");
                break;
        }
    } while (opcao != 0);
    free(prod); // Libera a área da memória alocada
    return 0;
} */

/* 8- Faça um programa que leia um valor n e crie dinamicamente um vetor de n
elementos e passe esse vetor para uma função que vai ler os elementos
desse vetor. Depois, no programa principal, o vetor preenchido deve ser
impresso. Além disso, antes de finalizar o programa, deve-se liberar a área
de memória alocada

void ler_vetor(int vetor[], int n) {
    for(int i = 0; i < n; i++) { // Percorre o vetor preenchendo cada elemento e imprimindo em seguida
        vetor[i] = i + 1;
        printf("%d ", vetor[i]);
    }
}

int main() {
    int *vetor, n;
    printf("Digite o tamanho do vetor: ");
    scanf("%d", &n);
    vetor = (int *) malloc(sizeof(int) * n); // Aloca o vetor
    printf("\nElementos do vetor: \n");
    ler_vetor(vetor, n); // Chama a função que ler, preenche e imprime (tudo em um)
    free(vetor); // Libera a área da memória alocada
    return 0;
} */

int **criar_matriz(int m, int n) {
    int **matriz = (int **) malloc(sizeof(int *) * m);
    if (matriz == NULL) return NULL; // Para caso ocorrar erro

    for (int i = 0; i < m; i++) {
        matriz[i] = (int *) malloc(sizeof(int) * n);
        if(matriz[i] == NULL) {
            for (int k = 0; k < i; k++) free(matriz[k]);
            free(matriz);
            return NULL; // Caso ocorrar erro ao alocar
        }
    }
    return matriz;
}

void preencher_matriz(int **matriz, int m, int n) {
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            matriz[i][j] = i + j; // Preenche e imprime o valor de cada posição da matriz
            printf("%d\t", matriz[i][j]); // Tabulação para ficar bonito
        }
        printf("\n"); // Só para ficar no formato da matriz m x n
    }
}

void liberar_memoria(int **matriz, int m) {
    for (int i = 0; i < m; i++){
        free(matriz[i]); // Libera a memória de cada linha
    }
    free(matriz); // Libera da coluna, o ponteiro principal
}

int main() {
    int m, n;
    int **matriz;

    printf("Digite o valor m e n da matriz: ");
    scanf("%d %d", &m, &n);

    matriz = criar_matriz(m, n);
    if(matriz == NULL) {
        printf("Erro ao alocar");
        return 1; // Caso não tenha alocado retorna um código de erro
    }

    preencher_matriz(matriz, m, n);
    liberar_memoria(matriz, m);

    return 0;
}