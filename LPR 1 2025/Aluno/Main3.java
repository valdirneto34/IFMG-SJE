import java.util.Scanner;

public class Main3 {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
        Aluno aluno = new Aluno();
        String nome;
        double nota1, nota2, nota3;

        System.out.println("Digite o nome do aluno:");
        nome = cin.nextLine();
        System.out.println("Digite a 1ª nota do aluno:");
        nota1 = cin.nextDouble();
        System.out.println("Digite a 2ª nota do aluno:");
        nota2 = cin.nextDouble();
        System.out.println("Digite a 3ª nota do aluno:");
        nota3 = cin.nextDouble();

        aluno.setNome(nome);
        aluno.setNota1(nota1);
        aluno.setNota2(nota2);
        aluno.setNota3(nota3);

        System.out.println("Nome do aluno.: " + aluno.getNome());
        System.out.println("Média do aluno: " + aluno.getMedia());
        if (aluno.getSituacaoFinal()) {
            System.out.println("Situação final: Aprovado!");
        } else {
            System.out.println("Situação final: Reprovado!");
        }

        cin.close();

    }
}
