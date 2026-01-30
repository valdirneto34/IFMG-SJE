public class Ex03Main {
    public static void main(String[] args) {
        Ex03Stack A = new Ex03Stack(10);
        Ex03Stack B = new Ex03Stack(12);

        try {
            System.out.println("\nPilha A: ");
            System.out.println(A.imprime());

            System.out.println("\nPilha B: ");
            System.out.println(B.imprime());

            if (Ex03Stack.equals(A, B)) {
                System.out.println("As pilhas são iguais!");
            } else {
                System.out.println("As pilhas não são iguais!");
            }
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }

    }
}
