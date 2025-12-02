#include <stdio.h>
#include <stdlib.h>

/**
 * Para conseguir pegar o último digito, multiplica por dez e o resto da divisão
 * será o último digito. Exemplo: 123 / 10, o resto dessa divisão é 3.
 * O último digito será guardado e será adicionado no valor parcial ate que a
 * condição seja atingida. Enquanto a condição não for atingida o valor parcial
 * será multiplicado por dez a somado com o último digito. Exemplo: 0 * 10 + 3 = 3.
 * Depois a função é chamada novamente com o número divido por dez. 
 * 123 % 10 = 3 -> 0 * 10 + 3 = 3 -> 123 / 10 = 12 -> 12 % 10 = 2 -> 3 * 10 + 2 = 32 ->
 * 12 / 10 = 1 -> 1 % 10 = 1 -> 32 * 10 + 1 = 321.
 */
int inverter_num(int num, int inverso_parcial) {
    if(num == 0) {
        return inverso_parcial;
    } else {
        // Pega o último dígito do número atual
        int ultimo_digito = num % 10;
        // Adiciona o último dígito ao final do inverso
        int inverso_atual = inverso_parcial * 10 + ultimo_digito;
        // Chama a função novamente com o número sem o último dígito
        return inverter_num(num / 10, inverso_atual);
    }
}

/**
 * Caso inicial é se o tamanho for <= 0 retorna 0, pois o vetor não pode haver tamanho 0
 * ou negativo. Vai iniciar somando o último elemento do vetor e na próxima chamada
 * chama a função com o tamanho - 1 até que o tamanho seja 0.
 */
int soma_elementos_vetor(int vetor[], int tamanho) {
    if(tamanho <= 0) {
        return 0; // Caso base
    } else {
        return vetor[tamanho - 1] + soma_elementos_vetor(vetor, tamanho - 1); // Soma o elemento da última casa com o penúltimo até chegar na vetor[0]
    }
}

/**
 * Caso base é se for o número for menor ou igual a zero para evitar números negativos,
 * se não vai para o passo recursivo que soma o número e chama a função recursiva
 * novamente com o número anterior a ele (n - 1).
 */
int somatorio_um_a_n(int num) {
    if(num <= 0) {
        return 0; // Caso base
    } else {
        return num + somatorio_um_a_n(num - 1); // Soma com o próximo termo
    }
}

/**
 * Os dois primeiros casos, para quando k for igual a zero retorna 0, toda potencia de 0 é 0,
 * para quando n for igual a 0 retorna 1, todo número elevado a 0 é igual a 1. Para as chamadas recursivas,
 * quando n for maior que zero a irá retorna k * k elevado n-1, mas se n for negativo ficará 1/k^n,
 * devido a regra de quando o expoente for negativo apenas inverte a base e o expoente fica positivo.
 * A função é um float para caso o expoente for negativo, pois assim o resultado será um número
 * pertencente ao conjunto dos números racionais.
 */
float k_elevado_a_n(int k, int n) {
    if(k == 0) return 0; // 0 ^ n = 0
    if(n == 0) return 1; // Caso base: Todo número elevado a 0 é 1
    if(n > 0) {
        return k * k_elevado_a_n(k, n - 1); // k * próximo termo até chegar no caso base
    } else {
        return 1 / k_elevado_a_n(k, -n); // Caso para n negativo: inverte a base e troca o sinal do expoente
    }
}

/**
 * Para gerar os números do exercício 5. Ele gera o número, adiciona no vetor e vai para vai para a
 * próxima "casa" do vetor de forma recursiva.
 */
void gerar_numero(float vetor[], int i, int tamanho) {
    if(i < tamanho) {
        vetor[i] = (double)rand() / RAND_MAX * 100.0;
        gerar_numero(vetor, i + 1, tamanho);
    }
}

/**
 * Inverte a ordem do primeiro e último valor do vetor. Na próxima chamada ele avança uma posição
 * do ínicio e retrocede uma do fim até que ínicio seja menor que o fim, ai para.
 */
