using System;
class Program
{
    static void Main()
    {
        Console.Write("Digite o nome do aluno: ");
        string nome = Console.ReadLine() ?? "Não informado";
        Console.Write("Digite a primeira nota: ");
        double.TryParse(Console.ReadLine(), out double nota1);
        Console.Write("Digite a segunda nota: ");
        double.TryParse(Console.ReadLine(), out double nota2);
        Console.Write("Digite a terceira nota: ");
        double.TryParse(Console.ReadLine(), out double nota3);

        double media = (nota1 + nota2 + nota3) / 3;

        if (media >= 60)
        {
            Console.WriteLine($"{nome} está Aprovado!");
        }
        else if (media >= 40)
        {
            Console.WriteLine($"{nome} está de Recuperação!");
        }
        else
        {
            Console.WriteLine($"{nome} está Reprovado!");
        }
    }
}
