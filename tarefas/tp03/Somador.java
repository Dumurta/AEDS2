import java.util.Scanner;
public class Somador {
    public static int SomarArray(int n)
    {
        int soma = 0;

        while(n != 0)
        {
            soma += n % 10; //pega o ultimo digito

            n = n / 10; //remove o ultimo digito
        }

        return soma;
    }
    public static void main(String[] args) {
        int numero;
        Scanner sc = new Scanner(System.in);

        while(sc.hasNextInt())
        {
            numero = sc.nextInt();
            int resultado = SomarArray(numero);
            System.out.println(resultado);
        }

        sc.close();
        
    }
}
