#include <stdio.h>
#include <stdbool.h>

// calcula o tamanho da string
int comprimento(char s[])
{
    int i = 0;
    while (s[i] != '\0' && s[i] != '\n')
    {
        i++;
    }
    return i;
}

// compara duas strings
bool compararStrings(char s1[], char s2[])
{
    bool iguais = true;
    int i = 0;

    while (s1[i] != '\0' && s1[i] != '\n' && s2[i] != '\0')
    {
        if (s1[i] != s2[i])
        {
            iguais = false;
        }
        i++;
    }

    if (s2[i] != '\0')
    {
        iguais = false;
    }

    return iguais;
}

// verifica recursivamente se a string e' palindromo
int ehPalindromoRecursivo(char s[], int i, int j)
{
    int resultado = 1;

    if (i >= j)
    {
        resultado = 1;
    }
    else
    {
        if (s[i] == s[j])
        {
            resultado = ehPalindromoRecursivo(s, i + 1, j - 1);
        }
        else
        {
            resultado = 0;
        }
    }

    return resultado;
}

// funcao principal para verificar palindromo
bool ehPalindromo(char s[])
{
    int tam = comprimento(s);
    bool resposta = true;

    if (tam > 0)
    {
        resposta = ehPalindromoRecursivo(s, 0, tam - 1);
    }
    else
    {
        resposta = false;
    }

    return resposta;
}

int main()
{
    char string[100];

    fgets(string, 100, stdin);

    while (!compararStrings(string, "FIM"))
    {
        bool resultado = ehPalindromo(string);

        if (resultado)
        {
            printf("SIM\n");
        }
        else
        {
            printf("NAO\n");
        }

        fgets(string, 100, stdin);
    }

    return 0;
}