void inverter_ordem(float vetor[], int inicio, int fim) {
    if (inicio < fim) {
        float temp = vetor[inicio];
        vetor[inicio] = vetor[fim];
        vetor[fim] = temp;
        inverter_ordem(vetor, inicio + 1, fim - 1);
    }
}

/**
 * Apenas para imprimir o vetor. A cada dez número quebra uma linha.
 */
void imprimir_vetor(float vetor[], int i, int tamanho) {
    if(i < tamanho) {
        printf(" %.2f ", vetor[i]);
        // Quando o índice for multiplo de 10 ele quebra a linha. 
        // É apenas para deixar um pouco organizado.
        if ((i + 1) % 10 == 0) {
            printf("\n"); // Quebra linha quando imprime 10 números
        }
        imprimir_vetor(vetor, i + 1, tamanho); // Já que o tema da lista é recursividade, por que não fazer essa função de forma recursiva também?
    }
}

/**
 * Calcular o mdc de dois números.
 */
int mdc(int a, int b) {
    if(b == 0) {
        return a; // Caso base
    } else {
        return mdc(b, a % b); // Verifica o MDC do próximo caso
    }
}

/**
 * Em parte é usada a mesma lógica da função do exercício 1, caso o número inicial seja 0 então retorna 0 (obviamente pq não tem
 * nenhuma ocorrência, a não seja que o digito seja 0), caso contrário retorna a função mais 1 se tiver o digito for igual
 * o último número, caso contrário novamente apenas retorna a função para verificar o próximo dígito.
 */
int contador_de_ocorrencias(int numero, int digito) {
    if(numero == 0 && digito == 0) return 1; // Caso base
    int ultimo_digito = numero % 10; // Divide por dez para conferir o próximo dígito
    if(ultimo_digito == digito) {
        return 1 + contador_de_ocorrencias(numero / 10, digito); // Incrementa 1 no contador de ocorrências
    } else {
        return contador_de_ocorrencias(numero / 10, digito); // Passa para o próximo número
    }
}

int Multi_Rec(int n1, int n2) {
    if(n1 == 0 || n2 == 0) {
        return 0; // Todo número multiplica por zero é zero
    } else {
        return n1 + Multi_Rec(n1, n2 - 1); // Soma o número com ele mesmo até n2 for zero
    }
}

int pares_crescente(int num) {
    if(num < 0) return 0; // Caso base: imprime apenas zero caso seja negativo
    pares_crescente(num - 2); // Confere o próximo número, a condição para imprimir é depois porque na volta vai imprimindo, assim fica na forma crescente
    if(num % 2 == 0) { // Quando satisfeita, imprime o número
        printf("%d ", num);
    }
    return 0;
}

int positivos_n_a_zero(int num) {
    if(num < 0) return 0; // Caso base: imprime apenas zero caso seja negativo
    printf("%d ", num); // Imprime primeiro depois vai para o próximo termo para ficar na ordem decrescente
    return positivos_n_a_zero(num - 1); 
}

int pares_decrescente(int num) { // Praticamente a mesma coisa que a pares_crescente, a diferença é que imprime primeiro pra deixar na forma decrescente
    if(num < 0) return 0; 
    if(num % 2 == 0) {
        printf("%d ", num);
    }
    return pares_decrescente(num - 1);
}

/**
 * Input: 5
 * 5 não é multiplo de dois (portanto não é par) e não é menor/igual a zero
 * então ficar 5 * fat_duplo(5 - 2) -> fat_duplo de 3 * fat_duplo(3 - 2) -> 1 * fat_duplo(1 - 2) -> retorna 1.
 * Output: 1 * 1 * 3 * 5 == 15.
 */
int fat_duplo(int num) {
    if(num % 2 == 0) return 0; // Caso seja positivo retorna 0 e finaliza a função.
    if(num <= 1) return 1; // Caso base: se for menor ou igual a zero retorna 1.
    return num * fat_duplo(num - 2); // Passo recursivo: multiplica o número com o resultado da função
}

