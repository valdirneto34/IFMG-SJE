namespace CatalogoProdutos;

public partial class CadastroForm
{
    private readonly TextBox txtPesquisa = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 0,
        PlaceholderText = "Digite para pesquisar..."
    };
    private readonly ComboBox cmbCategoria = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 1,
        DropDownStyle = ComboBoxStyle.DropDownList
    };
    private readonly CheckBox chkAtivo = new()
    {
        Text = "Somente em estoque",
        AutoSize = true,
        TabIndex = 2,
        Anchor = AnchorStyles.Right
    };
    private readonly Button btnPesquisar = new()
    {
        Text = "Pesquisar",
        AutoSize = true,
        TabIndex = 0
    };
    private readonly Button btnLimparFiltros = new()
    {
        Text = "Limpar Filtros",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly Label lblResultado = new Label()
    {
        Text = "Nenhum produto cadastrado",
        AutoSize = true,
        Anchor = AnchorStyles.Right
    };
    private readonly DataGridView grade = new()
    {
        Dock = DockStyle.Fill,
        ReadOnly = true,
        TabIndex = 4,
        AllowUserToAddRows = false,
        AllowUserToDeleteRows = false,
        MultiSelect = false,
        RowHeadersVisible = false,
        SelectionMode = DataGridViewSelectionMode.FullRowSelect,
        AutoGenerateColumns = false,
        AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill
    };
    private readonly TextBox txtCodigo = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 5
    };
    private readonly ComboBox cmbCategoriaForm = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 6,
        DropDownStyle = ComboBoxStyle.DropDownList
    };
    private readonly TextBox txtNome = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 7
    };
    private readonly TextBox txtPreco = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 8
    };
    private readonly NumericUpDown numEstoque = new()
    {
        Dock = DockStyle.Fill,
        TabIndex = 9,
        Minimum = 0,
        Maximum = 9999,
        Increment = 1,
        Value = 0
    };
    private readonly DateTimePicker dtpDataCadastro = new()
    {
        Dock = DockStyle.Fill,
        Format = DateTimePickerFormat.Short,
        TabIndex = 10
    };
    private readonly RadioButton rdbAtivo = new()
    {
        Text = "Ativo",
        AutoSize = true,
        Checked = true,
        TabIndex = 0
    };
    private readonly RadioButton rdbInativo = new()
    {
        Text = "Inativo",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly FlowLayoutPanel painelSituacao = new()
    {
        Dock = DockStyle.Fill,
        AutoSize = true,
        FlowDirection = FlowDirection.LeftToRight,
        Margin = new Padding(0),
        TabIndex = 11
    };
    private readonly CheckBox chkPromocao = new()
    {
        Text = "Produto em Promoção",
        AutoSize = true,
        TabIndex = 12
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
    private readonly Button btnCancelar = new()
    {
        Text = "Cancelar",
        AutoSize = true,
        TabIndex = 0
    };
    private readonly Button btnFechar = new()
    {
        Text = "Fechar",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly ErrorProvider erros = new();

    private void MontarTela()
    {
        Text = "Cadastro Produtos";
        ClientSize = new Size(760, 480);
        MinimumSize = new Size(600, 400);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;

        cmbCategoria.Items.Add("Todas");
        cmbCategoria.Items.AddRange(new object[] {
            "Acessórios", "Periféricos",
        });
        cmbCategoria.SelectedIndex = 0;

        cmbCategoriaForm.Items.AddRange(new object[] {
            "Acessórios", "Periféricos",
        });
        cmbCategoriaForm.SelectedIndex = 0;

        var lblPesquisa = new Label { Text = "Pesquisar por nome ou código:", AutoSize = true };
        var lblCategoria = new Label { Text = "Categoria:", AutoSize = true };
        var lblDadosProduto = new Label
        {
            Text = "Dados do Produto",
            AutoSize = true,
            Font = new Font("Segoe UI", 12F, FontStyle.Bold),
            ForeColor = Color.DarkBlue,
            Padding = new Padding(0, 10, 0, 5)
        };
        var lblCodigo = new Label { Text = "Codigo:", AutoSize = true };
        var lblNome = new Label { Text = "Nome:", AutoSize = true };
        var lblEstoque = new Label { Text = "Estoque:", AutoSize = true };
        var lblSituacao = new Label { Text = "Situação:", AutoSize = true };
        var lblCategoriaForm = new Label { Text = "Categoria:", AutoSize = true };
        var lblPreco = new Label { Text = "Preço:", AutoSize = true };
        var lblCadastro = new Label { Text = "Cadastro:", AutoSize = true };

        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 4,
            RowCount = 11
        };

        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));

        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

        txtPesquisa.Margin = new Padding(3, 3, 24, 3);
        cmbCategoria.Margin = new Padding(3, 3, 24, 3);
        txtCodigo.Margin = new Padding(3, 3, 24, 3);
        txtNome.Margin = new Padding(3, 3, 24, 3);
        numEstoque.Margin = new Padding(3, 3, 24, 3);
        cmbCategoriaForm.Margin = new Padding(3, 3, 24, 3);
        txtPreco.Margin = new Padding(3, 3, 24, 3);
        dtpDataCadastro.Margin = new Padding(3, 3, 24, 3);

        layout.Controls.Add(lblPesquisa, 0, 0);
        layout.Controls.Add(lblCategoria, 1, 0);

        layout.Controls.Add(txtPesquisa, 0, 1);
        layout.Controls.Add(cmbCategoria, 1, 1);
        layout.Controls.Add(chkAtivo, 3, 1);

        var botoesPesquisa = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 3
        };
        botoesPesquisa.Controls.AddRange(new Control[]{
        btnPesquisar, btnLimparFiltros
        });

        layout.Controls.Add(botoesPesquisa, 0, 2);
        layout.SetColumnSpan(botoesPesquisa, 2);
        layout.Controls.Add(lblResultado, 3, 2);

        layout.Controls.Add(grade, 0, 3);
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Codigo", HeaderText = "Código" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Nome", HeaderText = "Produto" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Categoria", HeaderText = "Categoria" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Preco", HeaderText = "Preço" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Estoque", HeaderText = "Estoque" });
        layout.SetColumnSpan(grade, 4);

        layout.Controls.Add(lblDadosProduto, 0, 4);

        layout.Controls.Add(lblCodigo, 0, 5);
        layout.Controls.Add(txtCodigo, 1, 5);
        layout.Controls.Add(lblCategoriaForm, 2, 5);
        layout.Controls.Add(cmbCategoriaForm, 3, 5);

        layout.Controls.Add(lblNome, 0, 6);
        layout.Controls.Add(txtNome, 1, 6);
        layout.Controls.Add(lblPreco, 2, 6);
        layout.Controls.Add(txtPreco, 3, 6);

        layout.Controls.Add(lblEstoque, 0, 7);
        layout.Controls.Add(numEstoque, 1, 7);
        layout.Controls.Add(lblCadastro, 2, 7);
        layout.Controls.Add(dtpDataCadastro, 3, 7);

        layout.Controls.Add(lblSituacao, 0, 8);
        painelSituacao.Controls.AddRange(new Control[] { rdbAtivo, rdbInativo });
        layout.Controls.Add(painelSituacao, 1, 8);
        layout.Controls.Add(chkPromocao, 3, 8);

        var botoes = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 13
        };
        botoes.Controls.AddRange(new Control[]{
        btnNovo, btnSalvar, btnExcluir
        });
        layout.Controls.Add(botoes, 0, 9);
        layout.SetColumnSpan(botoes, 3);


        var botoesCancelar = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 14,
            FlowDirection = FlowDirection.RightToLeft
        };
        botoesCancelar.Controls.AddRange(new Control[]{
        btnFechar, btnCancelar
        });
        layout.Controls.Add(botoesCancelar, 3, 9);

        lblPesquisa.Click += (s, e) => txtPesquisa.Focus();
        lblCodigo.Click += (s, e) => txtCodigo.Focus();
        lblNome.Click += (s, e) => txtNome.Focus();
        lblPreco.Click += (s, e) => txtPreco.Focus();
        lblEstoque.Click += (s, e) => numEstoque.Focus();
        lblCadastro.Click += (s, e) => dtpDataCadastro.Focus();
        lblCategoriaForm.Click += (s, e) => cmbCategoriaForm.Focus();

        Controls.Add(layout);
    }
}