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
                Console.WriteLine("ERRO! Digite um número válido!");
            }
        } while (numero <= 0);

        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine($"{i} x {numero} = {i * numero}");
        }
    }
}
