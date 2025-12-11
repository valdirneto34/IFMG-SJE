public class Funcionario {
    protected String nome;
    protected int cpf;
    protected int salario;

    public Funcionario(String nome, int cpf, int salario) {
        this.nome = nome;
        this.cpf = cpf;
        this.salario = salario;
    }

    public String getNome() {
        return nome;
    }

    public void setNome(String nome) {
        this.nome = nome;
    }

    public int getCpf() {
        return cpf;
    }

    public void setCpf(int cpf) {
        this.cpf = cpf;
    }

    public int getSalario() {
        return salario;
    }

    public void setSalario(int salario) {
        this.salario = salario;
    }

    public void Imprimir() {
        System.out.println("Nome: " + getNome());
        System.out.println("CPF: " + getCpf());
        System.out.println("Salário: " + getSalario());
        System.out.println("Bonificação: " + getBonificacao());
    }

    public double getBonificacao() {
        return getSalario() * 0.10;
    }

}