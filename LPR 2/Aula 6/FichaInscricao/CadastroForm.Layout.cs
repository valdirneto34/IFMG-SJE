namespace FichaInscricao;

public partial class CadastroForm
{
    private readonly ErrorProvider erros = new();
    private readonly MenuStrip menuPrincipal = new();
    private readonly ToolStripMenuItem menuArquivo = new() { Text = "&Arquivo" };
    private readonly ToolStripMenuItem menuEditar = new() { Text = "&Editar" };
    private readonly ToolStripMenuItem menuAjuda = new() { Text = "&Ajuda" };
    private readonly ToolStrip barraFerramentas = new();
    private readonly ToolStripButton tsbNovo = new() { Text = "Novo", ToolTipText = "Criar nova inscrição" };
    private readonly ToolStripButton tsbSalvar = new() { Text = "Salvar", ToolTipText = "Salvar inscrição atual" };
    private readonly ToolStripButton tsbExcluir = new() { Text = "Excluir", ToolTipText = "Excluir inscrição selecionada" };
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
    private readonly DateTimePicker dtpDataNasc = new()
    {
        Dock = DockStyle.Fill,
        Format = DateTimePickerFormat.Short,
        TabIndex = 2
    };
    private readonly CheckBox chkAvisos = new()
    {
        Text = "Receber avisos",
        AutoSize = true,
        TabIndex = 3,
        Anchor = AnchorStyles.Left
    };
    private readonly RadioButton rdbPresencial = new()
    {
        Text = "Presencial",
        AutoSize = true,
        Checked = true,
        TabIndex = 0
    };
    private readonly RadioButton rdbRemota = new()
    {
        Text = "Remota",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly FlowLayoutPanel painelModalidade = new()
    {
        Dock = DockStyle.Fill,
        AutoSize = true,
        FlowDirection = FlowDirection.LeftToRight,
        Margin = new Padding(0),
        TabIndex = 4
    };
    private readonly NumericUpDown numDependentes = new()
    {
        Dock = DockStyle.Fill,
        Minimum = 1,
        Maximum = 10,
        Value = 1,
        Enabled = false,
        TabIndex = 5
    };
    private readonly Button btnNovo = new()
    {
        Text = "Novo",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly Button btnSalvar = new()
    {
        Text = "Salvar",
        AutoSize = true,
        TabIndex = 0
    };
    private readonly StatusStrip lblStatus = new()
    {
        Text = "",
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
        Text = "Sistemas de inscrições";
        ClientSize = new Size(760, 480);
        MinimumSize = new Size(600, 400);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;
        // CONFIGURAÇÃO DO MENUSTRIP (VIA CÓDIGO)
        // 1. Vincula os submenus aos menus principais
        menuArquivo.DropDownItems.Add(menuSair);
        menuEditar.DropDownItems.Add(menuSobre);
        // 2. Adiciona os menus principais à barra de menu
        menuPrincipal.Items.Add(menuArquivo);
        menuPrincipal.Items.Add(menuEditar);
        // 3. Configura atalhos rápidos (opcional)
        menuSair.ShortcutKeys = Keys.Control | Keys.Q; // Ctrl + Q para sair
        // 4. Cria os eventos de clique
        menuSair.Click += MenuSair_Click;
        menuSobre.Click += MenuSobre_Click;
        // 5. ADICIONA O MENU AO FORMULÁRIO
        Controls.Add(menuPrincipal);

        // CONFIGURAÇÃO DA TOOLSTRIP (BARRA DE FERRAMENTAS)
        // Associa os eventos de clique aos botões da barra
        tsbNovo.Click += BtnNovo_Click;      // Pode reaproveitar o evento do seu botão normal
        tsbSalvar.Click += BtnSalvar_Click;  // Pode reaproveitar o evento do seu botão normal
        tsbExcluir.Click += BtnExcluir_Click;
        // Adiciona uma linha separadora visual entre "Salvar" e "Excluir" (opcional)
        var separador = new ToolStripSeparator();
        // Adiciona os botões na barra de ferramentas
        barraFerramentas.Items.AddRange(new ToolStripItem[] { tsbNovo, tsbSalvar, separador, tsbExcluir });
        // Adiciona a barra ao formulário (ficará logo abaixo do MenuStrip)
        Controls.Add(barraFerramentas);

        cmbCurso.Items.AddRange(new object[] {
        "Administração", "Agronomia", "Ciências Biológicas",
        "Engenharia Florestal", "Matemática", "Pedagogia", "Sistemas de Informação"});

        var lblTituloForm = new Label { Text = "Dados da Inscrição", Autosize = true };
        var lblNome = new Label { Text = "Nome:", AutoSize = true };
        var lblCurso = new Label { Text = "Curso:", AutoSize = true };
        var lblDataNasc = new Label { Text = "Nascimento:", AutoSize = true };
        var lblModalidade = new Label { Text = "Modalidade:", AutoSize = true };
        var lblDependentes = new Label { Text = "Dependentes:", AutoSize = true };

        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 2,
            RowCount = 10
        };

        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.ColumnStyles.Add(new ColumnStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

        txtNome.Margin = new Padding(3, 3, 24, 3);
        cmbCurso.Margin = new Padding(3, 3, 24, 3);
        dtpDataNasc.Margin = new Padding(3, 3, 24, 3);
        numDependentes.Margin = new Padding(3, 3, 24, 3);

        layout.Controls.Add(lblNome, 0, 0);
        layout.Controls.Add(txtNome, 1, 0);

        layout.Controls.Add(lblCurso, 0, 1);
        layout.Controls.Add(cmbCurso, 1, 1);

        layout.Controls.Add(lblModalidade, 1, 1);

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