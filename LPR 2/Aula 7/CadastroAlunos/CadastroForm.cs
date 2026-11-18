using MySql.Data.MySqlClient;
using System.Data;
using System.Globalization;

namespace CadastroAlunos;

public partial class CadastroForm : Form
{
    private const string ConnectionString = "Server=localhost;Port=3306;Database=inscricoes;" + "User ID=app_inscricoes;Password=admin123;";
    private static readonly string[] Preposicoes = ["da", "de", "do", "das", "dos", "e"];
    private static readonly TextInfo TextInfoPtBr = new CultureInfo("pt-BR").TextInfo;

    public CadastroForm()
    {
        MontarTela();
        ConectarEventos();
        PrepararNovo();
        Load += CadastroFormLoad;
    }

    private async void CadastroFormLoad(object? sender, EventArgs e)
    {
        try
        {
            await CarregarEstudantesAsync();
        }
        catch (MySqlException ex)
        {
            MessageBox.Show($"Erro ao carregar estudantes: {ex.Message}");
        }
    }

    private void ConectarEventos()
    {
        btnSalvar.Click += BtnSalvarClick;
        btnNovo.Click += NovoAluno;
        btnTestarConexao.Click += BtnTestarConexaoClick;

        grade.CellFormatting += Grade_CellFormatting;

        txtTelefone.KeyPress += TxtTelefone_KeyPress;
        txtTelefone.TextChanged += TxtTelefone_TextChanged;
        txtNome.TextChanged += FiltrarNomeProprio_TextChanged;
        txtCidade.TextChanged += FiltrarNomeProprio_TextChanged;
        txtNome.Leave += FormatarNomeProprio_Leave;
        txtCidade.Leave += FormatarNomeProprio_Leave;
        txtEmail.Leave += TxtEmail_Leave;
    }

    private void NovoAluno(object? sender, EventArgs args)
    {
        PrepararNovo();
    }

    private void PrepararNovo()
    {
        txtNome.Clear();
        txtEmail.Clear();
        cmbCurso.SelectedIndex = 0;
        txtTelefone.Clear();
        txtCidade.Clear();
        dtpDataIngresso.Value = DateTime.Today;
        grade.ClearSelection();
        btnSalvar.Text = "Salvar";
        btnExcluir.Enabled = false;
        lblStatus.Text = "Novo aluno. Preencha e clique em Salvar.";
        txtNome.Focus();
    }

    private bool ExibirErroValidacao(Control campo, string mensagem, string status, string titulo = "Erro de Validação")
    {
        MessageBox.Show(this, mensagem, titulo, MessageBoxButtons.OK, MessageBoxIcon.Warning);
        lblStatus.Text = status;
        campo.Focus();
        return false;
    }

    private bool ValidarCampos()
    {
        if (txtNome.Text.Trim().Length < 3)
            return ExibirErroValidacao(txtNome, "O nome do aluno deve ter no mínimo 3 caracteres.", "Revise o nome do aluno.");

        if (txtEmail.Text.Trim().Length < 5 || !txtEmail.Text.Contains('@') || !txtEmail.Text.Contains('.'))
            return ExibirErroValidacao(txtEmail, "Informe um endereço de e-mail válido.", "Revise o e-mail do aluno.");

        if (cmbCurso.SelectedIndex < 0)
            return ExibirErroValidacao(cmbCurso, "Selecione um curso válido.", "Revise o curso do aluno.");

        if (txtTelefone.Text.Count(char.IsDigit) < 10)
            return ExibirErroValidacao(txtTelefone, "Informe o telefone completo com DDD (10 ou 11 dígitos).", "Revise o telefone do aluno.");

        if (txtCidade.Text.Trim().Length < 3)
            return ExibirErroValidacao(txtCidade, "O nome da cidade deve ter no mínimo 3 caracteres.", "Revise a cidade do aluno.");

        return true;
    }

    private async void BtnTestarConexaoClick(object? sender, EventArgs e)
    {
        await TestarConexaoAsync();
    }

