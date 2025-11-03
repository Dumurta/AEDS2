#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Atleta
{
    int peso;
    char nome[51];
} Atleta;

int main()
{

    int n = 0;

    scanf("%d", &n);

    Atleta listaAtletas[n];

    for (int i = 0; i < n; i++)
    {
        scanf("%s %d", listaAtletas[i].nome, &listaAtletas[i].peso);
    }

    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - 1; j++)
        {
            Atleta atletaEsq = listaAtletas[j];
            Atleta atletaDir = listaAtletas[j + 1];
            if (atletaEsq.peso < atletaDir.peso)
            {
                Atleta temp = listaAtletas[j];
                listaAtletas[j] = listaAtletas[j + 1];
                listaAtletas[j + 1] = temp;
            }
            else if (atletaEsq.peso == atletaDir.peso && strcmp(atletaEsq.nome, atletaDir.nome) > 0)
            {
                Atleta temp = listaAtletas[j];
                listaAtletas[j] = listaAtletas[j + 1];
                listaAtletas[j + 1] = temp;
            }
        }
    } // end bubbleSort

    for (int i = 0; i < n; i++)
    {
        printf("%s %d\n", listaAtletas[i].nome, listaAtletas[i].peso);
    }

    return 0;
}
