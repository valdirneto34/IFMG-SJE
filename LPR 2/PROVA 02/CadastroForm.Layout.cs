namespace CatalogoProdutos;

public partial class CadastroForm
{

    private readonly MenuStrip menuPrincipal = new();
    private readonly ToolStripMenuItem opcoes = new() { Text = "&Opções" };
    private readonly ToolStripMenuItem menuSortear = new() { Text = "&Sortear destaque" };
    private readonly ToolStripMenuItem menuFechar = new() { Text = "&Fechar" };
    private readonly TextBox txtCodigo = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 0,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly TextBox txtNome = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 1,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly ComboBox cmbCategoria = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 2,
        DropDownStyle = ComboBoxStyle.DropDownList,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly TextBox txtPreco = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 3,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly RadioButton rdbDisponivel = new()
    {
        Text = "Ativo",
        AutoSize = true,
        Checked = true,
        TabIndex = 0
    };
    private readonly RadioButton rdbIndisponivel = new()
    {
        Text = "Inativo",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly FlowLayoutPanel painelDisponibilidade = new()
    {
        Dock = DockStyle.Fill,
        AutoSize = true,
        FlowDirection = FlowDirection.LeftToRight,
        Margin = new Padding(0),
        TabIndex = 4
    };
    private readonly NumericUpDown numEstoque = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 5,
        Minimum = 0,
        Maximum = 9999,
        Increment = 1,
        Value = 0,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly Button btnNovo = new()
    {
        Text = "Novo",
        AutoSize = true,
        TabIndex = 0
    };
    private readonly Button btnSalvar = new()
    {
        Text = "Salvar",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly Button btnExcluir = new()
    {
        Text = "Excluir",
        AutoSize = true,
        TabIndex = 2
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
        AutoGenerateColumns = false,
        AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill
    };
    private readonly ErrorProvider erros = new();

    private void MontarTela()
    {
        Text = "Cadastro";
        ClientSize = new Size(600, 400);
        MinimumSize = new Size(750, 500);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;

        opcoes.DropDownItems.Add(menuSortear);
        opcoes.DropDownItems.Add(menuFechar);
        menuPrincipal.Items.Add(opcoes);
        MainMenuStrip = menuPrincipal;

        Controls.Add(menuPrincipal);

        cmbCategoria.Items.AddRange(new object[] {
            "Acessórios", "Hardware", "Periféricos", "Software"
        });
        cmbCategoria.SelectedIndex = 0;

        var lblTituloForm = new Label
        {
            Text = "Cadastro de Produtos",
            AutoSize = true,
            Font = new Font("Segoe UI", 12F, FontStyle.Bold),
            ForeColor = Color.DarkBlue,
            Padding = new Padding(0, 20, 0, 3)
        };
        var lblCodigo = new Label { Text = "Codigo:", AutoSize = true };
        var lblNome = new Label { Text = "Nome:", AutoSize = true };
        var lblCategoria = new Label { Text = "Categoria:", AutoSize = true };
        var lblPreco = new Label { Text = "Preço:", AutoSize = true };
        var lblDisponivel = new Label { Text = "Disponibilidade:", AutoSize = true };
        var lblEstoque = new Label { Text = "Estoque:", AutoSize = true };

        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 4,
            RowCount = 12
        };

        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));

        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

        layout.Controls.Add(lblTituloForm, 0, 0);

        layout.Controls.Add(lblCodigo, 0, 1);
        layout.Controls.Add(txtCodigo, 1, 1);
        layout.Controls.Add(lblNome, 2, 1);
        layout.Controls.Add(txtNome, 3, 1);


        layout.Controls.Add(lblCategoria, 0, 2);
        layout.Controls.Add(cmbCategoria, 1, 2);
        layout.Controls.Add(lblPreco, 2, 2);
        layout.Controls.Add(txtPreco, 3, 2);

        layout.Controls.Add(lblDisponivel, 0, 3);
        painelDisponibilidade.Controls.AddRange(new Control[] { rdbDisponivel, rdbIndisponivel });
        layout.Controls.Add(painelDisponibilidade, 1, 3);
        layout.Controls.Add(lblEstoque, 2, 3);
        layout.Controls.Add(numEstoque, 3, 3);

        var botoes = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 6
        };
        botoes.Controls.AddRange(new Control[] { btnNovo, btnSalvar, btnExcluir });
        layout.Controls.Add(botoes, 0, 4);
        layout.SetColumnSpan(botoes, 3);

        layout.Controls.Add(grade, 0, 5);
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Codigo", HeaderText = "Código" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Nome", HeaderText = "Nome" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Categoria", HeaderText = "Categoria" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Preco", HeaderText = "Preço" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Estoque", HeaderText = "Estoque" });
        layout.SetColumnSpan(grade, 4);

        Controls.Add(layout);
    }
}