public class Carro extends Veiculo {
    @Override
    public void ligar() {
        System.out.println("Carro ligado.");
    }

    public void acelerar() {
        System.out.println("Carro acelerando. VRUM... VRUM...");
    }
}
