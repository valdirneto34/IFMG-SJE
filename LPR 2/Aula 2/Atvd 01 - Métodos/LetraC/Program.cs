class Program
{
    static double LeDouble()
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
    static double CalcularImc(double peso, double altura)
    {
        return peso / (altura * altura);
    }

    static string ClassificarImc(double imc) => imc switch
{
    < 18.5 => "Abaixo do peso",
    < 25.0 => "Peso normal (parabéns!)",
    < 30.0 => "Sobrepeso",
    < 35.0 => "Obesidade Grau I",
    < 40.0 => "Obesidade Grau II",
    _      => "Obesidade Grau III (mórbida)"
};
    static void Main()
    {
        double peso, altura, imc;
        Console.WriteLine("Vamos calcular o seu IMC!");
        Console.Write("\nPrimeiro, digite seu peso (em kg): ");
        peso = LeDouble();

        Console.Write("\nAgora, digite sua altura (em metros): ");
        altura = LeDouble();
        if(altura > 3.0)
        {
            altura /= 100;
        }

        imc = CalcularImc(peso, altura);
        Console.WriteLine($"\nO seu IMC é {imc:F2}");
        Console.WriteLine($"Classificação: {ClassificarImc(imc)}");
    }
}