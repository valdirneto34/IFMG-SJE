package Exemplo_Errado;

public class Main {
    public static void main(String[] args) {
        Livro l = new Livro("Harry Potter", 2002, 50);
        Fatura f = new Fatura(l, 4);
        ImpressaoDeFatura i = new ImpressaoDeFatura(f);

        i.imprimir();
    }
}
