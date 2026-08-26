using System.Globalization;
class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";
    static double LeNumero()
    {
        string separadorDoSistema = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
        double numero;
        do
        {
            string possivelNumero = LeEntrada().Trim();
            possivelNumero = separadorDoSistema == ","
                ? possivelNumero.Replace('.', ',')
                : possivelNumero.Replace(',', '.');
            if (double.TryParse(possivelNumero, out numero))
            {
                return numero;
            }
            else
                Console.Write("Valor inválido! Digite novamente: ");
        } while (true);
    }
    static double Maior(double a, double b)
    {
        return Math.Max(a, b);
    }
    static void Main()
    {
        Console.WriteLine("Digite dois números e veremos qual é o maior!");
        Console.Write("\nDigite o primeiro número: ");
        double a = LeNumero();

        Console.Write("\nDigite o segundo número: ");
        double b = LeNumero();

        double maior = Maior(a, b);
        Console.WriteLine($"\nO maior número entre {a} e {b} é o {maior}");
    }
}