int main() {
    int num;

    printf("*** Lista 1 - Recursividade ***\n");
    printf("1 - Inverter um numero\n");
    printf("2 - Somar elementos de um vetor\n");
    printf("3 - Somatorio de 1 ate N\n");
    printf("4 - K elevado a N (potencia)\n");
    printf("5 - Inverter ordem de um vetor de tamanho 100\n");
    printf("6 - MDC de dois numeros\n");
    printf("7 - Ocorrencias\n");
    printf("8 - Multiplicação recursiva\n");
    printf("9 - Pares em ordem crescente\n");
    printf("10- Numeros em ordem decrescente\n");
    printf("11- Pares em ordem decrescente\n");
    printf("12- Fatorial de impares\n");
    printf("0 - Sair\n");
    printf("-------------------------------------\n");
    printf("Escolha uma das opcoes acima: ");


    int opcao;
    do {
        scanf("%d", &opcao);
        switch(opcao) {
            case 0:
                exit(0);
                break;
            case 1:
                printf("Digite um número: \n");
                scanf("%d", &num);
                int inverso = inverter_num(num, 0);
                printf("O inverso: %d", inverso);
                break;
            case 2: {
                int tamanho, *vetor;
                printf("Digite o tamanho do vetor: \n");
                scanf("%d", &tamanho);
                vetor = (int *) malloc(sizeof(int) * tamanho);
                for(int i = 0; i < tamanho; i++) {
                    printf("Digite valor %d: ", i + 1);
                    scanf("%d", &vetor[i]);
                }
                printf("O valor da soma do elementos do vetor: %d", soma_elementos_vetor(vetor, tamanho));
                free(vetor);
                break;
            }
            case 3: {
                int num;
                printf("Digite um numero: ");
                scanf("%d", &num);
                printf("A soma de 1 a %d: %d", num, somatorio_um_a_n(num));
                break;
            }
            case 4: {
                int k, n;
                printf("Digite o valor da base e do expoente: ");
                scanf("%d %d", &k, &n);
                printf("O valor da potencia da base %d elevado a %d: %.3f", k, n, k_elevado_a_n(k, n));
                break;
            }
            case 5: {
                float tamanho = 100;
                float *vetor = (float *) malloc(sizeof(float) * tamanho);
                gerar_numero(vetor, 0, tamanho);
                printf("Ordem antes de inverter: ");
                imprimir_vetor(vetor, 0, tamanho);
                inverter_ordem(vetor, 0, tamanho - 1);
                printf("\nOrdem depois de inverter: ");
                imprimir_vetor(vetor, 0, tamanho);
                free(vetor);
                break;
            }
            case 6: {
                int a, b;
                printf("Digite um numero a e b: ");
                scanf("%d %d", &a, &b);
                printf("O MDC de %d e %d: %d", a, b, mdc(a, b));
                break;
            }
            case 7: {
                long int numero;
                int digito;
                printf("Digite um numero: ");
                scanf("%ld", &numero);
                printf("Digite o digito que deseja ver quantas vezes ocorre: ");
                scanf("%d", &digito);
                printf("O digito %d ocorre %d vezes no numero %ld", digito, contador_de_ocorrencias(numero, digito), numero);
                break;
            }
            case 8: {
                int n1, n2;
                printf("Digite os dois numeros: ");
                scanf("%d %d", &n1, &n2);
                printf("Resultado da multiplicacao: %d", Multi_Rec(n1, n2));
                break;
            }
            case 9: {
                int num;
                printf("Digite um numero: ");
                scanf("%d", &num);
                pares_crescente(num);
                break;
            }
            case 10: {
                int num;
                printf("Digite um numero: ");
                scanf("%d", &num);
                positivos_n_a_zero(num);
                break;

            }
            case 11: {
                int num;
                printf("Digite um numero: ");
                scanf("%d", &num);
                pares_decrescente(num);
                break;
            }
            case 12: {
                int num;
                printf("Digite um numero: ");
                scanf("%d", &num);
                printf("Fatorial duplo do numero digitado: %d", fat_duplo(num));
                break;
            }
            default:
                printf("Opcao invalida! Tente novamente.\n");
                break;
        }
    } while(!opcao);
    return 0;
}