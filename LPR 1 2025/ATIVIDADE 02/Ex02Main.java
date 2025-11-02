import java.util.Scanner;

public class Ex02Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        int num = 0;
        System.out.print("Digite um número inteiro: ");
        num = cin.nextInt();
        Ex02Stack A = new Ex02Stack(num);

        try {
            System.out.println("\nPilha A: ");
            System.out.println(A.imprime());
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
        try {
            System.out.println("\nSequência de remoção dos elementos: ");
            while (!A.isEmpty()) {
                System.out.print(A.pop());
                if (!A.isEmpty()) {
                    System.out.print(", ");
                }
            }
            System.out.println("\n\nPilha A após remoção: ");
            System.out.println(A.imprime());
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
        cin.close();
    }
}
