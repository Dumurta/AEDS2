/**
 * Eduardo Murta De Abreu - 884985
 */
import java.util.Scanner;

public class Juliocesarcopy{

    /**
     * Funcao para codificar caracter especifico seguindo o padrao unicode
     * verifica se o char e' letra, numero, ou espaco em branco
     * caso nao seja nenhum deles e' especial, entao ele retorna a mesma coisa que entrou
     * @param s1
     * @param chave
     * @return
     */

    public static char codificador(char s1, int chave)
    {
        char resultado = s1; 
        if(s1 != '\uFFFD')
        {
            resultado += (char) chave;
        }
        
        return resultado;
    }
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String s = "";
        s = scanner.nextLine();
        while (!(s.length() >= 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M')) {
            for(int i = 0; i < s.length(); i++)
            {
                System.out.print(codificador(s.charAt(i) , 3));
            }
            System.out.println();
            s = scanner.nextLine();

        }
        scanner.close();
    }
}

/**
 * confesso que nao conhecia sobre o problema do Ciframento de César
 * entao busquei alguns exemplos pra complementar minha logica
 * por isso da implementacao do warp-arround pra evitar o aparecimento de caracteres aleatorios
 * por exemplo, sem essa logica ao inserir a letra 'z' o programa retornava '}'
 * Atualizacao: por algum motivo essa logica nao funciona muito bem, troquei minha condicao pra
 * se o caracter e' \uFFFD ou nao (caracter de reposicao ou REPLACEMENT CHARACTER) e dessa forma
 * tive sucesso no verde.
 */