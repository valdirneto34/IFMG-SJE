using System.Globalization;

class Program
{
    static string separadorDoSistema = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
    static string LeEntrada() => Console.ReadLine() ?? "";

    static string LeEntradaNaoVazia(string mensagem)
    {
        while (true)
        {
            Console.Write(mensagem);
            string leitura = LeEntrada().Trim();
            if (!string.IsNullOrEmpty(leitura))
            {
                return leitura;
            }
            Console.WriteLine("\nValor inválido! O campo não pode ser vazio.");
        }
    }
    static double LeNota(string mensagem)
    {
        while (true)
        {
            Console.Write(mensagem);
            string entrada = LeEntrada().Trim();
            entrada = separadorDoSistema == "," ? entrada.Replace('.', ',') : entrada.Replace(',', '.');

            if (!double.TryParse(entrada, out double resultado))
            {
                Console.WriteLine("\nERRO! Digite um valor válido!");
            }
            else if (resultado < 0 || resultado > 10)
            {
                Console.WriteLine("\nERRO! Digite um valor entre 0 a 10!");
            }
            else
            {
                return resultado;
            }
        }
    }

    static double CalcularMedia(double nota1, double nota2) => (nota1 + nota2) / 2;

    static void Main()
    {
        Console.Clear();
        Console.WriteLine("=== CALCULADOR DE MÉDIA ===\n");
        Console.WriteLine("Este programa aceita vírgula ou ponto como separador decimal.\n");

        while (true)
        {
            string nome = LeEntradaNaoVazia("Digite o nome do estudante: ");
            double nota1 = LeNota("Digite a primeira nota: ");
            double nota2 = LeNota("Digite a segunda nota: ");

            double media = CalcularMedia(nota1, nota2);

            Console.WriteLine($"\nNome....: {nome}");
            Console.WriteLine($"Média...: {media:F2}");
            Console.WriteLine($"Situação: {(media >= 6 ? "Aprovado" : media >= 4 ? "Recuperação" : "Reprovado")}!\n");

            string opcao = LeEntradaNaoVazia("Deseja calcular outra média? [s/n]: ").ToLower();
            if (opcao == "n")
            {
                Console.WriteLine("\n--> PROGRAMA ENCERRADO <--\n");
                break;
            }
        }
    }
}