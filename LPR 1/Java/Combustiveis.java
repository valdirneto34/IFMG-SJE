import java.util.Scanner;

public class Combustiveis {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        float etanol, gasolina;

        System.out.println("Digite o preço do etanol:");
        etanol = cin.nextFloat();

        System.out.println("Digite o preço da gasolina:");
        gasolina = cin.nextFloat();

        if (etanol <= gasolina * 0.7) {
            System.out.println("Abasteça com etanol.");
        }else{
            System.out.println("Abasteça com gasolina.");
        }
        cin.close();
    }
}