    private static async Task TestarConexaoAsync()
    {
        try
        {
            using var conexao = new MySqlConnection(ConnectionString);
            await conexao.OpenAsync();
            MessageBox.Show("Conexão estabelecida com sucesso. A conexão está estável.", "Teste de Conexão", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
        catch (MySqlException ex)
        {
            MessageBox.Show($"Falha na conexão: {ex.Message}");
        }
    }

    private static async Task SalvarEstudanteAsync(string nome, string email, string curso, string telefone, string cidade, DateTime dataIngresso)
    {
        const string sql = "INSERT INTO estudante (nome, email, curso, telefone, cidade, data_ingresso) VALUES (@nome, @email, @curso, @telefone, @cidade, @data_ingresso)";
        using var conexao = new MySqlConnection(ConnectionString);
        await conexao.OpenAsync();
        using var comando = new MySqlCommand(sql, conexao);
        comando.Parameters.Add("@nome", MySqlDbType.VarChar).Value = nome;
        comando.Parameters.Add("@email", MySqlDbType.VarChar).Value = email;
        comando.Parameters.Add("@curso", MySqlDbType.VarChar).Value = curso;
        comando.Parameters.Add("@telefone", MySqlDbType.VarChar).Value = telefone;
        comando.Parameters.Add("@cidade", MySqlDbType.VarChar).Value = cidade;
        comando.Parameters.Add("@data_ingresso", MySqlDbType.Date).Value = dataIngresso;
        await comando.ExecuteNonQueryAsync();
    }

    private async void BtnSalvarClick(object? sender, EventArgs e)
    {
        if (!ValidarCampos())
            return;

        string nome = txtNome.Text.Trim();
        string email = txtEmail.Text.Trim();
        string curso = cmbCurso.SelectedItem?.ToString() ?? "";
        string telefone = new([.. txtTelefone.Text.Where(char.IsDigit)]);
        string cidade = txtCidade.Text.Trim();
        DateTime dataIngresso = dtpDataIngresso.Value.Date;

        try
        {
            await SalvarEstudanteAsync(nome, email, curso, telefone, cidade, dataIngresso);
            await CarregarEstudantesAsync();
            MessageBox.Show("Estudante cadastrado com sucesso.", "Sucesso no Cadastro", MessageBoxButtons.OK, MessageBoxIcon.Information);
            PrepararNovo();
            lblStatus.Text = "Registro salvo no banco de dados.";
        }
        catch (MySqlException ex)
        {
            MessageBox.Show($"Não foi possível salvar: {ex.Message}");
        }

    }

    private async Task CarregarEstudantesAsync()
    {
        const string sql = "SELECT id, nome, email, curso, telefone, cidade, data_ingresso FROM estudante ORDER BY id DESC";
        using var conexao = new MySqlConnection(ConnectionString);
        await conexao.OpenAsync();
        using var comando = new MySqlCommand(sql, conexao);
        using var leitor = await comando.ExecuteReaderAsync();
        var tabela = new DataTable();
        tabela.Load(leitor);
        grade.DataSource = tabela;
    }

    private void TxtTelefone_KeyPress(object? sender, KeyPressEventArgs e)
    {
        if (e.KeyChar == (char)Keys.Back && txtTelefone.SelectionStart == txtTelefone.Text.Length && txtTelefone.Text.EndsWith(") "))
        {
            txtTelefone.Text = txtTelefone.Text[..2];
            txtTelefone.SelectionStart = txtTelefone.Text.Length;
            e.Handled = true;
            return;
        }

        if (!char.IsDigit(e.KeyChar) && !char.IsControl(e.KeyChar))
        {
            e.Handled = true;
        }
    }

    private void TxtTelefone_TextChanged(object? sender, EventArgs e)
    {
        string digitos = new(txtTelefone.Text.Where(char.IsDigit).ToArray());

        if (digitos.Length > 11)
            digitos = digitos[..11];

        string formatado = digitos.Length switch
        {
            0 => "",
            1 => $"({digitos}",
            2 => $"({digitos}) ",
            <= 6 => $"({digitos[..2]}) {digitos[2..]}",
            <= 10 => $"({digitos[..2]}) {digitos[2..6]}-{digitos[6..]}",
            _ => $"({digitos[..2]}) {digitos[2..7]}-{digitos[7..]}"
        };

        if (txtTelefone.Text != formatado)
        {
            txtTelefone.Text = formatado;
            txtTelefone.SelectionStart = txtTelefone.Text.Length;
        }
    }

    private static bool EhCaractereValidoNome(char c)
    {
        return char.IsLetter(c) || c == ' ' || c == '-' || c == '\'';
    }

    private void FiltrarNomeProprio_TextChanged(object? sender, EventArgs e)
    {
        if (sender is not TextBox campo)
            return;

        int posicaoCursor = campo.SelectionStart;

        string textoFiltrado = new(campo.Text.Where(EhCaractereValidoNome).ToArray());

        if (campo.Text != textoFiltrado)
        {
            int diferenca = campo.Text.Length - textoFiltrado.Length;
            campo.Text = textoFiltrado;
            campo.SelectionStart = Math.Max(0, posicaoCursor - diferenca);
        }
    }

    private void FormatarNomeProprio_Leave(object? sender, EventArgs e)
    {
        if (sender is not TextBox campo || string.IsNullOrWhiteSpace(campo.Text))
            return;

        string textoLimpo = new(campo.Text.Where(EhCaractereValidoNome).ToArray());
        string[] palavras = textoLimpo.ToLower().Split(' ', StringSplitOptions.RemoveEmptyEntries);

        if (palavras.Length == 0)
            return;

        palavras[0] = TextInfoPtBr.ToTitleCase(palavras[0]);

        for (int i = 1; i < palavras.Length; i++)
        {
            if (!Preposicoes.Contains(palavras[i]))
                palavras[i] = TextInfoPtBr.ToTitleCase(palavras[i]);
        }

        campo.Text = string.Join(" ", palavras);
    }

    private void TxtEmail_Leave(object? sender, EventArgs e)
    {
        txtEmail.Text = txtEmail.Text.Trim().ToLower();
    }

    private void Grade_CellFormatting(object? sender, DataGridViewCellFormattingEventArgs e)
    {
        if (grade.Columns[e.ColumnIndex].DataPropertyName != "telefone" || e.Value is not string texto)
            return;

        string digitos = new(texto.Where(char.IsDigit).ToArray());

        e.Value = digitos.Length switch
        {
            10 => $"({digitos[..2]}) {digitos[2..6]}-{digitos[6..]}",
            11 => $"({digitos[..2]}) {digitos[2..7]}-{digitos[7..]}",
            _ => texto
        };

        e.FormattingApplied = true;
    }

}