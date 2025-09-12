#include <stdio.h>
/**
 * nao consegui pensar em outra maneira mais simples que essa pra
 * resolver o problema e usar apenas um return na funcao
 * a minha funcao soma digitos recebe N e com n % 10 retorna o ultimo
 * digito de N, e n / 10 remove o ultimo digito de n. A recursividade
 * faz isso ate 0 e retorna a soma dos valores retirados.
 */
int somaDigitos(int n)
{
    return (n == 0) ? 0 : (n % 10) + somaDigitos(n / 10);
}

int main()
{
    int numero;

    while (scanf("%d", &numero) == 1)
    {
        int resultado = somaDigitos(numero);
        printf("%d\n", resultado);
    }

    return 0;
}