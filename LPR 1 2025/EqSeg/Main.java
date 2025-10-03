import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        EquacaoSegundoGrau eq = new EquacaoSegundoGrau();

        eq.setA(2);
        eq.setB(-3);
        eq.setC(-5);

        cin.close();
    }
}
