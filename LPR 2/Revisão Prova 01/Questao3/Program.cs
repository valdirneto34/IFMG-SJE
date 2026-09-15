class Program
{
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
    static int Menu()
    {
        Console.WriteLine("\n======> MENU <=====");
        Console.WriteLine("0 - Sair\t\t2 - Listar itens");
        Console.WriteLine("1 - Adicionar item\t3 - Remover item");
        Console.WriteLine("======> MENU <=====");
        return LerInteiro("Digite sua opção: ");
    }

    static void AdicionarNome(List<string> lista)
    {
        string novoNome = LeStringObrigatoria("Digite o item a ser adicionado: ");
        lista.Add(novoNome);
        Console.WriteLine("\nITEM ADICIONADO COM SUCESSO!");
    }

    static void ListarNomes(List<string> lista)
    {
        if (lista.Count == 0)
        {
            Console.WriteLine("ERRO! Lista está vazia.");
            return;
        }

        Console.WriteLine("\n-----> LISTA DE ITENS <-----");
        for (int i = 0; i < lista.Count; i++)
        {
            Console.WriteLine($"{i + 1}° -> {lista[i]}");
        }
        Console.WriteLine($"# QUANTIDADE TOTAL: {lista.Count}");
        Console.WriteLine("----------------------------");
    }

    static void RemoverNome(List<string> lista)
    {
        if (lista.Count == 0)
        {
            Console.WriteLine("ERRO! Lista está vazia.");
            return;
        }

        int posicaoParaRemover = LerInteiro("Digite a posição do item a ser removido: ");
        if (posicaoParaRemover < 1 || posicaoParaRemover > lista.Count)
        {
            Console.WriteLine("ERRO! Posição não existe.");
            return;
        }

        lista.RemoveAt(posicaoParaRemover - 1);
        Console.WriteLine("\nITEM REMOVIDO COM SUCESSO!");
    }

    static void Main()
    {
        List<string> lista = new List<string>();
        while (true)
        {
            int opcao = Menu();
            switch (opcao)
            {
                case 0:
                    Console.WriteLine("\n--> PROGRAMA ENCERRADO <--\n");
                    return;
                case 1:
                    AdicionarNome(lista);
                    break;
                case 2:
                    ListarNomes(lista);
                    break;
                case 3:
                    RemoverNome(lista);
                    break;
                default:
                    Console.WriteLine("\nOPÇÃO INVÁLIDA\n");
                    break;
            }
        }
    }
}