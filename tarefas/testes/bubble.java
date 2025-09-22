package testes;
import java.util.Scanner;  
public class bubble{
    public static void bolhasort(int[] array, int n)
    {
        int i,j,temp;
        // percorre todo o array varias vezes
        for(i = 0; i < (n-1); i++){
            //ultimos i elementos estao ordenados
            for(j = 0; j < (n - i - 1); j++)
            {
                //se o elemento array[j] for maior q o proximo faz a troca.
                if(array[j] > array[j+1])
                {
                    temp = array[j];
                    array[j] = array[j + 1];
                    array[j + 1] = temp;
                }
            }
        }
    }

    public static void main(String[] args) {
        int[] arr = {64, 34, 25, 12, 22, 11, 90};
        int n = arr.length;

            System.out.println("Array original:");
            for(int i = 0; i < n; i++) {
                System.out.print(arr[i] + " ");
            }
            System.out.println();

            bolhasort(arr, n);

            System.out.println("Array ordenado:");
            for(int i = 0; i < n; i++) {
                System.out.print(arr[i] + " ");
            }
            System.out.println();
    }
}