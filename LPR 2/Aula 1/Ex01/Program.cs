class Program
{
    static void Main()
    {
        bool resp;
        double nota1, nota2, nota3;
        Console.Write("Digite o nome do aluno: ");
        string nome = Console.ReadLine() ?? "Não informado";
        do
        {
            Console.Write("Digite a primeira nota: ");
            resp = double.TryParse(Console.ReadLine(), out nota1);
            if (!resp || nota1 < 0)
            {
                Console.WriteLine("ERRO! Digite um número válido!");
            }
            else
            {
                break;
            }
        } while (true);

        do
        {
            Console.Write("Digite a segunda nota: ");
            resp = double.TryParse(Console.ReadLine(), out nota2);
            if (!resp || nota2 < 0)
            {
                Console.WriteLine("ERRO! Digite um número válido!");
            }
            else
            {
                break;
            }
        } while (true);

        do
        {
            Console.Write("Digite a terceira nota: ");
            resp = double.TryParse(Console.ReadLine(), out nota3);
            if (!resp || nota3 < 0)
            {
                Console.WriteLine("ERRO! Digite um número válido!");
            }
            else
            {
                break;
            }
        } while (true);

        double media = (nota1 + nota2 + nota3) / 3;
        Console.WriteLine($"A média foi de {media:F2} pontos.");

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
