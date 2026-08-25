class Program
{
    static string LeEntrada()
    {
        return Console.ReadLine() ?? "";
    }

    static double ConverterParaDouble(string entrada)
    {
        double numero;
        entrada = entrada.Replace('.', ',');
        while (!double.TryParse(entrada, out numero))
        {
            Console.Write("Valor inválido! Digite novamente: ");
            entrada = Console.ReadLine() ?? "";
            entrada = entrada.Replace('.', ',');
        }
        return numero;
    }

    static double[] InverterArray(double[] arrayEntrada)
    {
        int tamanhoDoArray = arrayEntrada.Length;
        double[] arrayInvertido = new double[tamanhoDoArray];
        foreach (var valor in arrayEntrada)
        {
            arrayInvertido[tamanhoDoArray - 1] = valor;
            tamanhoDoArray--;
        }
        return arrayInvertido;
    }
    static void Main()
    {
        Console.WriteLine("Digite vários números e depois veremos a sua ordem inversa.");
        Console.WriteLine("(Pressione ENTER vazio ou digite 'fim' para parar).\n");
        List<double> valores = new List<double>();
        int i = 0;
        do
        {
            Console.Write($"Digite o {i + 1}º número: ");
            string entrada = LeEntrada().Trim().ToLower();
            if (string.IsNullOrEmpty(entrada) || entrada == "fim")
            {
                break;
            }
            valores.Add(ConverterParaDouble(entrada));
            i++;
        } while (true);
        if (valores.Count == 0)
        {
            Console.WriteLine("\nNenhum valor foi digitado.\nPROGRAMA ENCERRADO!\n");
            return;
        }
        double[] array = valores.ToArray();
        double[] arrayInvertido = InverterArray(array);
        Console.Write($"\nArray original: ");
        foreach (double valor in array)
        {
            Console.Write($"{valor} -> ");
        }
        Console.Write($"\nArray invertido: ");
        foreach (double valor in arrayInvertido)
        {
            Console.Write($"{valor} -> ");
        }
    }
}