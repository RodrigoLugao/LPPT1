#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


//função que verifica se um número é primo
int primo(int n) {
    int i;
    if (n <= 1) return 0;
    if (n == 2) return 1;
    if (n % 2 == 0) return 0;
    for (i = 3; i <= sqrt(n); i += 2) { //se não for menor ou igual a um, 2 ou par, percorre todos os numeros de 3 até a raíz quadrada do número e verifica o resto
        if (n % i == 0) return 0; // caso não tenha resto, retorna falso
    }
    return 1; //caso contrario, retorna verdadeiro
}

int main(int argc, char *argv[]) {
    int i, cont = 0, n;
    clock_t inicio, fim; //guardam o momento do inicio e do fim
    double tempo;

    if (argc < 2) {
        printf("Entre com o valor do maior inteiro como parâmetro.\n");
        return 0;
    } else {
        n = strtol(argv[1], (char **)NULL, 10);
    }

    inicio = clock();

    // Conta o número 2 separadamente
    if (n >= 2) cont++;

    // Percorre todos os número verificando qual é primo
    for (i = 3; i <= n; i += 2) {
        if (primo(i)) cont++;
    }

    fim = clock();
    tempo = (double)(fim - inicio) / CLOCKS_PER_SEC; 

    printf("Quantidade de primos entre 1 e %d: %d\n", n, cont);
    printf("Tempo de execucao: %1.3f segundos\n", tempo);

    return 0;
}
