import java.util.Scanner;
import java.util.Locale;

public class BolsasEscolares {
    static class Aluno{
        private double media;
        private int frequencia;
        private String nome;

        Aluno(String nome, double media, int frequencia){
            this.media = media;
            this.frequencia = frequencia;
            this.nome = nome;
        }

        public double getMedia(){
            return this.media;
        }
        public int getFrequencia(){
            return this.frequencia;
        }
        public String getNome(){
            return this.nome;
        }

    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        sc.useLocale(Locale.US); //isso aqui e' pra poder ter a entrada com x.x e nao x,x devido ao scanner usar o locale do meu computador(pt-br)
        int n;
        n = sc.nextInt();

        Aluno[] listaDAlunos = new Aluno[n];

        for(int i = 0; i < n; i++){
            String nomeAluno = sc.next();
            double notaAluno = sc.nextDouble();
            int frequenciaAluno = sc.nextInt();

            listaDAlunos[i] = new Aluno(nomeAluno, notaAluno, frequenciaAluno);
        }

        for(int i = 0; i < n; i++){
            Aluno temp = listaDAlunos[i];
            if(temp.getMedia() >= 9.0 && temp.getFrequencia() >= 90 ){
                System.out.println(temp.nome + " " + "Bolsa Excelencia");
            }else if(temp.getMedia() >= 8.0 && temp.getFrequencia() == 100){
                System.out.println(temp.nome + " " + "Bolsa Esforco");
            }else{
                System.out.println(temp.nome + " " + "Sem Bolsa");
            }
        }

        sc.close();
    }
}
