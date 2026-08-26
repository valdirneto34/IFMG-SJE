using System.Globalization;

class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";

    static double ConverterParaDouble(string entrada)
    {
        string separadorDoSistema = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;

        while (true)
        {
            entrada = separadorDoSistema == ","
                ? entrada.Replace('.', ',')
                : entrada.Replace(',', '.');

            if (double.TryParse(entrada, out double numero))
            {
                return numero;
            }

            Console.Write("Valor inválido! Digite novamente: ");
            entrada = LeEntrada().Trim();
        }
    }
    static int ContarAcimaDaMedia(double[] valores)
    {
        double soma = 0;
        Console.WriteLine($"\nValores digitados: {ImprimeArray(valores)}");
        foreach (double valor in valores)
        {
            if (!double.IsNaN(valor))
            {
                soma += valor;
            }
        }

        double media = soma / valores.Length;
        Console.WriteLine($"Média: {media:F2}");

        List<double> valoresAcimaDaMedia = new List<double>();
        foreach (double valor in valores)
        {
            if (!double.IsNaN(valor) && valor > media)
            {
                valoresAcimaDaMedia.Add(valor);
            }
        }
        Console.WriteLine($"Valores acima da média: {ImprimeArray(valoresAcimaDaMedia.ToArray())}");
        return valoresAcimaDaMedia.Count;
    }

    static string ImprimeArray(double[] array) => string.Join(" -> ", array);
    static void Main()
    {
        List<double> valores = new List<double>();
        Console.WriteLine("\nDigite vários números para vermos quantos estão acima da média entre eles.");
        Console.WriteLine("(Pressione ENTER vazio ou digite 'fim' para parar antes).\n");

        for (int i = 1; ; i++)
        {
            Console.Write($"Digite o {i}º número: ");
            string entradaTratada = LeEntrada().Trim().ToLower();

            if (string.IsNullOrEmpty(entradaTratada) || entradaTratada == "fim")
            {
                break;
            }
            valores.Add(ConverterParaDouble(entradaTratada));
        }
        if (valores.Count == 0)
        {
            Console.WriteLine("\nNenhum valor foi digitado.\nPROGRAMA ENCERRADO!\n");
            return;
        }
        double[] array = valores.ToArray();
        Console.WriteLine($"Existe(m) {ContarAcimaDaMedia(array)} valor(es) acima da média.");
    }
}