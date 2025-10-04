import java.util.Scanner;

public class Main4 {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        Ponto ponto1 = new Ponto();
        Ponto ponto2 = new Ponto();
        double x1, y1, x2, y2;

        System.out.println("Digite o valor de x1:");
        x1 = cin.nextDouble();
        System.out.println("Digite o valor de y1:");
        y1 = cin.nextDouble();
        System.out.println("Digite o valor de x2:");
        x2 = cin.nextDouble();
        System.out.println("Digite o valor de y2:");
        y2 = cin.nextDouble();

        ponto1.setX(x1);
        ponto1.setY(y1);
        ponto2.setX(x2);
        ponto2.setY(y2);

        System.out.println("Ponto 1: x é igual a " + ponto1.getX() + " e y é igual a " + ponto1.getY());
        System.out.println("Ponto 2: x é igual a " + ponto2.getX() + " e y é igual a " + ponto2.getY());

        System.out.println("A distância entre os pontos é de: " + ponto1.calcularDistancia(ponto2));

        cin.close();
    }
}
