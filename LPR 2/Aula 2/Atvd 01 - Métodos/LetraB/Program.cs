class Program
{

    static double LeNumero()
    {
        double numero;
        do
        {
            string possivelNumero = Console.ReadLine() ?? "";
            possivelNumero = possivelNumero.Replace('.', ',');
            bool ehDouble = double.TryParse(possivelNumero, out numero);
            if (!ehDouble)
            {
                Console.Write("Valor inválido! Digite novamente: ");
            }
            else
            {
                break;
            }
        } while (true);
        return numero;
    }
    static double Maior(double a, double b)
    {
        if (a >= b)
        {
            return a;
        }
        return b;
    }
    static void Main()
    {
        double a, b, maior;
        Console.WriteLine("Digite dois números e veremos qual é o maior!");
        Console.Write("\nDigite o primeiro número: ");
        a = LeNumero();

        Console.Write("\nDigite o segundo número: ");
        b = LeNumero();
        
        maior = Maior(a, b);
        Console.WriteLine($"\nO maior número entre {a} e {b} é o {maior}");
    }
}