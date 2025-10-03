public class AnalisarJogos {
    static class Jogos{
        private int id, donos, m_score, u_score, conquistas;
        private String name, pubs, devs;
        private String[] data, lang, categories, genres, tags;

        public Jogos(int id, int donos, int m_score, int u_score, int conquistas, 
        String name, String pubs, String devs, String[] data, String[] lang, 
        String[] categories, String[] tags, String[] genres)
        {
                this.id = id;
                this.donos = donos;
                this.m_score = m_score;
                this.u_score = u_score;
                this.conquistas = conquistas;
                this.name = name;
                this.pubs = pubs;
                this.devs = devs;
                this.data = data;
                this.lang = lang;
                this.categories = categories;
                this.genres = genres;
                this.tags = tags;
        }

        
    }
}