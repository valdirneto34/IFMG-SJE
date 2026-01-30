import java.util.Scanner;

public class ExemploArray {
    public static void main(String[] args) {
        Scanner cin  = new Scanner(System.in);

        int[] A = new int[5];

        for(int i = 0; i < A.length; i++){
            System.out.print("Digite um número: ");
            A[i] = cin.nextInt();
        }

        for(int i = 0; i < A.length; i++){
            System.out.print(A[i] + " ");
        }

        cin.close();

    }
}
