public class TrianguloMain {
    public static void main(String[] args) {
        Triangulo a = new Triangulo();

        Triangulo b = new Triangulo(10, 20, 20);

        Triangulo c = new Triangulo(b);

        c.setLadoA(50);
        a.setLadoB(80);
        a.setLadoC(99);

        System.out.println("Triângulo A:");
        a.mostra();
        System.out.println("Perímetro: " + a.calcularPerimetro());
        System.out.println("Tipo: " + a.tipoTriangulo());

        System.out.println("\nTriângulo B:");
        b.mostra();
        System.out.println("Perímetro: " + b.calcularPerimetro());
        System.out.println("Tipo: " + b.tipoTriangulo());
        
        System.out.println("\nTriângulo C:");
        c.mostra();
        System.out.println("Perímetro: " + c.calcularPerimetro());
        System.out.println("Tipo: " + c.tipoTriangulo());


    }
}
