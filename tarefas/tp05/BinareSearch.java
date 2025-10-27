import java.util.*;
import java.io.*;

public class BinareSearch {
    
    static class ResultadoBusca {
        boolean encontrado;
        int comparacoes;
        
        ResultadoBusca(boolean enc, int comp) {
            encontrado = enc;
            comparacoes = comp;
        }
        //end "ResultadoBusca"
    }
    
    public static ArrayList<Jogo> lerArquivo(String caminho) throws Exception {
        BufferedReader arquivo = new BufferedReader(new FileReader(caminho));
        ArrayList<Jogo> jogos = new ArrayList<Jogo>();
        
        String linha = arquivo.readLine();
        
        linha = arquivo.readLine();
        while (linha != null) {
            String[] campos = Jogo.separarCampos(linha);
            
            if (campos.length >= 14) {
                Jogo j = Jogo.criarJogo(campos);
                if (j.id != -1) {
                    jogos.add(j);
                }
            }
            
            linha = arquivo.readLine();
        }
        
        arquivo.close();
        ArrayList<Jogo> resultado = jogos;
        return resultado;
    }
    //end "lerArquivo"
    
    public static void ordenarPorNome(Jogo[] jogos) {
        int n = jogos.length;
        int i = 0;
        
        while (i < n - 1) {
            int menor = i;
            int j = i + 1;
            
            while (j < n) {
                if (jogos[j].nome.compareTo(jogos[menor].nome) < 0) {
                    menor = j;
                }
                j++;
            }
            
            if (menor != i) {
                Jogo temp = jogos[i];
                jogos[i] = jogos[menor];
                jogos[menor] = temp;
            }
            
            i++;
        }
    }
    //end "ordenarPorNome"
    
    public static ResultadoBusca pesquisaBinaria(Jogo[] jogos, String nome) {
        int esq = 0;
        int dir = jogos.length - 1;
        int comparacoes = 0;
        boolean encontrado = false;
        
        while (esq <= dir && !encontrado) {
            int meio = (esq + dir) / 2;
            comparacoes++;
            int cmp = nome.compareTo(jogos[meio].nome);
            
            if (cmp == 0) {
                encontrado = true;
            } else if (cmp < 0) {
                dir = meio - 1;
            } else {
                esq = meio + 1;
            }
        }
        
        ResultadoBusca resultado = new ResultadoBusca(encontrado, comparacoes);
        return resultado;
    }
    //end "pesquisaBinaria"
    
    public static void criarLog(String matricula, int comparacoes, long tempo) throws Exception {
        PrintWriter writer = new PrintWriter(new FileWriter(matricula + "_binaria.txt"));
        writer.print(matricula + "\t" + comparacoes + "\t" + tempo);
        writer.close();
    }
    //end "criarLog"
    
    public static void main(String[] args) throws Exception {
        ArrayList<Jogo> todosJogos = lerArquivo("/tmp/games.csv");
        
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        ArrayList<Jogo> jogosSelecionados = new ArrayList<Jogo>();
        
        String linha = br.readLine();
        while (linha != null && !linha.equals("FIM")) {
            int idBuscado = Jogo.converterParaInt(linha);
            
            int i = 0;
            while (i < todosJogos.size()) {
                if (todosJogos.get(i).id == idBuscado) {
                    jogosSelecionados.add(todosJogos.get(i));
                    i = todosJogos.size();
                }
                i++;
            }
            
            linha = br.readLine();
        }
        
        Jogo[] jogos = new Jogo[jogosSelecionados.size()];
        int i = 0;
        while (i < jogosSelecionados.size()) {
            jogos[i] = jogosSelecionados.get(i);
            i++;
        }
        
        ordenarPorNome(jogos);
        
        int totalComparacoes = 0;
        long tempoInicio = System.currentTimeMillis();
        
        linha = br.readLine();
        while (linha != null && !linha.equals("FIM")) {
            ResultadoBusca resultado = pesquisaBinaria(jogos, linha);
            totalComparacoes = totalComparacoes + resultado.comparacoes;
            
            if (resultado.encontrado) {
                System.out.println(" SIM");
            } else {
                System.out.println(" NAO");
            }
            
            linha = br.readLine();
        }
        
        long tempoFim = System.currentTimeMillis();
        long tempoTotal = tempoFim - tempoInicio;
        
        criarLog("884985", totalComparacoes, tempoTotal);
        
        br.close();
    }
    //end "main"
}

class Jogo {
    int id;
    String nome;
    String data;
    double estimatedOwners;
    float preco;
    String[] idiomas;
    int metacriticScore;
    double userScore;
    int conquistas;
    String[] publishers;
    String[] developers;
    String[] categorias;
    String[] generos;
    String[] tags;
    
    public static boolean ehArray(String linha) {
        int i = 0;
        boolean resultado = false;
        while (i < linha.length() && linha.charAt(i) == ' ') {
            i++;
        }
        if (i < linha.length() && linha.charAt(i) == '[') {
            resultado = true;
        }
        return resultado;
    }
    //end "ehArray"
    
