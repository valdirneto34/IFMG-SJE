import java.util.Scanner;

public class ParOuImpar {

    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int num;

        System.out.println("Digite um número: ");
        num = cin.nextInt();

        if (num % 2 == 0) {
            System.out.println("O numero " + num + " é par.");
        } else {
            System.out.println("O numero " + num + " é impar.");
        }
        cin.close();

    }

}
