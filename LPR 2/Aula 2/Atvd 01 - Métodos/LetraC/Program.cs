using System.Globalization;
class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";
    static double LeDouble()
    {
        string separadorDoSistema = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
        while (true)
        {
            string possivelNumero = LeEntrada().Trim();

            possivelNumero = separadorDoSistema == ","
                ? possivelNumero.Replace('.', ',')
                : possivelNumero.Replace(',', '.');

            if (double.TryParse(possivelNumero, out double numero))
            {
                return numero;
            }
            Console.Write("Valor inválido! Digite novamente: ");
        }
    }
    static double CalcularImc(double peso, double altura) => peso / Math.Pow(altura, 2);


    static string ClassificarImc(double imc) => imc switch
    {
        < 18.5 => "Abaixo do peso",
        < 25.0 => "Peso normal (parabéns!)",
        < 30.0 => "Sobrepeso",
        < 35.0 => "Obesidade Grau I",
        < 40.0 => "Obesidade Grau II",
        _ => "Obesidade Grau III (mórbida)"
    };
    static void Main()
    {
        Console.WriteLine("\nVamos calcular o seu IMC!");

        Console.Write("\nPrimeiro, digite seu peso (em kg): ");
        double peso = LeDouble();

        Console.Write("\nAgora, digite sua altura (em metros): ");
        double altura = LeDouble();

        if (altura > 3.0)
        {
            altura /= 100;
        }

        double imc = CalcularImc(peso, altura);
        Console.WriteLine($"\nO seu IMC é {imc:F2}");
        Console.WriteLine($"Classificação: {ClassificarImc(imc)}");
    }
}