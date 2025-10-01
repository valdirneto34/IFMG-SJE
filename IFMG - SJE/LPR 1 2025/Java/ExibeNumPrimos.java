public class ExibeNumPrimos {
    public static void main(String[] args) {
        int contador = 0;
        int numero = 2;
        System.out.println("Aqui estão os 100 primeiros números primos:");

        while (contador < 100) {
            boolean primo = true;

            for (int i = 2; i <= Math.sqrt(numero); i++) {
                if (numero % i == 0) {
                    primo = false;
                    break;
                }
            }
            if (primo) {
                System.out.print(numero + " ");
                contador++;
            }
            numero++;
        }
    }
}
