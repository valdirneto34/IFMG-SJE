public class Aluno {
    private String nome;
    private double nota1, nota2, nota3;

    public void setNome(String nome) {
        this.nome = nome;
    }

    public void setNota1(double nota1) {
        this.nota1 = nota1;
    }

    public void setNota2(double nota2) {
        this.nota2 = nota2;
    }

    public void setNota3(double nota3) {
        this.nota3 = nota3;
    }

    public String getNome() {
        return nome;
    }

    public double getMedia() {
        double media = (nota1 + nota2 + nota3) / 3;

        return media;

    }

    public boolean getSituacaoFinal() {
        double media = (nota1 + nota2 + nota3) / 3;

        if (media >= 60) {
            return true;
        } else {
            return false;
        }

    }

}
