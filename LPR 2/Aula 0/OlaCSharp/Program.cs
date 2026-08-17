using System;
class Program
{
    static void Main()
    {
        Console.WriteLine("Olá, C#!");
        Console.Write("Digite seu nome: ");
        string nome = Console.ReadLine()?? "User";
        Console.WriteLine($"Bem-vindo, {nome}!");
    }
}
