public class Exemplo6 {
    public static void verificaIdade(int idade) {
        if (idade < 18) {
            throw new IllegalArgumentException("Menores de 18 anos não são permitidos");
        }
        System.out.println("Acesso permitido!");
    }

    public static void main(String[] args) {
        try {
            verificaIdade(15);
        } catch (IllegalArgumentException e) {
            System.out.println("Exceção capturada: " + e.getMessage());
        }
    }
}
