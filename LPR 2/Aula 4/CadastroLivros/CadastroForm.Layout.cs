namespace CadastroLivros;


public partial class CadastroForm
{
    private readonly ErrorProvider erros = new();
    
    private readonly TextBox txtTitulo = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 0
    };

    private readonly TextBox txtAutor = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 1
    };

    private readonly ComboBox cmbCategoria = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 2,
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
        Text = "Preencha os dados do livro.",
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
        Text = "Cadastro de Livros";
        ClientSize = new Size(760, 480);
        MinimumSize = new Size(600, 400);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;
        cmbCategoria.Items.AddRange(new object[] {
        "Computação", "Literatura", "Ciências", "Administração", "História"
    });
        var lblTitulo = new Label { Text = "Título:", AutoSize = true };
        var lblAutor = new Label { Text = "Autor:", AutoSize = true };
        var lblCategoria = new Label { Text = "Categoria:", AutoSize = true };
        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 2,
            RowCount = 6
        };

        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

        txtTitulo.Margin = new Padding(3, 3, 24, 3);
        txtAutor.Margin = new Padding(3, 3, 24, 3);
        cmbCategoria.Margin = new Padding(3, 3, 24, 3);

        layout.Controls.Add(lblTitulo, 0, 0);
        layout.Controls.Add(txtTitulo, 1, 0);

        layout.Controls.Add(lblAutor, 0, 1);
        layout.Controls.Add(txtAutor, 1, 1);

        layout.Controls.Add(lblCategoria, 0, 2);
        layout.Controls.Add(cmbCategoria, 1, 2);

        var botoes = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 2
        };
        
        botoes.Controls.AddRange(new Control[]{
        btnSalvar, btnNovo, btnExcluir
        });

        layout.Controls.Add(botoes, 0, 3);
        layout.SetColumnSpan(botoes, 2);
        layout.Controls.Add(grade, 0, 4);
        layout.SetColumnSpan(grade, 2);
        layout.Controls.Add(lblStatus, 0, 5);
        layout.SetColumnSpan(lblStatus, 2);
        Controls.Add(layout);
    }
}