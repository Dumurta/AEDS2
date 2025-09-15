package AEDS2.tarefas.labs;
import java.util.Scanner;
public class GridF1 {
    public static int ultrapassagem(int[] chegada, int[] largada)
    {

        int tamanho = chegada.length;
        int ultrapassagem = 0;
        for(int i = 0; i < tamanho; i++)
        {
            int posicaoLargadaAtual = -1;
            for(int j = 0; j < tamanho; j++)
            {
                if (largada[j] == chegada[i]) {
                    posicaoLargadaAtual = j;
                    j = tamanho;
                }
            }

            int posicaoLargadaAnterior = -1;
            for (int j = 0; j < i; j++) {
                for (int k = 0; k < tamanho; k++) {
                    if (largada[k] == chegada[j]) {
                        posicaoLargadaAnterior = k;
                        k = tamanho;
                    }
                }
            }
            if(posicaoLargadaAtual > posicaoLargadaAnterior)
            {
                ultrapassagem ++;
            }
        }

        return ultrapassagem;
    }


    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        //entrada
        int n = sc.nextInt();
        int[] laragada = new int[n];
        int[] chegada = new int[n];
        while(sc.hasNext()){
            for(int i = 0; i < n; i++ )
            {   if(sc.hasNextInt()){
                    laragada[i] = sc.nextInt();
                }
            }
            for(int i = 0; i < n; i++ )
            {
                if(sc.hasNextInt()){
                    chegada[i] = sc.nextInt();
                }
            }
            System.out.println(ultrapassagem(chegada, laragada));
            n = sc.nextInt();

        }
        sc.close();
     }
}
