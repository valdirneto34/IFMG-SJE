using System;
class Program
{
    static void Main()
    {
        double numero = 0;
        double[] valores;
        do
        {
            Console.Write("Digite um número inteiro positivo: ");
            double.TryParse(Console.ReadLine(), out valores.a);
        } while (numero != 0);

        for (int i = 1; i <= 10; i++)
        {
            Console.WriteLine($"{i} x {numero} = {i * numero}");
        }
    }
}
