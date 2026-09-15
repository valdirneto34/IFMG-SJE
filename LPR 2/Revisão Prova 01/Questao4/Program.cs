using System.Globalization;

class Program
{
    static string separadorDoSistema = CultureInfo.CurrentCulture.NumberFormat.NumberDecimalSeparator;

    static string LeEntrada() => Console.ReadLine() ?? "";

    static string LeStringObrigatoria(string mensagem)
    {
        while (true)
        {
            Console.Write(mensagem);
            string leitura = LeEntrada().Trim();
            if (!string.IsNullOrEmpty(leitura))
            {
                return leitura;
            }
            Console.WriteLine("\nValor inválido! O campo não pode ser vazio.");
        }
    }

    static int LerInteiro(string mensagem)
    {
        while (true)
        {
            Console.Write(mensagem);
            string entrada = LeEntrada().Trim();

            if (int.TryParse(entrada, out int resultado))
            {
                return resultado;
            }
            Console.WriteLine("\nERRO! Digite um valor válido!");
        }
    }

    static decimal LerDecimal(string mensagem)
    {
        while (true)
        {
            Console.Write(mensagem);
            string entrada = LeEntrada().Trim();
            entrada = separadorDoSistema == "," ? entrada.Replace(".", ",") : entrada.Replace(",", ".");

            if (!decimal.TryParse(entrada, out decimal resultado))
            {
                Console.WriteLine("\nERRO! Digite um número!");
            }
            else if (resultado < 0)
            {
                Console.WriteLine("\nERRO! Digite um valor maior ou igual a 0!");
            }
            else
            {
                return resultado;
            }
        }
    }

    static int Menu()
    {
        Console.WriteLine("\n======> MENU <=====");
        Console.WriteLine("0 - Sair");
        Console.WriteLine("1 - Cadastrar preço");
        Console.WriteLine("2 - Consultar preço");
        Console.WriteLine("======> MENU <=====");
        return LerInteiro("Digite sua opção: ");
    }

    static void CadastrarPreco(Dictionary<string, decimal> produtos)
    {
        string codigo = LeStringObrigatoria("\nDigite o código do produto: ").ToUpper();
        if (produtos.ContainsKey(codigo))
        {
            Console.WriteLine($"\nERRO! Produto com o código \"{codigo}\" já existe.");
            return;
        }

        decimal preco = LerDecimal("Digite o preço do produto: ");
        produtos.Add(codigo, preco);
        Console.WriteLine("\nPRODUTO CADASTRADO COM SUCESSO!");
    }

    static void ConsultarPreco(Dictionary<string, decimal> produtos)
    {
        string codigo = LeStringObrigatoria("\nDigite o código do produto: ").ToUpper();
        if (produtos.TryGetValue(codigo, out decimal preco))
        {
            Console.WriteLine($"\nProduto encontrado (Código: {codigo} | Preço: {preco:C})");
        }
        else
        {
            Console.WriteLine($"\nERRO! Produto com o código \"{codigo}\" não foi encontrado.");
        }

    }
    static void Main()
    {
        Console.Clear();
        Console.WriteLine("=== CONSULTA DE PREÇOS ===\n");
        Console.WriteLine("Este programa aceita vírgula ou ponto como separador decimal.");

        Dictionary<string, decimal> produtos = new Dictionary<string, decimal>();

        while (true)
        {
            int opcao = Menu();
            switch (opcao)
            {
                case 0:
                    Console.WriteLine("\n--> PROGRAMA ENCERRADO <--\n");
                    return;
                case 1:
                    CadastrarPreco(produtos);
                    break;
                case 2:
                    ConsultarPreco(produtos);
                    break;
                default:
                    Console.WriteLine("\nOPÇÃO INVÁLIDA\n");
                    break;
            }
        }
    }
}