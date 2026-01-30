public class Ex06Main {
    public static void main(String[] args) {

        Ex06Classes Aluno1 = new Ex06Classes("Valdir de Souza Carvalho Neto", 1, "Licenciatura em Matemática", 21);
        Ex06Classes Aluno2 = new Ex06Classes("Patrícia da Silva Costa", 2, "Bacharelado em Sistemas de informação", 20);
        Ex06Classes Aluno3 = new Ex06Classes("Juliana Gabriel Lopes", 3, "Licenciatura em Ciências Biológicas", 42);

        System.out.print(Aluno1.exibeInformacoes());
        System.out.print(Aluno2.exibeInformacoes());
        System.out.print(Aluno3.exibeInformacoes());

        Universidade.setNomeInstituicao("IFMG - Campus Bambuí");

        System.out.print(Aluno1.exibeInformacoes());
        System.out.print(Aluno2.exibeInformacoes());
        System.out.print(Aluno3.exibeInformacoes());
    }
}
