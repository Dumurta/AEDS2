#include <stdio.h>
#include <stdbool.h>
bool compararStrings(char s1[], char s2[])
{
    bool teste = false;
    int i = 0;
    while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
    {
        i++;
    }
    if (s1[i] == s2[i])
    {
        teste = true;
    }
    return teste;
}
int comprimento(char s[])

{
    int i = 0;
    while (s[i] != '\0' && s[i] != '\n')
    {
        i++;
    }
    return i;
}

char toLower(char s)
{
    char c = s;
    if (c >= 'A' && c <= 'Z')
    {
        c = (char)(c + 32);
    }
    return c;
}
bool testeVogaisRec(char string[], int i)
{
    bool teste = true;
    int tamanho = comprimento(string);
    if (i < tamanho)
    {
        char c = string[i];
        c = toLower(c);
        if (c != 'a' && c != 'e' && c != 'i' && c != 'o' && c != 'u')
        {
            teste = false;
        }
        else
        {
            teste = testeVogaisRec(string, i + 1);
        }
    }
    return teste;
}
bool testeVogais(char string[])
{
    int i = 0;
    return testeVogaisRec(string, i);
}

bool testeConsoRec(char string[], int i)
{
    bool teste = true;
    int tamanho = comprimento(string);
    if (i < tamanho)
    {
        char c = string[i];
        c = toLower(c);
        if (!(c >= 'a' && c <= 'z'))
        {
            teste = false;
        }
        else if ((c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'))
        {
            teste = false;
        }
        else
        {
            teste = testeConsoRec(string, i + 1);
        }
    }
    return teste;
}
bool testeConso(char string[])
{
    int i = 0;
    return testeConsoRec(string, i);
}

bool testeNumRec(char string[], int i)
{
    bool teste = true;
    int tamanho = comprimento(string);
    if (i < tamanho)
    {
        char c = string[i];
        if (!(c >= '0' && c <= '9'))
        {
            teste = false;
        }
        else
        {
            teste = testeNumRec(string, i + 1);
        }
    }
    return teste;
}
bool testeNum(char string[])
{
    int i = 0;
    return testeNumRec(string, i);
}

bool testeRealRec(char string[], int i, int pontos)
{
    bool teste = false;
    int tamanho = comprimento(string);
    if (i < tamanho)
    {
        char c = string[i];
        if (c == '.' || c == ',')
        {
            if (pontos < 1)
            {
                teste = testeRealRec(string, i + 1, pontos + 1);
            }
        }
        else if (c >= '0' && c <= '9')
        {
            teste = testeRealRec(string, i + 1, pontos);
        }
    }
    else
    {
        teste = (pontos == 1);
    }
    return teste;
}

bool testeReal(char string[])
{
    int i = 0;
    return testeRealRec(string, i, 0);
}
int main()
{
    char string[1000];
    bool fimEncontrado = false;

    while (!fimEncontrado && fgets(string, 1000, stdin) != NULL)
    {

        int len = comprimento(string);
        if (len > 0 && string[len - 1] == '\n')
        {
            string[len - 1] = '\0';
        }
        if (comprimento(string) >= 3 && string[0] == 'F' && string[1] == 'I' && string[2] == 'M')
        {
            fimEncontrado = true;
        }
        else
        {
            bool x1 = testeVogais(string);
            bool x2 = testeConso(string);
            bool x3 = testeNum(string);
            bool x4 = testeReal(string);

            printf("%s ", x1 ? "SIM" : "NAO");
            printf("%s ", x2 ? "SIM" : "NAO");
            printf("%s ", x3 ? "SIM" : "NAO");
            printf("%s\n", x4 ? "SIM" : "NAO");
        }
    }
    return 0;
}