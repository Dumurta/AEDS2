import java.util.Scanner;
public class VerificadorAnagrama {

/**
 * Metodo iterativo que verifica se duas strings sao anagramas
 * Utiliza array de frequencia para contar ocorrencias de cada letra
 * @param s1 primeira string a ser comparada
 * @param s2 segunda string a ser comparada
 * @return true se as strings sao anagramas, false caso contrario
 */
public static boolean ehAnagrama(String s1, String s2)
{
	// Variavel para armazenar o resultado final da verificacao
	boolean teste = true;
	
	// Se os tamanhos sao diferentes, nao e' anagrama
	if(s1.length() != s2.length()){
		teste = false;
	}
	
	// Array para contar frequencia de cada letra do alfabeto a-z
	int[] contador = new int[26];
	
	// Primeiro loop: percorre primeira string e incrementa contador para cada letra
	for(int i = 0; i < s1.length(); i++)
	{
		char c = s1.charAt(i);
		
		// Converte letra maiuscula para minuscula
		if(c >= 'A' && c <= 'Z')
		{
			c = (char) (c + 32); 
		}
		
		/*
		 * Pra cada posicao do array, temos uma letra do alfabeto,
		 * esse IF verifica se o caractere em questao faz parte do alfabeto
		 * e com a operacao [c - 'a'] ele cria o valor de 1 na posicao da letra
		 * c dentro do array, por exemplo se c - 'a' = 25, logo temos Z no array
		 */
		if(c >= 'a' && c <= 'z')
		{
			contador[c - 'a']++; // Incrementa contador na posicao correspondente a letra
		}
	}
	
	/*Mesmo for mas agora fazendo -1 ao inves de +1, caso no final
	 * meu array contador tenha 0 em todas posicoes, as strings sao
	 * Anagramas
	 */
	// Segundo loop: percorre segunda string e decrementa contador para cada letra
	for(int i = 0; i < s2.length(); i++)
	{
		char c = s2.charAt(i);
		
		// Converte maiuscula para minuscula se necessario
		if(c >= 'A' && c <= 'Z')
		{
			c = (char) (c + 32);
		}
		
		// Decrementa contador apenas para letras validas do alfabeto
		if(c >= 'a' && c <= 'z')
		{
			contador[c - 'a']--; //decrementa do contador
		}
	}
	
	// Terceiro loop: verifica se todos os contadores estao zerados
	// Se algum contador nao for zero, as strings nao sao anagramas
	for(int i = 0; i < 26; i++)
	{
		if(contador[i] != 0)
		{
			teste = false; // Encontrou diferenca, nao sao anagramas
		}
	}
	
	return teste;
}

/**
 * Metodo iterativo que separa uma linha em duas palavras usando hifen como delimitador
 * Processa caractere por caractere para extrair as duas palavras
 * @param linha string contendo duas palavras separadas por hifen
 * @return array de strings contendo as duas palavras separadas
 */
public static String[] separarPalavra(String linha)
{
	// Strings para armazenar primeira e segunda palavra
	String p1 = "";
	String p2 = "";
	
	boolean encontrouHifen = false;
	
	for(int i = 0; i<linha.length(); i++)
	{
		char c = linha.charAt(i);
		
		// Se encontrar hifen e ja tiver caracteres na primeira palavra
		if(c == '-' && p1.length() > 0)
		{
			encontrouHifen = true; // Marca que encontrou o separador
		}
		else{
			// Se ainda nao encontrou hifen, adiciona caractere a primeira palavra
			if(!encontrouHifen)
			{
				p1 += c;
			}
			// Se ja encontrou hifen, adiciona caractere a segunda palavra
			else{
				p2 += c;
			}
		}
	}
	
	return new String[]{p1, p2}; //nao encontrei metodos melhores de dar esse return com new
}

/**
 * Metodo principal que le linhas de entrada ate encontrar "FIM"
 * Para cada linha, separa as palavras e verifica se sao anagramas
 * Imprime "SIM" se forem anagramas ou "NAO" caso contrario
 */
public static void main(String[] args) {
	Scanner sc = new Scanner(System.in);
	String linha = sc.nextLine();
	while (!(linha.length() >= 3 && linha.charAt(0) == 'F' && linha.charAt(1) == 'I' && linha.charAt(2) == 'M'))
	{
		String[] palavras = separarPalavra(linha);
		if (palavras.length >= 2) {
			if (ehAnagrama(palavras[0], palavras[1])) {
				System.out.println("SIM");
			} else {
				System.out.println("NÃO");
			}
		}
		linha = sc.nextLine();
	} 
	sc.close();
}
}