class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";

    static int LeInteiro(string mensagem)
    {
        while (true)
        {
            Console.Write(mensagem);
            string entrada = LeEntrada().Trim();

            if (int.TryParse(entrada, out int resultado))
            {
                return resultado;
            }
            Console.WriteLine("\nERRO! Digite um valor válido!");
        }
    }

    static int Somar(int[] numeros)
    {
        int soma = 0;
        for (int i = 0; i < numeros.Length; i++)
        {
            soma += numeros[i];
        }
        return soma;
    }

    static int EncontrarMaior(int[] numeros)
    {
        int maior = numeros[0];
        for (int i = 1; i < numeros.Length; i++)
        {
            if (numeros[i] > maior)
            {
                maior = numeros[i];
            }
        }
        return maior;
    }

    static double CalcularMedia(int[] numeros)
    {
        return (double)Somar(numeros) / numeros.Length;
    }

    static int ContarNumerosPares(int[] numeros)
    {
        int numerosPares = 0;
        for (int i = 0; i < numeros.Length; i++)
        {
            if (numeros[i] % 2 == 0)
                numerosPares++;
        }
        return numerosPares;
    }

    static string ExibirNaOrdemDeLeitura(int[] numeros)
    {
        string resposta = $"{numeros[0]}";
        for (int i = 1; i < numeros.Length; i++)
        {
            resposta += $" -> {numeros[i]}";
        }
        return resposta;
    }

    static void Main()
    {
        Console.Clear();
        Console.WriteLine("=== ANÁLISE DE CINCO NÚMEROS ===\n");

        int[] numeros = new int[5];
        for (int i = 0; i < 5; i++)
        {
            numeros[i] = LeInteiro($"Digite o {i + 1}° número: ");
        }

        Console.WriteLine($"\nNúmeros na ordem de leitura: {ExibirNaOrdemDeLeitura(numeros)}");
        Console.WriteLine($"Soma dos números: {Somar(numeros)}");
        Console.WriteLine($"Média dos números: {CalcularMedia(numeros):F2}");
        Console.WriteLine($"Maior dos números: {EncontrarMaior(numeros)}");
        Console.WriteLine($"Quantidade de números pares: {ContarNumerosPares(numeros)}");
    }
}