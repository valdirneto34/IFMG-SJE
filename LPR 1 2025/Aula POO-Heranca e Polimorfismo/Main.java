public class Main {
    public static void main(String[] args) {
        Funcionario f = new Funcionario("Valdir", 1, 1518);
        Gerente g = new Gerente(f.getNome(), f.getCpf(), f.getSalario(), "TI");

        f.Imprimir();
        System.out.println();
        
        g.Imprimir();
        System.out.println();
        
        g.alterarInformacao("Fulano", 4, 3200, "Financeiro");
        
        g.Imprimir();
        System.out.println();

    }
}

