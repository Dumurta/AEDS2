import java.util.*;
class No{
    int elemento;
    No esq;
    No dir;
    No(int elemento)
    {
        this.elemento = elemento;
        this.esq = null;
        this.dir = null;
    }
}
public class ArvoreBin{
    private No raiz;
    private ArvoreBin(){
                raiz = null;
            }
    public void inserir(int x) throws Exception
    {
        raiz = inserir(x, raiz);
    }
    No inserir(int x, No i) throws Exception{
        if(i == null)
        {
            i = new No(x);
        }else if(x < i.elemento){
            i.esq = inserir(x, i.esq);
        }else if(x > i.elemento){
            i.dir = inserir(x, i.dir);
        }else{
            throw new Exception("ERRO!");
        }
        return i;
    }
    boolean pesquisar(int x){
        return pesquisar(x, raiz);
    }
    boolean pesquisar(int x, No i){
        boolean resposta;
        if(i == null){
            resposta = false;
        }else if(i.elemento == x){
            resposta = true;
        }else if(i.elemento < x){
            resposta = pesquisar(x, i.esq);
        }else{
            resposta = pesquisar(x, i.dir);
        }
        return resposta;
    }
    public void caminharCentral(No i){
        if(i != null){
            caminharCentral(i.esq);
            System.out.print(i.elemento);
            caminharCentral(i.dir);
        }
    }
    public void caminharPos(No i){
        if(i != null){
            caminharPos(i.esq);
            caminharPos(i.dir);
            System.out.print(i.elemento);
        }
    }
    public void caminharPre(No i){
        if(i != null){
            System.out.print(i.elemento);
            caminharPre(i.esq);
            caminharPre(i.dir);
        }
    }
}
class LabArvoreBinaria{
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String line = sc.nextLine();
        while(sc.hasNext()){
            if(line.equals("I")){
                
            }
        }
    }
}