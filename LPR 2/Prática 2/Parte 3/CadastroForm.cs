using System.ComponentModel;
namespace CatalogoProdutos;

public partial class CadastroForm : Form
{
    private readonly BindingList<Produto> produtos = new();
    private Produto? produtoEmEdicao;
    private string caminhoImagemAtual = "";

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
        txtPesquisa.TextChanged += PesquisarProduto;
        cmbCategoria.SelectedIndexChanged += PesquisarProduto;
        chkAtivo.CheckedChanged += PesquisarProduto;

        btnNovo.Click += NovoProduto;
        btnSalvar.Click += SalvarProduto;
        btnExcluir.Click += ExcluirProduto;

        grade.CellClick += SelecionarProduto;
        grade.CellFormatting += FormatarGradeEstoque;

        chkPromocao.CheckedChanged += MudancaPromocao;
        numDesconto.ValueChanged += CalcularPrecoFinal;
        txtPreco.TextChanged += CalcularPrecoFinal;

        btnSelecionarImagem.Click += EscolherImagem;
        btnRemoverImagem.Click += RemoverImagem;

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

    private void FormatarGradeEstoque(object? sender, DataGridViewCellFormattingEventArgs e)
    {
        if (e.RowIndex >= 0)
        {
            var produto = grade.Rows[e.RowIndex].DataBoundItem as Produto;

            if (produto != null)
            {
                if (produto.Estoque == 0)
                    grade.Rows[e.RowIndex].DefaultCellStyle.BackColor = Color.LightCoral;
                else if (produto.Estoque >= 1 && produto.Estoque <= 5)
                    grade.Rows[e.RowIndex].DefaultCellStyle.BackColor = Color.LightYellow;
                else
                    grade.Rows[e.RowIndex].DefaultCellStyle.BackColor = Color.White;

                if (grade.Columns[e.ColumnIndex].DataPropertyName == "Preco")
                {
                    e.Value = produto.PrecoFinal.ToString("C");
                    e.FormattingApplied = true;
                }
            }
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

        numDesconto.Value = 1;
        lblPrecoFinal.Text = "";

        caminhoImagemAtual = "";
        picImagem.ImageLocation = null;

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

        if (txtPreco.Text.Trim().Contains('.'))
        {
            MessageBox.Show("Digite o preço com vírgula \",\".", "Preço inválido.", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            txtPreco.Focus();
            return false;
        }
        return true;
    }

    private void MudancaPromocao(object? sender, EventArgs e)
    {
        numDesconto.Enabled = chkPromocao.Checked;
        CalcularPrecoFinal();
    }

    private void CalcularPrecoFinal(object? sender = null, EventArgs? e = null)
    {
        if (chkPromocao.Checked && double.TryParse(txtPreco.Text.Trim(), out double precoAtual))
        {
            double precoFinal = precoAtual * (1 - ((double)numDesconto.Value / 100.0));

            lblPrecoFinal.Text = $"Preço com desconto: {precoFinal:C}";
        }
        else
        {
            lblPrecoFinal.Text = "";
        }
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
                EmPromocao = emPromocao,
                CaminhoImagem = caminhoImagemAtual,
                PorcentoDesconto = chkPromocao.Checked ? (int)numDesconto.Value : 0,
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
            produtoEmEdicao.CaminhoImagem = caminhoImagemAtual;
            produtoEmEdicao.PorcentoDesconto = chkPromocao.Checked ? (int)numDesconto.Value : 0;

            produtos.ResetItem(produtos.IndexOf(produtoEmEdicao));
        }
        PrepararNovo();
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

        caminhoImagemAtual = produtoEmEdicao.CaminhoImagem;
        if (!string.IsNullOrEmpty(caminhoImagemAtual) && File.Exists(caminhoImagemAtual))
        {
            picImagem.ImageLocation = caminhoImagemAtual;
        }
        else
        {
            picImagem.ImageLocation = null;
        }

        if (produtoEmEdicao.Ativo)
        {
            rdbAtivo.Checked = true;
        }
        else
        {
            rdbInativo.Checked = true;
        }
        chkPromocao.Checked = produtoEmEdicao.EmPromocao;

        if (produtoEmEdicao.EmPromocao && produtoEmEdicao.PorcentoDesconto > 0)
        {
            numDesconto.Value = produtoEmEdicao.PorcentoDesconto;
        }
        else
        {
            numDesconto.Value = 1;
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
        PesquisarProduto();
    }

    private void CancelarEdicao(object? sender, EventArgs args)
    {
        if (produtoEmEdicao != null)
            PrepararNovo();
    }

    private void EscolherImagem(object? sender, EventArgs e)
    {
        using OpenFileDialog ofd = new();
        ofd.Filter = "Imagens (*.png;*.jpg;*.jpeg)|*.png;*.jpg;*.jpeg";
        ofd.Title = "Selecione a imagem do produto";

        if (ofd.ShowDialog() == DialogResult.OK)
        {
            caminhoImagemAtual = ofd.FileName;
            picImagem.ImageLocation = caminhoImagemAtual;
        }
    }

    private void RemoverImagem(object? sender, EventArgs e)
    {
        caminhoImagemAtual = "";
        picImagem.ImageLocation = null;
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
            erros.Dispose();
        base.Dispose(disposing);
    }
}