package OCP;

public class Main {
    public static void main(String[] args) {
        CalculadoraDePreco cal = new CalculadoraDePreco();
        double precoOriginal = 100;

        System.out.println("Preço com desconto comum: " + cal.CalcularPrecoFinal(precoOriginal, new DescontoComum()));
        System.out.println("Preço Black Friday: " + cal.CalcularPrecoFinal(precoOriginal, new DescontoBlack()));
    }
}

interface Desconto {
    double calcular(double valor);

}

class DescontoComum implements Desconto {
    @Override
    public double calcular(double valor) {
        return valor * 0.9;
    }
}

class DescontoBlack implements Desconto {
    @Override
    public double calcular(double valor) {
        return valor * 0.5;
    }
}

class CalculadoraDePreco {
    public double CalcularPrecoFinal(double valor, Desconto desconto) {
        return desconto.calcular(valor);
    }
}
