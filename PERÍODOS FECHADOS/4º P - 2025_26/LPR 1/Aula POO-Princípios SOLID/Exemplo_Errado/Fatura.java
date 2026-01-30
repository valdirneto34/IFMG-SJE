package Exemplo_Errado;

public class Fatura {
    private Livro livro;
    private int quantidade;
    private double total;

    public Fatura(Livro livro, int quantidade) {
        this.livro = livro;
        this.quantidade = quantidade;
        this.total = this.calcularTotal();
    }

    public double calcularTotal() {
        total = (livro.getPreco() * quantidade);
        return total;
    }

    public Livro getLivro() {
        return livro;
    }

    public int getQuantidade() {
        return quantidade;
    }

}
