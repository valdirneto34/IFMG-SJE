import java.util.ArrayList;

public class Ex02 {
    private static final int MAX = 50;
    ArrayList<String> elementos = new ArrayList<>();
    int qtd;

    Ex02() {
        this.qtd = 0;
    }

    public void add(String p) {
        if (this.qtd >= MAX) {
            System.out.println("Lista está cheia!");
            return;
        }
        elementos.add(p);
        this.qtd++;

    }

    public void mostra() {
        for (int i = 0; i < qtd; i++) {
            System.out.println("Elemento na posição " + i + ": " + elementos.get(i));
        }
    }

    public String getPalavra(int indice) {
        if (indice < this.qtd) {
            return elementos.get(indice);
        } else {
            return "Índice não existe!";
        }
    }

    public int tamanho() {
        return elementos.size();
    }

}
