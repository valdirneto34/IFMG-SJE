using System;
class Program
{
    static void Main()
    {
        int numero = 0;
        do
        {
            Console.Write("Digite um número inteiro positivo: ");
            int.TryParse(Console.ReadLine(), out numero);
        } while (numero <= 0);

        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine($"{i} x {numero} = {i * numero}");
        }
    }
}