    public static String pegarConteudo(String linha) {
        String conteudo = "";
        int i = 0;
        boolean dentroColchetes = false;
        while (i < linha.length()) {
            char c = linha.charAt(i);
            if (c == '[') {
                dentroColchetes = true;
            } else if (c == ']') {
                dentroColchetes = false;
            } else if (dentroColchetes) {
                conteudo = conteudo + c;
            }
            i++;
        }
        return conteudo;
    }
    //end "pegarConteudo"
    
    public static String limparElemento(String elemento) {
        String limpo = "";
        int i = 0;
        
        while (i < elemento.length() && elemento.charAt(i) == ' ') {
            i++;
        }
        
        while (i < elemento.length()) {
            char c = elemento.charAt(i);
            if (c != '\'' && c != '"') {
                limpo = limpo + c;
            }
            i++;
        }
        
        int fim = limpo.length() - 1;
        
        while (fim >= 0 && limpo.charAt(fim) == ' ') {
            fim--;
        }
        
        String resultado = "";
        i = 0;
        while (i <= fim) {
            resultado = resultado + limpo.charAt(i);
            i++;
        }
        
        return resultado;
    }
    //end "limparElemento"
    
    public static String[] processarArray(String s) {
        String[] resultado = new String[0];
        if (ehArray(s)) {
            String conteudo = pegarConteudo(s);
            String[] partes = conteudo.split(",");
            
            int contado = 0;
            int i = 0;
            while (i < partes.length) {
                String limpo = limparElemento(partes[i]);
                if (limpo.length() > 0) {
                    contado++;
                }
                i++;
            }
            
            resultado = new String[contado];
            
            int pos = 0;
            i = 0;
            
            while (i < partes.length) {
                String limpo = limparElemento(partes[i]);
                if (limpo.length() > 0) {
                    resultado[pos] = limpo;
                    pos++;
                }
                i++;
            }
        }
        return resultado;
    }
    //end "processarArray"
    
    public static String[] separarCampos(String s) {
        ArrayList<String> campos = new ArrayList<String>();
        String campoAtual = "";
        boolean dentroAspas = false;
        int i = 0;
        while (i < s.length()) {
            char c = s.charAt(i);
            
            if (c == '"') {
                dentroAspas = !dentroAspas;
            } else if (c == ',' && !dentroAspas) {
                campos.add(campoAtual);
                campoAtual = "";
            } else {
                campoAtual = campoAtual + c;
            }
            
            i++;
        }
        
        campos.add(campoAtual);
        
        String[] resultado = new String[campos.size()];
        
        i = 0;
        
        while (i < campos.size()) {
            resultado[i] = campos.get(i);
            i++;
        }
        
        return resultado;
    }
    //end "separarCampos"
    
    public static String removerAspas(String campo) {
        String resultado = "";
        int inicio = 0;
        int fim = campo.length() - 1;
        
        while (inicio < campo.length() && campo.charAt(inicio) == ' ') {
            inicio++;
        }
        
        while (fim >= 0 && campo.charAt(fim) == ' ') {
            fim--;
        }
        
        if (inicio <= fim && campo.charAt(inicio) == '"') {
            inicio++;
        }
        if (inicio <= fim && campo.charAt(fim) == '"') {
            fim--;
        }
        
        int i = inicio;
        while (i <= fim) {
            resultado = resultado + campo.charAt(i);
            i++;
        }
        
        return resultado;
    }
    //end "removerAspas"
    
    public static Jogo criarJogo(String[] campos) {
        Jogo j = new Jogo();
        
        j.id = converterParaInt(campos[0]);
        j.nome = removerAspas(campos[1]);
        j.data = formatarData(campos[2]);
        j.estimatedOwners = converterParaDouble(campos[3]);
        j.preco = converterParaPreco(campos[4]);
        j.idiomas = processarArray(campos[5]);
        j.metacriticScore = converterParaInt(campos[6]);
        j.userScore = converterParaUserScore(campos[7]);
        j.conquistas = converterParaInt(campos[8]);
        j.publishers = processarArray(campos[9]);
        j.developers = processarArray(campos[10]);
        j.categorias = processarArray(campos[11]);
        j.generos = processarArray(campos[12]);
        j.tags = processarArray(campos[13]);
        
        return j;
    }
    //end "criarJogo"
    
    public static int converterParaInt(String s) {
        String numeros = "";
        int i = 0;
        
        while (i < s.length()) {
            char c = s.charAt(i);
            if (c >= '0' && c <= '9') {
                numeros = numeros + c;
            }
            i++;
        }
        
        int resultado = -1;
        if (numeros.length() > 0) {
            resultado = Integer.parseInt(numeros);
        }
        
        return resultado;
    }
    //end "converterParaInt"
    
