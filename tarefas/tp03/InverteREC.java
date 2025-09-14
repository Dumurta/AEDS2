import java.util.Scanner;
public class InverteREC{
    public static String inverterStringR(String s1, int i){
        String s2 = "";
        if(i >= 0)
        {
            s2 += s1.charAt(i);
            s2 += inverterStringR(s1, i - 1);
        }

        return s2;
    }
    public static String inverterString(String s)
    {
        int i = s.length() - 1;
        return inverterStringR(s, i);
    }
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String s = "";
        s = sc.nextLine();

        while (!(s.length() >= 3 && s.charAt(0) == 'F' && s.charAt(1) == 'I' && s.charAt(2) == 'M')) {

            System.out.println(inverterString(s));
            s = sc.nextLine();

        }
        sc.close();
    }
}
