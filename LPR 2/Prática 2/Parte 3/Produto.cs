namespace CatalogoProdutos;

public class Produto
{
    public string Codigo { get; set; } = "";
    public string Nome { get; set; } = "";
    public string Categoria { get; set; } = "";
    public double Preco { get; set; }
    public int Estoque { get; set; }
    public DateTime DataCadastro { get; set; }
    public bool Ativo { get; set; }
    public bool EmPromocao { get; set; }
    public int PorcentoDesconto { get; set; }
    public string CaminhoImagem { get; set; } = "";

    public double PrecoFinal 
    {
        get 
        {
            if (EmPromocao && PorcentoDesconto > 0)
                return Preco - (Preco * (PorcentoDesconto / 100.0));
            
            return Preco;
        }
    }
}