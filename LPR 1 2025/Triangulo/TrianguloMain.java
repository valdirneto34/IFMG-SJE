public class TrianguloMain {
    public static void main(String[] args) {
        Triangulo a = new Triangulo();
        
        Triangulo b = new Triangulo(10, 20, 20);
        
        Triangulo c = new Triangulo(b);

        System.out.println("Tudo certo!");
    }
}
