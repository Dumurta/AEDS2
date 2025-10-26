public class Main{
    class Jogo{
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

        public static boolean ehArray(String linha){
            int i = 0;
            boolean resultado = false;
            while(i < linha.length() && linha.charAt(i) == ' ')
            {
                i++;
            }
            if(i < linha.length() && linha.charAt(i) == '[')
            {
                resultado = true;
            }

            return resultado;
        }//end ehArray

        public static String pegarConteudo(String linha){
            String conteudo = " ";
            int i = 0;
            boolean dentroColchetes = false;
            while(i < linha.length()){
                char c = linha.charAt(i);
                if(c == '[')
                {
                    dentroColchetes = true;
                }
                else if ( c == ']')
                {
                    dentroColchetes = false;
                }
                else if(dentroColchetes){
                    conteudo = conteudo + c;
                }
                i++;
            }
            return conteudo;
        }//end pegarConteudo

        public static String limparElemento(String elemento)
        {
            String limpo = ""; 
            int i = 0;

            while(i < elemento.length() && elemento.charAt(i) == ' ')
            {
                i++;
            }

            while(i < elemento.length())
            {
                char c = elemento.charAt(i);
                if(c != '\'' && c != '"')
                {
                    limpo = limpo + c;
                }
                i++;
            }

            int fim = limpo.length() - 1;

            while(fim >= 0 && limpo.charAt(fim) == ' ')
            {
                fim--;
            }

            String resultado = ""; 
            i = 0;
            while (i <= fim)
            {
                resultado = resultado + limpo.charAt(i);
                i++;
            }

            return resultado;
        }//end limparElemento

        public static String[] processarArray(String s)
        {
            String[] resultado = new String[0];
            if(ehArray(s))
            {

                String conteudo = pegarConteudo(s);

                String[] partes = conteudo.split(",");

                int contado = 0;
                int i = 0;
                while(i < partes.length)
                {
                    String limpo = limparElemento(partes[i]);
                    if(limpo.length() > 0)
                    {
                        contado++;
                    }
                    i++;
                }
                
                resultado = new String[contado];

                int pos = 0;

                i = 0;

                while(i < partes.length)
                {
                    String limpo = limparElemento(partes[i]);
                    if(limpo.length() > 0)
                    {
                        resultado[pos] = limpo;
                        pos++;
                    }

                    i++;
                }
            }
            return resultado;
        }//end processaArray

        public static String[] separarCampos(String s)
        {
            ArrayList<String> campos = new ArrayList<String>();
            String campoAtual ="";
            boolean dentroAspas = false;
            int i = 0;
            while(i< s.length())
            {
                char c = s.charAt(i);

                if(c == '"')
                {
                    dentroAspas = !dentroAspas;
                }
                else if(c == ',' && !dentroAspas)
                {
                    campos.add(campoAtual);
                    campoAtual = "";
                }
                else{
                    campoAtual = campoAtual + c;
                }

                i++;
            }

            campos.add(campoAtual);

            String[] resultado = new String[campos.size()];

            i = 0;

            while(i < campos.size())
            {
                resultado[i] = campos.get(i);
                i++;
            }

            return resultado;
        }

    }
}