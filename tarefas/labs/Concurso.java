import java.util.Scanner;

public class Concurso{
    public static class Atleta{
        private int peso;
        private String nome;

        Atleta(String nome, int peso){
            this.nome = nome;
            this.peso = peso;
        }

        public int getPeso(){
            return this.peso;
        }
        public String getNome(){
            return this.nome;
        }

        public void imprimir(){
            System.out.println(this.nome + " " + this.peso);
        }
    }
    public static void ordenarLista(Atleta[] lista){
        int n = lista.length;

        for(int i = 0; i < n - 1; i++){
            for(int j = 0; j < n - 1; j++){
                Atleta atletaEsq = lista[j];
                Atleta atletaDir = lista[j + 1];
               if(atletaEsq.getPeso() < atletaDir.getPeso()){
                    Atleta temp = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = temp;
               }else if(atletaEsq.getPeso() == atletaDir.getPeso() && atletaEsq.getNome().compareTo(atletaDir.getNome()) > 0){
                    Atleta temp = lista[j];
                    lista[j] = lista[j + 1];
                    lista[j + 1] = temp;
               }
            }
        }
    }
    public static void main(String[] args){
        Scanner sc = new Scanner(System.in);
        int n = sc.nextInt();

        Atleta[] listaAtletas = new Atleta[n];

        for(int i = 0; i < n; i++){
            String nomeAtleta = sc.next();
            int pesoAtleta = sc.nextInt();

            listaAtletas[i] = new Atleta(nomeAtleta, pesoAtleta);
        }
        ordenarLista(listaAtletas);
        
        for(int i = 0; i < n; i++){
            listaAtletas[i].imprimir();
        }

        sc.close();
    }

}