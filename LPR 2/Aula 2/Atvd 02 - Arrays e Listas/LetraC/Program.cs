class Program
{
    static string LeEntrada()
    {
        return Console.ReadLine() ?? "";
    }

    static double ConverterParaInt(string entrada)
    {
        int numero;
        entrada = entrada.Replace('.', ',');
        while (!int.TryParse(entrada, out numero))
        {
            Console.Write("Valor inválido! Digite novamente: ");
            entrada = Console.ReadLine() ?? "";
            entrada = entrada.Replace('.', ',');
        }
        return numero;
    }

    static List<double> RetornaListaDePares(List<double> listaOriginal)
    {
        List<double> pares = new List<double>();
        foreach (double valor in listaOriginal)
        {
            if (valor % 2 == 0)
            {
                pares.Add(valor);
            }
        }
    }

    static void Main()
    {
        Console.WriteLine("Digite números inteiros e eu vou te devolver os apenas os pares.");
        Console.WriteLine("(Pressione ENTER vazio ou digite 'fim' para parar).\n");
        List<int> valores = new List<int>();
        do
        {
            string leitura = LeEntrada();
            string leitura = LeEntrada().Trim().ToLower();
            if (string.IsNullOrEmpty(leitura) || leitura == "fim")
            {
                break;
            }
            valores.Add(ConverterParaInt(leitura));
        } while (true);
        if (valores.Count == 0)
        {
            Console.WriteLine("\nNenhum valor foi digitado.\nPROGRAMA ENCERRADO!\n");
            return;
        }
    }
}