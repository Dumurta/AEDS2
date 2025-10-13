import java.io.*;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception {
        ArrayList<Jogo> lista = Jogo.lerCsv("/tmp/games.csv");
        BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
        String linha;
        while ((linha = in.readLine()) != null) {
            linha = linha.trim();
            if (linha.equals("FIM")) break;
            int id = Jogo.inteiro(linha);
            for (int i = 0; i < lista.size(); i++) {
                if (lista.get(i).id == id) {
                    lista.get(i).imprimir();
                    break;
                }
            }
        }
    }
}

class Jogo {
    int id;
    String nome;
    String data;
    long donos;
    float preco;
    String idiomas;
    int meta;
    double user;
    int conquistas;
    String pubs;
    String devs;
    String cats;
    String gens;
    String tags;

    public static ArrayList<Jogo> lerCsv(String caminho) throws Exception {
        BufferedReader arq = new BufferedReader(new FileReader(caminho));
        String linha = arq.readLine();
        ArrayList<Jogo> lista = new ArrayList<Jogo>();
        while ((linha = arq.readLine()) != null) {
            ArrayList<String> d = separar(linha);
            if (d.size() > 0) {
                Jogo j = criar(d);
                if (j.id != -1) lista.add(j);
            }
        }
        arq.close();
        return lista;
    }

    public static ArrayList<String> separar(String linha) {
        ArrayList<String> partes = new ArrayList<String>();
        String atual = "";
        boolean aspas = false;
        for (int i = 0; i < linha.length(); i++) {
            char c = linha.charAt(i);
            if (c == '"') aspas = !aspas;
            else if (c == ',' && !aspas) {
                partes.add(atual.trim());
                atual = "";
            } else atual += c;
        }
        partes.add(atual.trim());
        return partes;
    }

    public static Jogo criar(ArrayList<String> d) {
        Jogo j = new Jogo();
        j.id = (d.size() > 0) ? inteiro(d.get(0)) : -1;
        j.nome = (d.size() > 1) ? limpar(d.get(1)) : "";
        j.data = (d.size() > 2) ? formatarData(d.get(2)) : "01/01/0000";
        j.donos = (d.size() > 3) ? longo(d.get(3)) : 0;
        j.preco = (d.size() > 4) ? preco(d.get(4)) : 0;
        j.idiomas = (d.size() > 5) ? lista(d.get(5)) : "[]";
        j.meta = (d.size() > 6) ? inteiro(d.get(6)) : -1;
        j.user = (d.size() > 7) ? user(d.get(7)) : -1;
        j.conquistas = (d.size() > 8) ? inteiro(d.get(8)) : 0;
        j.pubs = (d.size() > 9) ? lista(d.get(9)) : "[]";
        j.devs = (d.size() > 10) ? lista(d.get(10)) : "[]";
        j.cats = (d.size() > 11) ? lista(d.get(11)) : "[]";
        j.gens = (d.size() > 12) ? lista(d.get(12)) : "[]";
        j.tags = (d.size() > 13) ? lista(d.get(13)) : "[]";
        return j;
    }

    public static String limpar(String s) {
        s = s.trim();
        if (s.length() >= 2 && ((s.charAt(0) == '"' && s.charAt(s.length()-1) == '"') || (s.charAt(0) == '\'' && s.charAt(s.length()-1) == '\''))) {
            s = s.substring(1, s.length()-1);
        }
        return s;
    }

    public static int inteiro(String s) {
        String n = "";
        for (int i = 0; i < s.length(); i++) {
            if (Character.isDigit(s.charAt(i))) n += s.charAt(i);
        }
        if (n.equals("")) return -1;
        return Integer.parseInt(n);
    }

    public static long longo(String s) {
        String n = "";
        for (int i = 0; i < s.length(); i++) {
            if (Character.isDigit(s.charAt(i))) n += s.charAt(i);
        }
        if (n.equals("")) return 0;
        return Long.parseLong(n);
    }

    public static float preco(String s) {
        s = s.trim();
        if (s.equalsIgnoreCase("Free to Play")) return 0;
        String n = "";
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (Character.isDigit(c) || c == '.') n += c;
        }
        if (n.equals("")) return 0;
        return Float.parseFloat(n);
    }

    public static double user(String s) {
        s = s.trim().toLowerCase();
        if (s.equals("") || s.equals("tbd")) return -1;
        String n = "";
        for (int i = 0; i < s.length(); i++) {
            char c = s.charAt(i);
            if (Character.isDigit(c) || c == '.' || c == ',') n += c;
        }
        n = n.replace(',', '.');
        if (n.equals("")) return -1;
        return Double.parseDouble(n);
    }

    public static String lista(String s) {
        s = s.trim();
        int a = s.indexOf('[');
        int b = s.lastIndexOf(']');
        if (a >= 0 && b > a) s = s.substring(a+1, b);
        String[] p = s.split(",");
        String r = "[";
        for (int i = 0; i < p.length; i++) {
            String x = p[i].trim();
            if (x.length() > 0) {
                if (r.length() > 1) r += ", ";
                r += x.replace("'", "").replace("\"", "");
            }
        }
        return r + "]";
    }

    public static String formatarData(String s) {
        s = s.trim();
        if (s.matches("\\d{4}")) return "01/01/" + s;
        if (s.matches("\\d{1,2}/\\d{1,2}/\\d{4}")) return s;
        String[] mes = {"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
        String[] num = {"01","02","03","04","05","06","07","08","09","10","11","12"};
        for (int i = 0; i < 12; i++) {
            if (s.toLowerCase().contains(mes[i])) {
                String ano = s.replaceAll("[^0-9]", "");
                String dia = "01";
                if (s.matches(".*\\d{1,2}.*")) {
                    String n = s.replaceAll("[^0-9 ]", "").trim().split(" ")[0];
                    if (n.length() > 0 && n.length() <= 2) dia = n;
                }
                return (dia.length() == 1 ? "0" + dia : dia) + "/" + num[i] + "/" + ano;
            }
        }
        return "01/01/0000";
    }

    public void imprimir() {
        String p = String.format(java.util.Locale.ENGLISH, "%.2f", preco);
        String u = String.format(java.util.Locale.ENGLISH, "%.1f", user);
        System.out.println("=> " + id + " ## " + nome + " ## " + data + " ## " + donos + " ## " + p + " ## " + idiomas +
                " ## " + meta + " ## " + u + " ## " + conquistas + " ## " + pubs + " ## " + devs +
                " ## " + cats + " ## " + gens + " ## " + tags + " ##");
    }
}
