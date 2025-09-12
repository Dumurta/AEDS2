/**
 * Eduardo Murta De Abreu - 884985
 */
import java.util.Random;
import java.util.Scanner;

public class Aleatorio {

    /**
     * Funcao que recebe uma string e substitui todas as
     * ocorrencias de uma letra sorteada por outra letra sorteada
     * usando numeros aleatorios gerados pela classe Random
     * @param s1
     * @param gerador
     * @return string modificada
     */
    public static String trocarLetras(String s1, Random gerador){
        String resultado = "";

        // sorteio das duas letras
        char l1 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));
        char l2 = (char) ('a' + (Math.abs(gerador.nextInt()) % 26));

        // percorre a string original e substitui as ocorrencias
        for(int i = 0; i < s1.length(); i++) {
            char c = s1.charAt(i);

            if(c == l1){
                resultado += l2;    // troca a letra sorteada pela nova
            }
            else{
                resultado += c;     // mantem o caractere original
            }
        }

        return resultado;
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        Random gerar = new Random();

        gerar.setSeed(4); // fixa a semente para garantir repetibilidade

        String linha = scanner.nextLine();

        // SUPER condicao que continua lendo enquanto a entrada nao for "FIM"
        while (!(linha.length() >= 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M')) {
            String moddedString = trocarLetras(linha, gerar);
            System.out.println(moddedString);

            linha = scanner.nextLine();
        }

        scanner.close();
    }
}
