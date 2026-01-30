public class Exemplo0 {
    public static void main(String[] args) {
        try {
            int a = 10, b = 0;
            int c = a / b;
            System.out.println(c);
        } catch (ArithmeticException e) {
            System.out.println("Erro: Divisão por zero!");
        }
        System.out.println("Programa continua executando...");
    }
}
