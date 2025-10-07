import java.util.Scanner;

public class ProdutoMain {
    public static void main(String[] args) {
        Produto produto = new Produto();
        Scanner cin = new Scanner(System.in);
        String nome;
        double preco;

        System.out.println("Digite o nome do produto:");
        nome = cin.nextLine();
        System.out.println("Digite o preço do produto:");
        preco = cin.nextDouble();

        produto.setNome(nome);
        produto.setPreco(preco);

        System.out.println("\nO nome do produto é.: " + produto.getNome());
        System.out.println("O preço do produto é: " + produto.getPreco());

        cin.close();
    }
}
