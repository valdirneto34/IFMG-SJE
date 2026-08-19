class Program
{
    static void Main()
    {
        int limite = 100;
        bool[] ehPrimo = new bool[limite + 1];

        Array.Fill(ehPrimo, true);

        ehPrimo[0] = false;
        ehPrimo[1] = false;

        for (int i = 2; i * i <= limite; i++)
        {
            if (ehPrimo[i])
            {
                for (int multiplo = i * i; multiplo <= limite; multiplo += i)
                {
                    ehPrimo[multiplo] = false;
                }
            }
        }

        Console.WriteLine("Números primos de 1 a 100:");
        for (int i = 1; i <= limite; i++)
        {
            if (ehPrimo[i])
            {
                Console.Write($"{i} ");
            }
        }
    }
}