public class EquacaoSegundoGrau {
    private double a, b, c;

    public void setA(double a) {
        this.a = a;
    }

    public void setB(double b) {
        this.b = b;
    }

    public void setC(double c) {
        this.c = c;
    }

    public void calcRaizes() {
        double delta = b * b - 4 * a * c;
        if (delta < 0) {
            System.out.println("Não existem raízes reais.");
        } else if (delta == 0) {
            double x = -b / (2 * a);
            System.out.println("A única raíz da equação é " + x);
        } else {
            double x1 = (-b + Math.sqrt(delta)) / (2 * a);
            double x2 = (-b - Math.sqrt(delta)) / (2 * a);

            System.out.println("Raízes x\' = " + x1 + "\nx\'\' = " + x2);
        }
    }
}
