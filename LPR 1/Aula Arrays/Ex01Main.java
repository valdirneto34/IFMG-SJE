public class Ex01Main {
    public static void main(String[] args) {
        Ex01 a = new Ex01();

        a.add("Valdir de Souza Carvalho Neto");
        a.add("Patrícia da Silva Costa");
        a.add("Sebastião de Souza Carvalho");
        a.add("Juliana Gabriel Lopes");

        a.mostra();

        System.out.println(a.getPalavra(5));
    }
}
