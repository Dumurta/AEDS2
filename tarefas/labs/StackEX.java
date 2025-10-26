import java.util.Scanner;
public class StackEX{
    class Celula{
        private int elemento;
        private Celula prox;
        public Celula(int x)
        {
            this.elemento = x;
            this.prox = null;
        }

    }
    class Pilha{
        private Celula cabeca;
        public Pilha()
        {
            cabeca = null;
        }
        public void empilhar(int x){
            Celula tmp = new Celula(x);
            tmp.prox = cabeca;
            cabeca = tmp;
            tmp = null;
        }
        public int remover(){
            int elemento = 0;
            if(cabeca == null){
                elemento = -1;
            }
            else{
                elemento = cabeca.prox.elemento;
                Celula tmp = cabeca;
                cabeca = cabeca.prox;
                tmp.prox = null;
                tmp = null;
            }
            return elemento;
        }
        public void mostrar(){
            Celula tmp = cabeca;
            while(tmp != null){
                System.out.print(tmp.elemento);
                tmp = tmp.prox;
            }
            tmp = null;
        }
        public boolean pesquisar(int x){
            Celula tmp = cabeca;
            boolean resultado = false;
            while(tmp != null){
                if(tmp.elemento == x){
                    resultado = true;
                    tmp = null;
                }
                else{
                    tmp = tmp.prox;
                }
            }
            return resultado;
        }
        
    }

    public static void main(String[] args) {
        Scanner sc  = new Scanner(System.in);
        while (sc.hasNextLine()) {
            
        }

    }
}