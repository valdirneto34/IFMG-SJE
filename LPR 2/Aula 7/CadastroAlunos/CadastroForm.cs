using System.ComponentModel;
using MySql.Data.MySqlClient;
using System.Data;

namespace CadastroAlunos;

public partial class CadastroForm : Form
{
    private const string ConnectionString = "Server=localhost;Port=3306;Database=inscricoes;" + "User ID=app_inscricoes;Password=admin123;";
    private readonly BindingList<Aluno> alunos = new();
    private Aluno? alunoEmEdicao;

    public CadastroForm()
    {
        MontarTela();
        grade.DataSource = alunos;
        erros.ContainerControl = this;
        ConectarEventos();
        PrepararNovo();
    }

    private void ConectarEventos()
    {
        btnSalvar.Click += BtnSalvarClick;
        btnNovo.Click += NovoAluno;
        btnExcluir.Click += ExcluirAluno;
        grade.CellClick += SelecionarAluno;
    }

    private void NovoAluno(object? sender, EventArgs args)
    {
        PrepararNovo();
    }

    private void PrepararNovo()
    {
        alunoEmEdicao = null;
        txtNome.Clear();
        txtEmail.Clear();
        grade.ClearSelection();
        erros.Clear();
        btnSalvar.Text = "Salvar";
        btnExcluir.Enabled = false;
        lblStatus.Text = "Novo aluno. Preencha e clique em Salvar.";
        txtNome.Focus();
    }

    private bool ValidarCampos()
    {
        erros.Clear();

        if (txtNome.Text.Trim().Length < 3)
        {
            erros.SetError(txtNome, "Informe pelo menos 3 caracteres.");
            lblStatus.Text = "Revise o nome do aluno.";
            txtNome.Focus();
            return false;
        }

        if (txtEmail.Text.Trim().Length < 10)
        {
            erros.SetError(txtNome, "Informe pelo menos 10 caracteres.");
            lblStatus.Text = "Revise o e-mail do aluno.";
            txtNome.Focus();
            return false;
        }

        return true;
    }

    private void SalvarAluno(object? sender, EventArgs args)
    {
        if (!ValidarCampos())
            return;

        string nome = txtNome.Text.Trim();
        string email = txtEmail.Text.Trim();
        bool novoCadastro = alunoEmEdicao is null;

        if (alunoEmEdicao is null)
        {
            SalvarEstudanteAsync(nome, email);
        }
        else
        {
            alunoEmEdicao.Nome = nome;
            alunoEmEdicao.Email = email;
            alunos.ResetItem(alunos.IndexOf(alunoEmEdicao));
        }

        PrepararNovo();
        lblStatus.Text = novoCadastro ? "Registro salvo em memória." : "Registro atualizado.";
    }

    private void SelecionarAluno(object? sender, DataGridViewCellEventArgs args)
    {
        if (args.RowIndex < 0)
            return;
        var aluno = grade.Rows[args.RowIndex].DataBoundItem as Aluno;
        if (aluno is null)
            return;
        alunoEmEdicao = aluno;
        txtNome.Text = alunoEmEdicao.Nome;
        txtEmail.Text = alunoEmEdicao.Email;
        btnSalvar.Text = "Atualizar";
        btnExcluir.Enabled = true;
        erros.Clear();
        lblStatus.Text = "Editando o aluno selecionado.";
    }

    private void ExcluirAluno(object? sender, EventArgs args)
    {
        if (alunoEmEdicao is null)
            return;
        DialogResult resposta = MessageBox.Show(this,
        $"Excluir {alunoEmEdicao.Nome}?", "Confirmar exclusão",
        MessageBoxButtons.YesNo, MessageBoxIcon.Question,
        MessageBoxDefaultButton.Button2);
        if (resposta != DialogResult.Yes)
            return;
        alunos.Remove(alunoEmEdicao);
        PrepararNovo();
        lblStatus.Text = "Registro excluído.";
    }

    private async Task TestarConexaoAsync()
    {
        try
        {
            using var conexao = new MySqlConnection(ConnectionString);
            await conexao.OpenAsync();
            MessageBox.Show("Conexão estabelecida com sucesso.");
        }
        catch (MySqlException ex)
        {
            MessageBox.Show($"Falha na conexão: {ex.Message}");
        }
    }

    private async Task SalvarEstudanteAsync(string nome, string email)
    {
        const string sql = "INSERT INTO estudante (nome, email) VALUES (@nome, @email)";
        using var conexao = new MySqlConnection(ConnectionString);
        await conexao.OpenAsync();
        using var comando = new MySqlCommand(sql, conexao);
        comando.Parameters.Add("@nome", MySqlDbType.VarChar).Value = nome;
        comando.Parameters.Add("@email", MySqlDbType.VarChar).Value = email;
        await comando.ExecuteNonQueryAsync();
    }

    private async void BtnSalvarClick(object sender, EventArgs e)
    {
        // Lê os campos e remove espaços no início e no fim.
        string nome = txtNome.Text.Trim();
        string email = txtEmail.Text.Trim();
        bool novoCadastro = alunoEmEdicao is null;
        // Impede o envio se algum campo estiver vazio.
        if (!ValidarCampos())
        {
            return;
        }
        try
        {
            // Salva no banco e atualiza a grade com os dados recentes.
            await SalvarEstudanteAsync(nome, email);
            await CarregarEstudantesAsync();
            MessageBox.Show("Estudante salvo.");
        }
        catch (MySqlException ex)
        {
            // Exibe falhas retornadas pelo MySQL, como e-mail duplicado.
            MessageBox.Show($"Não foi possível salvar: {ex.Message}");
        }
        PrepararNovo();
        lblStatus.Text = novoCadastro ? "Registro salvo em memória." : "Registro atualizado.";
    }

    private async Task CarregarEstudantesAsync()
    {
        const string sql = "SELECT id, nome, email, criado_em " + "FROM estudante ORDER BY id DESC";
        using var conexao = new MySqlConnection(ConnectionString);
        await conexao.OpenAsync();
        using var comando = new MySqlCommand(sql, conexao);
        // Executa o SELECT e obtém as linhas retornadas.
        using var leitor = await comando.ExecuteReaderAsync();
        var tabela = new DataTable();// Carrega os resultados em uma tabela
        tabela.Load(leitor); // Vincula os dados à grade para exibição no formulário.
        //dgvEstudantes.DataSource = tabela;
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
            erros.Dispose();
        base.Dispose(disposing);
    }
}