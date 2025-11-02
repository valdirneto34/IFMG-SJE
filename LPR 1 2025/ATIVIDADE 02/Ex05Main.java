public class Ex05Main {
    public static void main(String[] args) {
        Ex04Aluno Aluno1 = new Ex04Aluno();
        Aluno1.setNome("Valdir de Souza Carvalho Neto");
        Aluno1.setMatricula(1);
        Aluno1.setCurso("Licenciatura em Matemática");
        Aluno1.setIdade(21);
        Ex05Aluno Aluno2 = new Ex05Aluno("Patrícia da Silva Costa", 2);
        Aluno2.setCurso("Bacharelado em Sistemas de Informação");
        Aluno2.setIdade(20);
        Ex05Aluno Aluno3 = new Ex05Aluno("Juliana Gabriel Lopes", 3, "Licenciatura em Ciências Biológicas", 42);

        System.out.print(Aluno1.exibeInformacoes());
        System.out.print(Aluno2.exibeInformacoes());
        System.out.print(Aluno3.exibeInformacoes());
    }
}