    public static double converterParaDouble(String s) {
        String numeros = "";
        int i = 0;
        
        while (i < s.length()) {
            char c = s.charAt(i);
            if (c >= '0' && c <= '9') {
                numeros = numeros + c;
            }
            i++;
        }
        
        double resultado = 0;
        if (numeros.length() > 0) {
            resultado = Double.parseDouble(numeros);
        }
        
        return resultado;
    }
    //end "converterParaDouble"
    
    public static float converterParaPreco(String s) {
        s = removerAspas(s);
        
        String sLower = "";
        int i = 0;
        while (i < s.length()) {
            char c = s.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                sLower = sLower + (char)(c + 32);
            } else {
                sLower = sLower + c;
            }
            i++;
        }
        
        float resultado = 0.0f;
        if (sLower.equals("free to play")) {
            resultado = 0.0f;
        } else {
            String numeros = "";
            i = 0;
            while (i < s.length()) {
                char c = s.charAt(i);
                if ((c >= '0' && c <= '9') || c == '.') {
                    numeros = numeros + c;
                }
                i++;
            }
            
            if (numeros.length() > 0) {
                resultado = Float.parseFloat(numeros);
            }
        }
        
        return resultado;
    }
    //end "converterParaPreco"
    
    public static double converterParaUserScore(String s) {
        s = removerAspas(s);
        
        String sLower = "";
        int i = 0;
        while (i < s.length()) {
            char c = s.charAt(i);
            if (c >= 'A' && c <= 'Z') {
                sLower = sLower + (char)(c + 32);
            } else {
                sLower = sLower + c;
            }
            i++;
        }
        
        double resultado = -1.0;
        if (!sLower.equals("") && !sLower.equals("tbd")) {
            String numeros = "";
            i = 0;
            while (i < s.length()) {
                char c = s.charAt(i);
                if ((c >= '0' && c <= '9') || c == '.' || c == ',') {
                    if (c == ',') {
                        numeros = numeros + '.';
                    } else {
                        numeros = numeros + c;
                    }
                }
                i++;
            }
            
            if (numeros.length() > 0) {
                resultado = Double.parseDouble(numeros);
            }
        }
        
        return resultado;
    }
    //end "converterParaUserScore"
    
    public static String formatarData(String s) {
        s = removerAspas(s);
        
        boolean somenteDigitos = true;
        int i = 0;
        while (i < s.length()) {
            if (s.charAt(i) < '0' || s.charAt(i) > '9') {
                somenteDigitos = false;
            }
            i++;
        }
        
        String resultado = "01/01/0000";
        if (somenteDigitos && s.length() == 4) {
            resultado = "01/01/" + s;
        } else {
            boolean temBarra = false;
            i = 0;
            while (i < s.length()) {
                if (s.charAt(i) == '/') {
                    temBarra = true;
                }
                i++;
            }
            
            if (temBarra) {
                resultado = s;
            } else {
                String[] meses = {"jan", "feb", "mar", "apr", "may", "jun", 
                                "jul", "aug", "sep", "oct", "nov", "dec"};
                String[] numMes = {"01", "02", "03", "04", "05", "06",
                                 "07", "08", "09", "10", "11", "12"};
                
                i = 0;
                while (i < 12) {
                    String sLower = "";
                    int j = 0;
                    while (j < s.length()) {
                        char c = s.charAt(j);
                        if (c >= 'A' && c <= 'Z') {
                            sLower = sLower + (char)(c + 32);
                        } else {
                            sLower = sLower + c;
                        }
                        j++;
                    }
                    
                    boolean contemMes = false;
                    j = 0;
                    while (j <= sLower.length() - 3 && !contemMes) {
                        boolean match = true;
                        int k = 0;
                        while (k < 3 && match) {
                            if (sLower.charAt(j + k) != meses[i].charAt(k)) {
                                match = false;
                            }
                            k++;
                        }
                        if (match) {
                            contemMes = true;
                        }
                        j++;
                    }
                    
                    if (contemMes) {
                        String numeros = "";
                        j = 0;
                        while (j < s.length()) {
                            if (s.charAt(j) >= '0' && s.charAt(j) <= '9') {
                                numeros = numeros + s.charAt(j);
                            } else {
                                numeros = numeros + " ";
                            }
                            j++;
                        }
                        
                        String[] partesNum = numeros.split(" ");
                        String dia = "01";
                        String ano = "";
                        
                        j = 0;
                        while (j < partesNum.length) {
                            if (partesNum[j].length() > 0) {
                                if (partesNum[j].length() == 4) {
                                    ano = partesNum[j];
                                } else if (partesNum[j].length() <= 2 && dia.equals("01")) {
                                    dia = partesNum[j];
                                }
                            }
                            j++;
                        }
                        
                        if (dia.length() == 1) {
                            dia = "0" + dia;
                        }
                        
                        resultado = dia + "/" + numMes[i] + "/" + ano;
                        i = 12;
                    }
                    
                    i++;
                }
            }
        }
        
        return resultado;
    }
    //end "formatarData"
}