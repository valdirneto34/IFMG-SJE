import java.util.Scanner;

public class NumeroPrimo {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int num, cont = 0;
        System.out.println("Digite um número para verificar se ele é primo:");
        num = cin.nextInt();

        for (int i = 1; i <= num; i++) {
            if (num % i == 0) {
                cont++;
            }
        }

        if (cont > 2) {
            System.out.println("O número não é primo.");
        } else {
            System.out.println("O número é primo.");
        }
        cin.close();
    }
}
