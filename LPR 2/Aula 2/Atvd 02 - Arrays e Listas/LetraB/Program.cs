using System.Globalization;
class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";

    static double ConverterParaDouble(string entrada)
    {
        string separadorDoSistema = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;
        double numero;

        while (true)
        {
            entrada = separadorDoSistema == "," 
                ? entrada.Replace('.', ',') 
                : entrada.Replace(',', '.');

            if (double.TryParse(entrada, out numero))
            {
                return numero;
            }

            Console.Write("Valor inválido! Digite novamente: ");
            entrada = LeEntrada().Trim();
        }
    }

    static double[] InverterArray(double[] arrayEntrada)
    {
        int tamanho = arrayEntrada.Length;
        double[] arrayInvertido = new double[tamanho];
        for (int i = 0; i < tamanho; i++)
        {
            arrayInvertido[tamanho - 1 - i] = arrayEntrada[i];
        }
        return arrayInvertido;
    }

        static string ImprimeArray(double[] array) => string.Join(" -> ", array);

    static void Main()
    {
        Console.WriteLine("\nDigite vários números e depois veremos a sua ordem inversa.");
        Console.WriteLine("(Pressione ENTER vazio ou digite 'fim' para parar).\n");
        List<double> valores = new List<double>();
        for (int i = 1; ; i++)
        {
            Console.Write($"Digite o {i}º número: ");
            string entrada = LeEntrada().Trim().ToLower();
            if (string.IsNullOrEmpty(entrada) || entrada == "fim")
            {
                break;
            }
            valores.Add(ConverterParaDouble(entrada));
        }
        if (valores.Count == 0)
        {
            Console.WriteLine("\nNenhum valor foi digitado.\nPROGRAMA ENCERRADO!\n");
            return;
        }
        double[] array = valores.ToArray();
        double[] arrayInvertido = InverterArray(array);

        Console.WriteLine($"\nArray original: {ImprimeArray(array)}");
        Console.WriteLine($"Array invertido: {ImprimeArray(arrayInvertido)}");
    }
}