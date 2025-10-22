public class PalavrasMain {
    public static void main(String[] args) {
        Palavras a = new Palavras();

        a.add("Valdir de Souza Carvalho Neto");
        a.add("Patrícia da Silva Costa");
        a.add("Sebastião de Souza Carvalho");
        a.add("Juliana Gabriel Lopes");

        a.mostra();

        System.out.println(a.getPalavra(5));
    }
}
