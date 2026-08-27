class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";

    static int ConverterParaInt(string entrada)
    {
        while (true)
        {
            if (int.TryParse(entrada, out int numero))
            {
                return numero;
            }
            Console.Write("Valor inválido! Digite novamente: ");
            entrada = LeEntrada().Trim();
        }
    }

    static List<int> RetornaListaDePares(List<int> listaOriginal)
    {
        List<int> pares = new List<int>();
        foreach (int valor in listaOriginal)
        {
            if (valor % 2 == 0)
            {
                pares.Add(valor);
            }
        }
        return pares;
    }

    static string ImprimeLista(List<int> listaOriginal) => string.Join(" -> ", listaOriginal);

    static void Main()
    {
        Console.WriteLine("\nDigite números inteiros e eu vou te devolver os apenas os pares.");
        Console.WriteLine("(Pressione ENTER vazio ou digite 'fim' para parar).\n");

        List<int> valores = new List<int>();
        for (int i = 1; ; i++)
        {
            Console.Write($"Digite o {i}º número: ");
            string leitura = LeEntrada().Trim().ToLower();

            if (string.IsNullOrEmpty(leitura) || leitura == "fim")
            {
                break;
            }
            valores.Add(ConverterParaInt(leitura));
        }

        if (valores.Count == 0)
        {
            Console.WriteLine("\nNenhum valor foi digitado.\nPROGRAMA ENCERRADO!\n");
            return;
        }

        List<int> listaDePares = RetornaListaDePares(valores);
        Console.WriteLine($"Lista original: {ImprimeLista(valores)}");
        Console.WriteLine($"Lista só de pares: {ImprimeLista(listaDePares)}");
    }
}