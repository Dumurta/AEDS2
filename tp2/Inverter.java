
import java.util.Scanner;

public class Inverter {
    public static String inverteString(String s1)
    {
        String s2 = "";
        int tamanho = s1.length() - 1;
        while (tamanho >= 0)
        {
            s2 += s1.charAt(tamanho);
            tamanho--;
        }
        return s2;
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = "";
        s = sc.nextLine();

        while (!(s.length() >= 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M')) {

            System.out.println(inverteString(s));
            s = sc.nextLine();

        }
        sc.close();
    }
}
