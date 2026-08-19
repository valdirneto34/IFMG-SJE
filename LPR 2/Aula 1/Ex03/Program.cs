class Program
{
    static void Main()
    {
        Console.WriteLine("\n==> Digite números para ver a quantidade, a soma, o menor e o maior valor. <==\n");
        List<double> numeros = [];
        bool resultado;
        do
        {
            Console.Write("Digite um número (0 para SAIR): ");
            resultado = double.TryParse(Console.ReadLine(), out double numero);
            if (!resultado)
            {
                Console.Write("Valor inválido! ");
            }
            else
            {
                if (numero == 0)
                {
                    break;
                }
                numeros.Add(numero);
            }
        } while (true);

        int quantidade = numeros.Count;
        double soma = 0;
        double menor, maior;
        try
        {
            menor = numeros.First();
            maior = numeros.First();
        }
        catch (InvalidOperationException)
        {
            Console.WriteLine($"\nERRO: Cálculos impossíveis, pois não existem elementos adicionados!\n");
            return;
        }

        foreach (double num in numeros)
        {
            soma += num;
            if (num < menor)
            {
                menor = num;
            }
            if (num > maior)
            {
                maior = num;
            }
        }
        double media = soma / quantidade;

        Console.WriteLine($"\nQuantidade: {quantidade}");
        Console.WriteLine($"Soma......: {soma}");
        Console.WriteLine($"Média.....: {media:F2}");
        Console.WriteLine($"Menor.....: {menor}");
        Console.WriteLine($"Maior.....: {maior}");
    }
}
