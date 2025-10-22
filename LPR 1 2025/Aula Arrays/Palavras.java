public class Palavras {
    private static final int MAX = 5;
    private String[] elementos;
    int qtd;

    Palavras() {
        this.elementos = new String[MAX];
        this.qtd = 0;
    }

    public void add(String p) {
        if (this.qtd >= MAX) {
            System.out.println("Lista está cheia!");
            return;
        }
        this.elementos[this.qtd] = p;
        this.qtd++;

    }

    public void mostra() {
        for (int i = 0; i < qtd; i++) {
            System.out.println("p na posição " + i + ": " + elementos[i]);
        }
    }

    public String getPalavra(int indice) {
        if (indice < this.qtd) {
            return this.elementos[indice];
        } else {
            return "Índice não existe!";
        }
    }

    public int tamanho(){
        return this.qtd;
    }
}
