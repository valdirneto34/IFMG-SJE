import java.util.Scanner;

public class ArrayMain {
    public static void main(String[] args) {
        Scanner cin  = new Scanner(System.in);

        int[] A = new int[5];

        for(int i = 0; i < A.length; i++){
            System.out.println("Digite um número:");
            A[i] = cin.nextInt();
        }

        for(int i = 0; i < A.length; i++){
            System.out.println(A[i]);
        }

        cin.close();

    }
}
