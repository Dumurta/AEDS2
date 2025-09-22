#include <stdio.h>

void bubbleSort(int arr[], int n)
{
    int i, j, temp;

    // Percorre o vetor várias vezes
    for (i = 0; i < n - 1; i++)
    {
        // Últimos i elementos já estarão no lugar correto
        for (j = 0; j < n - i - 1; j++)
        {
            // Se o elemento atual for maior que o próximo, troca
            if (arr[j] > arr[j + 1])
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main()
{
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Vetor original:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    bubbleSort(arr, n);

    printf("\n\nVetor ordenado com Bubble Sort:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n");
    return 0;
}
