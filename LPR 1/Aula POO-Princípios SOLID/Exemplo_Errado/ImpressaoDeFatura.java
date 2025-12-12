package Exemplo_Errado;

public class ImpressaoDeFatura {
    private Fatura fatura;

    public ImpressaoDeFatura(Fatura fatura) {
        this.fatura = fatura;
    }

    public void imprimir(){
        System.out.println(fatura.getQuantidade() + "x " + fatura.getLivro().getNome() + " R$" + fatura.getLivro().getPreco());
        System.out.println("Total: " + fatura.calcularTotal());
    }
}
