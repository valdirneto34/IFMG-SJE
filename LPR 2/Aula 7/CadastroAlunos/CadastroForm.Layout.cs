namespace CadastroAlunos;

public partial class CadastroForm
{
    private readonly ErrorProvider erros = new();
    private readonly TextBox txtNome = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 0,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly TextBox txtEmail = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 1,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly ComboBox cmbCurso = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 2,
        DropDownStyle = ComboBoxStyle.DropDownList,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly TextBox txtTelefone = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 11,
        TabIndex = 3,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly TextBox txtCidade = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 50,
        TabIndex = 4,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly DateTimePicker dtpDataIngresso = new()
    {
        Dock = DockStyle.Fill,
        Format = DateTimePickerFormat.Short,
        TabIndex = 5,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly Button btnSalvar = new()
    {
        Text = "Salvar",
        AutoSize = true,
        TabIndex = 0
    };
    private readonly Button btnNovo = new()
    {
        Text = "Novo",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly Button btnExcluir = new()
    {
        Text = "Excluir",
        AutoSize = true,
        TabIndex = 2
    };
    private readonly Label lblStatus = new()
    {
        Text = "Preencha os dados do aluno.",
        AutoSize = true,
        Dock = DockStyle.Fill
    };
    private readonly DataGridView grade = new()
    {
        Dock = DockStyle.Fill,
        ReadOnly = true,
        TabIndex = 7,
        AllowUserToAddRows = false,
        AllowUserToDeleteRows = false,
        MultiSelect = false,
        RowHeadersVisible = false,
        SelectionMode = DataGridViewSelectionMode.FullRowSelect,
        AutoGenerateColumns = true,
        AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill
    };

    private void MontarTela()
    {
        Text = "Cadastro Acadêmico";
        ClientSize = new Size(760, 480);
        MinimumSize = new Size(600, 400);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;
        cmbCurso.Items.AddRange(new object[] {
        "Administração", "Agronomia", "Ciências Biológicas",
        "Engenharia Florestal", "Matemática", "Pedagogia", "Sistemas de Informação"});
        var lblNome = new Label { Text = "Nome:", AutoSize = true };
        var lblEmail = new Label { Text = "E-mail:", AutoSize = true };
        var lblCurso = new Label { Text = "Curso:", AutoSize = true };
        var lblTelefone = new Label { Text = "Telefone:", AutoSize = true };
        var lblCidade = new Label { Text = "Cidade:", AutoSize = true };
        var lblDataIngresso = new Label { Text = "Data de Ingresso:", AutoSize = true };
        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 4,
            RowCount = 5
        };

        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));

        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

        layout.Controls.Add(lblNome, 0, 0);
        layout.Controls.Add(txtNome, 1, 0);
        layout.Controls.Add(lblEmail, 2, 0);
        layout.Controls.Add(txtEmail, 3, 0);

        layout.Controls.Add(lblCurso, 0, 1);
        layout.Controls.Add(cmbCurso, 1, 1);
        layout.Controls.Add(lblTelefone, 2, 1);
        layout.Controls.Add(txtTelefone, 3, 1);
        
        layout.Controls.Add(lblCidade, 0, 2);
        layout.Controls.Add(txtCidade, 1, 2);
        layout.Controls.Add(lblDataIngresso, 2, 2);
        layout.Controls.Add(dtpDataIngresso, 3, 2);

        var botoes = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 6
        };
        botoes.Controls.AddRange(new Control[]{
        btnSalvar, btnNovo, btnExcluir
        });
        layout.Controls.Add(botoes, 0, 3);
        layout.SetColumnSpan(botoes, 4);

        layout.Controls.Add(grade, 0, 4);
        layout.SetColumnSpan(grade, 4);

        layout.Controls.Add(lblStatus, 0, 5);
        layout.SetColumnSpan(lblStatus, 4);

        Controls.Add(layout);
    }
}