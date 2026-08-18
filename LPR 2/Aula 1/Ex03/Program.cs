class Program
{
    static void Main()
    {
        double numero = 0;
        List<double> numeros = new List<double>();
        do
        {
            Console.Write("Digite um número inteiro positivo (0 para SAIR): ");
            bool resultado = double.TryParse(Console.ReadLine(), out numero);
            if (numero == 0)
            {
                break;
            }
            if (!resultado || numero < 0)
            {
                Console.WriteLine("Número inválido! ");
            }
            else
            {
                numeros.Add(numero);
            }
        } while (true);

        int quantidade = numeros.Count;
        double soma = 0;
        double menor = numeros.First();
        double maior = numeros.First();

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

        Console.WriteLine($"Quantidade: {quantidade}");
        Console.WriteLine($"Soma......: {soma}");
        Console.WriteLine($"Média.....: {media:F2}");
        Console.WriteLine($"Menor.....: {menor}");
        Console.WriteLine($"Maior.....: {maior}");
    }
}
