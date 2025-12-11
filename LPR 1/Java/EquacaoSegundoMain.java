import java.util.Scanner;

public class EquacaoSegundoMain {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        EquacaoSegundoGrau eq = new EquacaoSegundoGrau();

        eq.setA(2);
        eq.setB(-3);
        eq.setC(-5);
        eq.calcRaizes();

        eq.setA(2);
        eq.setB(6);
        eq.setC(4);
        eq.calcRaizes();

        cin.close();
    }
}
