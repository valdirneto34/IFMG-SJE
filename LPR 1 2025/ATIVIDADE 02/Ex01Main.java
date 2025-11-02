public class Ex01Main {
    public static void main(String[] args) {
        Ex01Stack Original = new Ex01Stack();
        for (int i = 100; i >= 10; i -= 10) {
            Original.push(i);
        }
        Ex01Stack Copia = new Ex01Stack(Original);

        try {
            System.out.println("Pilha original: ");
            System.out.println(Original.imprime());
            System.out.println("\nPilha cópia: ");
            System.out.println(Copia.imprime());
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }

        try {
            Original.pop();
            Original.pop();
            Original.pop();
            Copia.push(0);
            System.out.println("\n------------------------------------------------\n");
            System.out.println("Pilha original após exclusão de três elementos: ");
            System.out.println(Original.imprime());
            System.out.println("\nPilha cópia após adição de um elemento: ");
            System.out.println(Copia.imprime());
        } catch (Exception e) {
            System.out.println("Erro: " + e.getMessage());
        }
    }
}