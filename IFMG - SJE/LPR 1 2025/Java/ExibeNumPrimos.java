public class ExibeNumPrimos {
    public static void main(String[] args) {
        int cont = 0;
        System.out.println("Aqui estão os 100 primeiros números primos:");
        for (int i = 1; i <= 100; i++) {
            cont = 0;
            for (int j = 1; j <= i; j++) {
                if (i % j == 0) {
                    cont++;
                }
            }
            if (cont <= 2) {
                System.out.print(i + " - ");
            }
        }
    }
}
