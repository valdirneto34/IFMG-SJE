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
        btnPesquisar.Click += PesquisarProduto;
        btnLimparFiltros.Click += LimparFiltros;

        btnNovo.Click += NovoProduto;
        btnSalvar.Click += SalvarProduto;
        btnExcluir.Click += ExcluirProduto;
        grade.CellClick += SelecionarProduto;

        btnCancelar.Click += CancelarEdicao;
        btnFechar.Click += (s, e) => Close();
    }

    private void PesquisarProduto(object? sender = null, EventArgs? args = null)
    {
        string nomeOuCodigo = txtPesquisa.Text.Trim().ToLower();
        string categoria = cmbCategoria.SelectedItem?.ToString() ?? "";
        bool somenteEstoque = chkAtivo.Checked;

        BindingList<Produto> produtosEncontrados = new();

        foreach (Produto p in produtos)
        {
            bool atendePesquisa = string.IsNullOrEmpty(nomeOuCodigo) ||
                              p.Nome.ToLower().Contains(nomeOuCodigo) ||
                              p.Codigo.ToLower().Contains(nomeOuCodigo);
            bool atendeCategoria = categoria == "Todas" || p.Categoria == categoria;
            bool atendeEstoque = !somenteEstoque || p.Estoque > 0;
            if (atendePesquisa && atendeCategoria && atendeEstoque)
                produtosEncontrados.Add(p);
        }
        if (produtos.Count == 0)
        {
            lblResultado.Text = "Nenhum produto cadastrado";
        }
        else
        {
            lblResultado.Text = $"{produtos.Count} {(produtos.Count > 1 ? "produtos cadastrados" : "produto cadastrado")}";
        }
        grade.DataSource = produtosEncontrados;
    }

    private void LimparFiltros(object? sender, EventArgs args)
    {
        txtPesquisa.Clear();
        cmbCategoria.SelectedIndex = 0;
        chkAtivo.Checked = false;
        grade.DataSource = produtos;
        txtPesquisa.Focus();

        if (produtos.Count == 0)
        {
            lblResultado.Text = "Nenhum produto cadastrado";
        }
        else
        {
            lblResultado.Text = $"{produtos.Count} {(produtos.Count > 1 ? "produtos cadastrados" : "produto cadastrado")}";
        }
    }

    private void NovoProduto(object? sender, EventArgs args)
    {
        PrepararNovo();
    }

    private void PrepararNovo()
    {
        produtoEmEdicao = null;
        txtNome.Clear();
        txtCodigo.Clear();
        txtPreco.Clear();
        txtPesquisa.Clear();
        numEstoque.Value = 0;
        dtpDataCadastro.Value = DateTime.Now;
        chkPromocao.Checked = false;
        rdbAtivo.Checked = true;

        cmbCategoriaForm.SelectedIndex = 0;

        grade.ClearSelection();
        erros.Clear();

        btnSalvar.Text = "Salvar";
        btnExcluir.Enabled = false;
        txtCodigo.Focus();
    }
    private bool ValidarCampos()
    {
        erros.Clear();
        if (txtNome.Text.Trim().Length < 3)
        {
            MessageBox.Show("O nome do produto deve ter no mínimo 3 caracteres.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtNome.Focus();
            return false;
        }

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
        if (cmbCategoriaForm.SelectedIndex < 0)
        {
            MessageBox.Show("Selecione uma categoria válida.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            cmbCategoriaForm.Focus();
            return false;
        }

        if (!double.TryParse(txtPreco.Text.Trim(), out double precoValor) || precoValor < 0)
        {
            MessageBox.Show("Preço inválido.", "Erro de Validação", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtPreco.Focus();
            return false;
        }

        if (txtPreco.Text.Trim().Contains("."))
        {
            MessageBox.Show("Digite o preço com \",\"", "Preço inválido.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtPreco.Focus();
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
        string categoria = cmbCategoriaForm.SelectedItem?.ToString() ?? "";
        double preco = double.Parse(txtPreco.Text.Trim());
        int estoque = (int)numEstoque.Value;
        DateTime dataCadastro = dtpDataCadastro.Value;
        bool ativo = rdbAtivo.Checked;
        bool emPromocao = chkPromocao.Checked;
        bool novoCadastro = produtoEmEdicao is null;


        if (produtoEmEdicao is null)
        {
            produtos.Add(new Produto
            {
                Codigo = codigo,
                Nome = nome,
                Categoria = categoria,
                Preco = preco,
                Estoque = estoque,
                DataCadastro = dataCadastro,
                Ativo = ativo,
                EmPromocao = emPromocao
            });
        }
        else
        {
            produtoEmEdicao.Codigo = codigo;
            produtoEmEdicao.Nome = nome;
            produtoEmEdicao.Categoria = categoria;
            produtoEmEdicao.Preco = preco;
            produtoEmEdicao.Estoque = estoque;
            produtoEmEdicao.DataCadastro = dataCadastro;
            produtoEmEdicao.Ativo = ativo;
            produtoEmEdicao.EmPromocao = emPromocao;

            produtos.ResetItem(produtos.IndexOf(produtoEmEdicao));
        }
        PrepararNovo();
        if (novoCadastro)
            MessageBox.Show($"Produto '{nome}' cadastrado!", "Sucesso no Cadastro", MessageBoxButtons.OK, MessageBoxIcon.Information);
        PesquisarProduto();
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
        txtPreco.Text = produtoEmEdicao.Preco.ToString("F2");
        cmbCategoriaForm.SelectedItem = produtoEmEdicao.Categoria;
        numEstoque.Value = produtoEmEdicao.Estoque;
        dtpDataCadastro.Value = produtoEmEdicao.DataCadastro;

        if (produtoEmEdicao.Ativo)
        {
            rdbAtivo.Checked = true;
        }
        else
        {
            rdbInativo.Checked = true;
        }
        chkPromocao.Checked = produtoEmEdicao.EmPromocao;

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
        PesquisarProduto();
    }

    private void CancelarEdicao(object? sender, EventArgs args)
    {
        if (produtoEmEdicao != null)
            PrepararNovo();
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
            erros.Dispose();
        base.Dispose(disposing);
    }
}