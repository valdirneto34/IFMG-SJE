namespace CadastroAlunos;


public partial class CadastroForm
{
    private readonly ErrorProvider erros = new();
    private readonly TextBox txtNome = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 0
    };

    private readonly ComboBox cmbCurso = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 1,
        DropDownStyle = ComboBoxStyle.DropDownList
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
        Text = "Novo aluno.",
        AutoSize = true,
        Dock = DockStyle.Fill
    };

    private readonly DataGridView grade = new()
    {
        Dock = DockStyle.Fill,
        ReadOnly = true,
        TabIndex = 3,
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
        Text = "Cadastro de alunos";
        ClientSize = new Size(760, 480);
        MinimumSize = new Size(600, 400);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;
        cmbCurso.Items.AddRange(new object[] {
        "Sistemas de Informação", "Agronomia", "Administração"
    });
        var lblNome = new Label { Text = "Nome:", AutoSize = true };
        var lblCurso = new Label { Text = "Curso:", AutoSize = true };
        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 2,
            RowCount = 5
        };
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        txtNome.Margin = new Padding(3, 3, 24, 3);
        cmbCurso.Margin = new Padding(3, 3, 24, 3);
        layout.Controls.Add(lblNome, 0, 0);
        layout.Controls.Add(txtNome, 1, 0);
        layout.Controls.Add(lblCurso, 0, 1);
        layout.Controls.Add(cmbCurso, 1, 1);
        var botoes = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 2
        };
        botoes.Controls.AddRange(new Control[]{
        btnSalvar, btnNovo, btnExcluir
        });
        layout.Controls.Add(botoes, 0, 2);
        layout.SetColumnSpan(botoes, 2);
        layout.Controls.Add(grade, 0, 3);
        layout.SetColumnSpan(grade, 2);
        layout.Controls.Add(lblStatus, 0, 4);
        layout.SetColumnSpan(lblStatus, 2);
        Controls.Add(layout);
    }
}
