public class Ex04Main {
        public static void main(String[] args) {
                Ex04Aluno Aluno1 = new Ex04Aluno();
                Aluno1.setNome("Valdir de Souza Carvalho Neto");
                Aluno1.setMatricula(1);
                Aluno1.setCurso("Licenciatura em Matemática");
                Aluno1.setIdade(21);

                Ex04Aluno Aluno2 = new Ex04Aluno();
                Aluno2.setNome("Patrícia da Silva Costa");
                Aluno2.setMatricula(2);
                Aluno2.setCurso("Bacharelado em Sistemas de Informação");
                Aluno2.setIdade(20);

                Ex04Aluno Aluno3 = new Ex04Aluno();
                Aluno3.setNome("Juliana Gabriel Lopes");
                Aluno3.setMatricula(3);
                Aluno3.setCurso("Licenciatura em Ciências Biológicas");
                Aluno3.setIdade(42);

                System.out.print(Aluno1.exibeInformacoes());
                System.out.print(Aluno2.exibeInformacoes());
                System.out.print(Aluno3.exibeInformacoes());
        }
}
