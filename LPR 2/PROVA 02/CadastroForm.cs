using System.ComponentModel;
namespace CatalogoProdutos;

public partial class CadastroForm : Form
{
    private readonly BindingList<Produto> produtos = new();
    private Produto? produtoEmEdicao;

    public CadastroForm()
    {
        MontarTela();
        grade.DataSource = produtos;
        erros.ContainerControl = this;
        ConectarEventos();
        PrepararNovo();
    }

    private void ConectarEventos()
    {
        btnNovo.Click += NovoProduto;
        btnSalvar.Click += SalvarProduto;
        btnExcluir.Click += ExcluirProduto;

        grade.CellClick += SelecionarProduto;

        menuSortear.Click += SortearDestaque;
        menuFechar.Click += (s, e) => Close();
    }

    private void NovoProduto(object? sender, EventArgs args)
    {
        PrepararNovo();
    }

    private void PrepararNovo()
    {
        produtoEmEdicao = null;
        txtCodigo.Clear();
        txtNome.Clear();
        cmbCategoria.SelectedIndex = 0;
        txtPreco.Clear();
        rdbDisponivel.Checked = true;
        numEstoque.Value = 0;

        grade.ClearSelection();
        erros.Clear();

        btnSalvar.Text = "Salvar";
        btnExcluir.Enabled = false;

        txtCodigo.Focus();
    }

    private bool ValidarCampos()
    {
        erros.Clear();
        if (txtCodigo.Text.Trim().Length == 0)
        {
            MessageBox.Show("O código do produto não pode ser vazio.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtCodigo.Focus();
            return false;
        }
        else
        {
            foreach (Produto p in produtos)
            {
                if (p.Codigo == txtCodigo.Text.Trim() && produtoEmEdicao == null)
                {
                    MessageBox.Show("Já existe um produto com este código.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    txtCodigo.Focus();
                    return false;
                }
            }
        }

        if (txtNome.Text.Trim().Length < 3)
        {
            MessageBox.Show("O nome do produto deve ter no mínimo 3 caracteres.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtNome.Focus();
            return false;
        }

        if (!double.TryParse(txtPreco.Text.Trim(), out double precoValor) || precoValor < 0)
        {
            MessageBox.Show("Preço inválido.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtPreco.Focus();
            return false;
        }
        if (txtPreco.Text.Trim().Contains('.'))
        {
            MessageBox.Show("Digite o preço com vírgula \",\".", "Preço inválido.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtPreco.Focus();
            return false;
        }

        if (cmbCategoria.SelectedIndex < 0)
        {
            MessageBox.Show("Selecione uma categoria válida.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            cmbCategoria.Focus();
            return false;
        }

        if ((int)numEstoque.Value < 0)
        {
            MessageBox.Show("Estoque não pode ser menor do que zero.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            numEstoque.Focus();
            return false;
        }
        return true;
    }

    private void SalvarProduto(object? sender, EventArgs args)
    {
        if (!ValidarCampos())
            return;

        string codigo = txtCodigo.Text.Trim();
        string nome = txtNome.Text.Trim();
        string categoria = cmbCategoria.SelectedItem?.ToString() ?? "";
        double preco = double.Parse(txtPreco.Text.Trim());
        bool disponivel = rdbDisponivel.Checked;
        int estoque = (int)numEstoque.Value;
        if (estoque <= 0)
            disponivel = false;

        if (produtoEmEdicao is null)
        {
            produtos.Add(new Produto
            {
                Codigo = codigo,
                Nome = nome,
                Categoria = categoria,
                Preco = preco,
                Disponivel = disponivel,
                Estoque = estoque,
            });
        }
        else
        {
            produtoEmEdicao.Codigo = codigo;
            produtoEmEdicao.Nome = nome;
            produtoEmEdicao.Categoria = categoria;
            produtoEmEdicao.Preco = preco;
            produtoEmEdicao.Estoque = estoque;
            produtoEmEdicao.Disponivel = disponivel;

            produtos.ResetItem(produtos.IndexOf(produtoEmEdicao));
        }
        PrepararNovo();
    }

    private void SelecionarProduto(object? sender, DataGridViewCellEventArgs args)
    {
        if (args.RowIndex < 0)
            return;

        var produto = grade.Rows[args.RowIndex].DataBoundItem as Produto;
        if (produto is null)
            return;

        produtoEmEdicao = produto;

        txtCodigo.Text = produtoEmEdicao.Codigo;
        txtNome.Text = produtoEmEdicao.Nome;
        cmbCategoria.SelectedItem = produtoEmEdicao.Categoria;
        txtPreco.Text = produtoEmEdicao.Preco.ToString("F2");
        numEstoque.Value = produtoEmEdicao.Estoque;

        if (produtoEmEdicao.Disponivel)
        {
            rdbDisponivel.Checked = true;
        }
        else
        {
            rdbIndisponivel.Checked = true;
        }

        btnSalvar.Text = "Atualizar";
        btnExcluir.Enabled = true;
        erros.Clear();
    }

    private void ExcluirProduto(object? sender, EventArgs args)
    {
        if (produtoEmEdicao is null)
            return;

        DialogResult resposta = MessageBox.Show(this,
        $"Excluir {produtoEmEdicao.Nome}?", "Confirmar exclusão",
        MessageBoxButtons.YesNo, MessageBoxIcon.Question,
        MessageBoxDefaultButton.Button2);

        if (resposta != DialogResult.Yes)
            return;

        produtos.Remove(produtoEmEdicao);
        PrepararNovo();
    }

    private void SortearDestaque(object? sender, EventArgs args)
    {
        int qtdProdutos = produtos.Count;
        var geraAleatorio = new Random();
        if (qtdProdutos == 0)
        {
            MessageBox.Show("Ainda não há produtos para destacar.", "Sem Produtos Cadastrados", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            return;
        }
        int indexAleatorio = geraAleatorio.Next(0, qtdProdutos);
        Produto produto = produtos[indexAleatorio];
        string msg = $"Nome: {produto.Nome} | Preço: {produto.Preco} | Estoque: {produto.Estoque}";
        MessageBox.Show(msg, "Produto Destacado", MessageBoxButtons.OK);
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
            erros.Dispose();
        base.Dispose(disposing);
    }
}