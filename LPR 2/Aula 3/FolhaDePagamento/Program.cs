interface IBonificavel
{
    double CalcularBonus();
}

abstract class Funcionario : IBonificavel
{
    public string Nome { get; } = "";
    public double SalarioBase { get; }

    public Funcionario(string nome, double salarioBase)
    {
        if (string.IsNullOrWhiteSpace(nome))
        {
            throw new ArgumentException("Nome não pode ser vazio!");
        }
        if (salarioBase < 0)
        {
            throw new ArgumentOutOfRangeException("Salário deve ser maior ou igual a zero!");
        }
        Nome = nome;
        SalarioBase = salarioBase;
    }
    public virtual double CalcularBonus() => SalarioBase * 0.05;

    public double CalcularPagamento() => SalarioBase + CalcularBonus();

    public void ExibirResumo()
    {
        Console.WriteLine($"Nome........: {Nome}");
        Console.WriteLine($"Salário base: {SalarioBase:C}");
    }

    public void ExibirResumo(bool detalhado)
    {
        ExibirResumo();
        if (detalhado)
        {
            Console.WriteLine($"Bônus.......: {CalcularBonus():C}");
            Console.WriteLine($"Pagamento...: {CalcularPagamento():C}");
        }
    }
}

class Gerente : Funcionario
{
    public Gerente(string nome, double salarioBase) : base(nome, salarioBase)
    {
    }

    public override double CalcularBonus() => SalarioBase * 0.15;
}

class Desenvolvedor : Funcionario
{
    public Desenvolvedor(string nome, double salarioBase) : base(nome, salarioBase)
    {
    }

    public override double CalcularBonus() => SalarioBase * 0.1;
}

class Program
{
    static void Main()
    {
        Funcionario[] equipe =
        {
          new Gerente("Ana", 5000),
          new Desenvolvedor("Bruno", 4000)
        };

        foreach (Funcionario funcionario in equipe)
        {
            Console.WriteLine("------ RESUMO SIMPLES ------");
            funcionario.ExibirResumo();
            Console.WriteLine("----------------------------");
            Console.WriteLine("----- RESUMO DETALHADO -----");
            funcionario.ExibirResumo(true);
            Console.WriteLine("----------------------------\n");
        }
    }
}