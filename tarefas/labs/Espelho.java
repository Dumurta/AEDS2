package AEDS2.tarefas.labs;
import java.util.Scanner;

/*Descricao do problema
 * Imprimir números em sequência é uma tarefa relativamente simples. Mas, e quando se trata de uma sequência espelho? Trata-se de uma sequência que possui um número de início e um número de fim, e todos os números entre estes, inclusive estes, são dispostos em uma sequência crescente, sem espaços e, em seguida, esta sequência é projetada de forma invertida, como um reflexo no espelho. Por exemplo, se a sequência for de 7 a 12, o resultado ficaria 789101112211101987.
Escreva um programa que, dados dois números inteiros, imprima a respectiva sequência espelho.
 */
public class Espelho {
    public static String toStringBoa(int[]array)
    {
        String resultado = "";
        for(int i = 0; i < array.length; i++)
        {
            resultado = resultado + array[i];
        }

        return resultado;
    }

    public static String Espelhar(int n1, int n2){
        int tamanho = n2 - n1 + 1;
        int[] arr = new int[tamanho];
        int indice = 0;
        for (int num = n1; num <= n2; num++) {
            arr[indice] = num;
            indice++;
        }
        String parteOriginal = toStringBoa(arr);
        String parteRevertida = "";
        for (int i = parteOriginal.length() - 1; i >= 0; i--) {
            parteRevertida = parteRevertida + parteOriginal.charAt(i);
        }
        return parteOriginal + parteRevertida;
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        while(sc.hasNextInt()){
            int n1 = sc.nextInt();
            int n2 = sc.nextInt();
            String resultado = Espelhar(n1,n2);
            System.out.println(resultado);
        }
        sc.close();
    } 
}
