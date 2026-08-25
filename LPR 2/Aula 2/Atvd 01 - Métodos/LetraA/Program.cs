class Program
{
    static bool EhPar(int numero)
    {
        if(numero % 2 == 0)
        {
            return true;
        }
        return false;
    }
    static void Main()
    {
        bool ehInteiro;
        int numero;
        Console.Write("Digite um número inteiro para verificar se ele é par: ");
        do
        {
        ehInteiro = int.TryParse(Console.ReadLine(), out numero);
            if (!ehInteiro)
            {
                Console.Write("Valor inválido! Digite novamente: ");
            }
            else
            {
                break;
            }
        } while (true);

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