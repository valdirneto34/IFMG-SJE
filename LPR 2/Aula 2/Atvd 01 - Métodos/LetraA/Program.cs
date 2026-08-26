class Program
{
    static bool EhPar(int numero)
    {
        if (numero % 2 == 0)
        {
            return true;
        }
        return false;
    }
    static void Main()
    {
        int numero;
        Console.Write("Digite um número inteiro para verificar se ele é par: ");
        while (!int.TryParse(Console.ReadLine(), out numero))
        {
            Console.Write("Valor inválido! Digite novamente: ");
        }

        bool ehPar = EhPar(numero);
        if (ehPar)
        {
            Console.WriteLine($"O número {numero} é par!");
        }
        else
        {
            Console.WriteLine($"O número {numero} não é par!");
        }
    }
}