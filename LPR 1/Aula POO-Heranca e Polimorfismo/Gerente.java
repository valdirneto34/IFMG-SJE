public class Gerente extends Funcionario {

    private String setorResponsavel;

    public Gerente(String nome, int cpf, int salario, String setorResponsavel) {
        super(nome, cpf, salario);
        this.setorResponsavel = setorResponsavel;
    }

    public String getSetorResponsavel() {
        return setorResponsavel;
    }

    public void setSetorResponsavel(String setorResponsavel) {
        this.setorResponsavel = setorResponsavel;
    }

    @Override
    public void Imprimir() {
        super.Imprimir();
        System.out.println("Setor responsável: " + getSetorResponsavel());
    }

    public void alterarInformacao(String nome, int cpf, int salario, String setsetorResponsavelor) {
        setNome(nome);
        setCpf(cpf);
        setSalario(salario);
        setSetorResponsavel(setorResponsavel);
    }

    @Override
    public double getBonificacao() {
        return getSalario() * 0.15 + 1000;
    }

}
