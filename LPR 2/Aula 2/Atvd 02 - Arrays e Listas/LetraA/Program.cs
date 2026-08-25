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
    static int ContarAcimaDaMedia(double[] valores)
    {
        int qtd = 0;
        double soma = 0;
        Console.Write("\nValores digitados: ");
        for (int i = 0; i < valores.Length; i++)
        {
            if (!double.IsNaN(valores[i]))
            {
                soma += valores[i];
                qtd++;
                Console.Write($"{valores[i]} -> ");
            }
        }
        if (qtd == 0) return 0;

        double media = soma / qtd;
        int acimaDaMedia = 0;
        Console.WriteLine($"\nMédia: {media:F2}");
        Console.Write("Valores acima da média: ");
        for (int i = 0; i < valores.Length; i++)
        {
            if (!double.IsNaN(valores[i]) && valores[i] > media)
            {
                acimaDaMedia++;
                Console.Write($"{valores[i]} -> ");
            }
        }
        return acimaDaMedia;
    }
    static void Main()
    {
        List<double> valores = new List<double>();
        Console.WriteLine("Digite vários números para vermos quantos estão acima da média.");
        Console.WriteLine("(Pressione ENTER vazio ou digite 'fim' para parar antes).\n");

        for (int i = 0; i < 10; i++)
        {
            Console.Write($"Digite o {i + 1}º número: ");
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
        int acimaDaMedia = ContarAcimaDaMedia(array);
        Console.WriteLine($"\nExistem {acimaDaMedia} valores acima da média.");
    }
}