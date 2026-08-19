class Program
{
    static void Main()
    {
        int numero;
        do
        {
            Console.Write("Digite um número inteiro positivo: ");
            bool resultado = int.TryParse(Console.ReadLine(), out numero);
            if (!resultado || numero <= 0)
            {
                Console.WriteLine("ERRO! Digite um valor válido!");
            }
        } while (numero <= 0);

        Console.WriteLine($"------ TABUADA DO {numero} ------");
        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine($"{numero} x {i} = {i * numero}");
        }
        Console.WriteLine($"---------------------------------");
    }
}
