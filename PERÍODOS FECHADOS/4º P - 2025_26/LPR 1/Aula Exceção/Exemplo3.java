public class Exemplo3 {
    public static void main(String[] args) {
        try {
            int numeros[] = { 1, 2, 3 };
            System.out.println(numeros[5]);
        } catch (ArrayIndexOutOfBoundsException e) {
            System.out.println("Índice fora dos limites. " + e.getMessage());
        } finally {

            System.out.println("Este bloco vai ser sempre executado.");
        }
    }
}
