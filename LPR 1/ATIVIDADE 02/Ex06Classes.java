public class Ex06Classes {
    private String nome;
    private int matricula;
    private String curso;
    private int idade;

    public Ex06Classes() {
    }

    public Ex06Classes(String nome, int matricula) {
        this.setNome(nome);
        this.setMatricula(matricula);
    }

    public Ex06Classes(String nome, int matricula, String curso, int idade) {
        this.setNome(nome);
        this.setMatricula(matricula);
        this.setCurso(curso);
        this.setIdade(idade);
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public String getNome() {
        return nome;
    }

    public void setMatricula(int matricula) {
        this.matricula = matricula;
    }

    public int getMatricula() {
        return matricula;
    }

    public void setCurso(String curso) {
        this.curso = curso;
    }

    public String getCurso() {
        return curso;
    }

    public void setIdade(int idade) {
        this.idade = idade;
    }

    public int getIdade() {
        return idade;
    }

    public String exibeInformacoes() {
        String result = "";
        result += "---------------------------------------------------\n";
        result += "Nome........: " + getNome() + "\n";
        result += "Matrícula...: " + getMatricula() + "\n";
        result += "Curso.......: " + getCurso() + "\n";
        result += "Idade.......: " + getIdade() + "\n";
        result += "Universidade: " + Universidade.nomeInstituicao + "\n";
        result += "---------------------------------------------------\n";
        return result;
    }
}

class Universidade {
    static String nomeInstituicao = "IFMG - Campus SJE";

    public static void setNomeInstituicao(String nomeInstituicao) {
        Universidade.nomeInstituicao = nomeInstituicao;
    }
}