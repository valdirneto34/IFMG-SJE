using System.Reflection.Emit;

class Program
{
    static string LeEntrada() => Console.ReadLine() ?? "";

    static void LeEntradaParaAgenda(out string leitura)
    {
        leitura = LeEntrada().Trim();
        while (leitura == "" || string.IsNullOrEmpty(leitura))
        {
            Console.Write("Valor inválido! Digite novamente: ");
            leitura = LeEntrada().Trim();
        }
    }

    static void LeNumeroTelefone(out string numero)
    {
        while (true)
        {
            LeEntradaParaAgenda(out numero);
            numero = numero.Replace(" ", "").Replace("-", "");

            if (numero.All(char.IsDigit))
            {
                break;
            }
            Console.Write("Número inválido (não digite letras)! Digite novamente: ");
        }
    }

    static int ConverteParaInt(string entrada)
    {
        while (true)
        {
            if (int.TryParse(entrada, out int numero))
            {
                return numero;
            }
            Console.Write("Valor inválido! Digite novamente: ");
            entrada = LeEntrada().Trim();
        }
    }

    static void PausarELimpar()
    {
        Console.WriteLine("\nPressione qualquer tecla para continuar...");
        Console.ReadKey(true);
        Console.Clear();
    }
    static void CadastrarContato(Dictionary<string, string> agenda)
    {
        Console.Write("Digite o nome do contato: ");
        LeEntradaParaAgenda(out string nomeContato);
        Console.Write("Digite o número do contato: ");
        LeNumeroTelefone(out string numeroContato);
        if (agenda.TryAdd(nomeContato, numeroContato))
        {
            Console.WriteLine($"\nContato ({nomeContato}, {numeroContato}) cadastrado com sucesso!");
        }
        else
        {
            Console.WriteLine($"\nO nome '{nomeContato}' já existe na sua agenda!");

        }
    }

    static void ConsultarContato(Dictionary<string, string> agenda)
    {
        if (agenda.Count == 0)
        {
            Console.WriteLine("ERRO: A agenda está vazia!");
            return;
        }
        Console.Write("Digite o nome do contato que deseja consultar: ");
        LeEntradaParaAgenda(out string nomeContato);
        if (agenda.TryGetValue(nomeContato, out string? numeroContato))
        {
            Console.WriteLine("\nContato encontrado!");
            Console.WriteLine($"Nome: {nomeContato} | Número: {numeroContato}");
        }
        else
        {
            Console.WriteLine($"\nContato com o nome '{nomeContato}' não encontrado!");

        }
    }

    static void AtualizarContato(Dictionary<string, string> agenda)
    {
        if (agenda.Count == 0)
        {
            Console.WriteLine("ERRO: A agenda está vazia!");
            return;
        }
        Console.Write("Digite o nome do contato que deseja atualizar: ");
        LeEntradaParaAgenda(out string nomeContato);
        if (agenda.TryGetValue(nomeContato, out string? numeroContato))
        {
            Console.Write("Digite o novo número do contato: ");
            LeNumeroTelefone(out string novoNumeroContato);
            agenda[nomeContato] = novoNumeroContato;
            Console.WriteLine("\nContato atualizado com sucesso!");
            Console.WriteLine($"Nome: {nomeContato} | Número antigo: {numeroContato}");
            Console.WriteLine($"Nome: {nomeContato} | Número atualizado: {novoNumeroContato}");
        }
        else
        {
            Console.WriteLine($"\nContato com o nome '{nomeContato}' não encontrado!");

        }
    }

    static void RemoverContato(Dictionary<string, string> agenda)
    {
        if (agenda.Count == 0)
        {
            Console.WriteLine("ERRO: A agenda está vazia!");
            return;
        }
        Console.Write("Digite o nome do contato que deseja remover: ");
        LeEntradaParaAgenda(out string nomeContato);
        if (agenda.Remove(nomeContato))
        {
            Console.WriteLine($"\nContato com o nome '{nomeContato}' removido com sucesso!");
        }
        else
        {
            Console.WriteLine($"\nContato com o nome '{nomeContato}' não encontrado!");
        }
    }

    static void ImprimirContatos(Dictionary<string, string> agenda)
    {
        if (agenda.Count == 0)
        {
            Console.WriteLine("ERRO: A agenda está vazia!");
            return;
        }

        int larguraColunaNome = agenda.Keys.Max(nome => nome.Length);
        larguraColunaNome = Math.Max(larguraColunaNome, 15);

        Console.WriteLine($"{"NOME".PadRight(larguraColunaNome)} | NÚMERO");
        Console.WriteLine(new string('-', larguraColunaNome + 15));

        foreach (var item in agenda)
        {
            Console.WriteLine($"{item.Key.PadRight(larguraColunaNome)} | {item.Value}");
        }
    }

    static int ImprimeMenu()
    {
        Console.WriteLine("========== MENU ==========");
        Console.WriteLine("0 - Encerrar Programa");
        Console.WriteLine("1 - Cadastrar Contato");
        Console.WriteLine("2 - Consultar Contato");
        Console.WriteLine("3 - Atualizar Contato");
        Console.WriteLine("4 - Remover Contato");
        Console.WriteLine("5 - Imprimir Contatos");
        Console.WriteLine("==========================");
        Console.Write("Digite sua escolha: ");
        string leitura = LeEntrada().Trim();
        return ConverteParaInt(leitura);
    }
    static void Main()
    {
        Console.Clear();
        Console.WriteLine("\nPrograma que cadastra, consulta, atualiza e remove contatos de uma agenda.\n");
        Dictionary<string, string> agenda = new Dictionary<string, string>();
        do
        {
            int opcao = ImprimeMenu();
            Console.WriteLine();
            switch (opcao)
            {
                case 0:
                    Console.WriteLine("PROGRAMA ENCERRADO!");
                    return;
                case 1:
                    CadastrarContato(agenda);
                    break;
                case 2:
                    ConsultarContato(agenda);
                    break;
                case 3:
                    AtualizarContato(agenda);
                    break;
                case 4:
                    RemoverContato(agenda);
                    break;
                case 5:
                    ImprimirContatos(agenda);
                    break;
                default:
                    Console.WriteLine("OPÇÃO INVÁLIDA!");
                    break;
            }
            PausarELimpar();
        } while (true);
    }
}