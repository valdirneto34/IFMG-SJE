namespace FichaInscricao;

public partial class CadastroForm
{
    private readonly ErrorProvider erros = new();
    private readonly MenuStrip menuPrincipal = new();
    private readonly ToolStripMenuItem menuArquivo = new() { Text = "&Arquivo" };
    private readonly ToolStripMenuItem menuEditar = new() { Text = "&Editar" };
    private readonly ToolStripMenuItem menuAjuda = new() { Text = "&Ajuda" };
    private readonly ToolStrip barraFerramentas = new();
    private readonly ToolStripButton tsbNovo = new()
    {
        Text = "Novo",
        ToolTipText = "Criar nova inscrição",
        Image = CriarIcone("novo"),
        DisplayStyle = ToolStripItemDisplayStyle.ImageAndText
    };
    private readonly ToolStripButton tsbSalvar = new()
    {
        Text = "Salvar",
        ToolTipText = "Salvar inscrição atual",
        Image = CriarIcone("salvar"),
        DisplayStyle = ToolStripItemDisplayStyle.ImageAndText
    };
    private readonly ToolStripButton tsbExcluir = new()
    {
        Text = "Excluir",
        ToolTipText = "Excluir inscrição selecionada",
        Image = CriarIcone("excluir"),
        DisplayStyle = ToolStripItemDisplayStyle.ImageAndText
    };
    private readonly TextBox txtNome = new()
    {
        Dock = DockStyle.Fill,
        MaxLength = 100,
        TabIndex = 0,
        PlaceholderText = "Digite seu nome completo",
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly ComboBox cmbCurso = new()
    {
        Anchor = AnchorStyles.Left,
        Width = 200,
        TabIndex = 1,
        DropDownStyle = ComboBoxStyle.DropDownList,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly DateTimePicker dtpDataNasc = new()
    {
        Anchor = AnchorStyles.Left,
        Width = 200,
        Format = DateTimePickerFormat.Short,
        TabIndex = 2,
        Margin = new Padding(3, 3, 24, 3)
    };
    private readonly CheckBox chkAvisos = new()
    {
        Text = "Receber avisos",
        AutoSize = true,
        TabIndex = 3,
        Anchor = AnchorStyles.Left,
    };
    private readonly RadioButton rdbPresencial = new()
    {
        TextAlign = ContentAlignment.MiddleCenter,
        Text = "Presencial",
        AutoSize = true,
        Checked = true,
        TabIndex = 0,
        Margin = new Padding(0, 0, 15, 0)
    };
    private readonly RadioButton rdbRemota = new()
    {
        TextAlign = ContentAlignment.MiddleCenter,
        Text = "Remota",
        AutoSize = true,
        TabIndex = 1
    };
    private readonly FlowLayoutPanel painelModalidade = new()
    {
        AutoSize = true,
        FlowDirection = FlowDirection.LeftToRight,
        Margin = new Padding(50, 4, 0, 0),
        TabIndex = 4
    };
    private readonly NumericUpDown numDependentes = new()
    {
        Anchor = AnchorStyles.Left,
        Width = 200,
        Minimum = 0,
        Maximum = 10,
        Value = 1,
        TabIndex = 5,
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
    private readonly StatusStrip barraStatus = new() { Dock = DockStyle.Bottom };
    private readonly ToolStripStatusLabel lblStatusTexto = new()
    {
        Text = "Pronto",
        Spring = true,
        TextAlign = ContentAlignment.MiddleLeft
    };
    private readonly ToolStripStatusLabel lblContadorInscricoes = new()
    {
        Text = "Nenhuma inscrição",
        Spring = false,
        TextAlign = ContentAlignment.MiddleRight
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
        AutoGenerateColumns = false,
        AutoSizeColumnsMode = DataGridViewAutoSizeColumnsMode.Fill,
        BackgroundColor = SystemColors.Window,
        BorderStyle = BorderStyle.Fixed3D
    };
    private readonly ContextMenuStrip menuGrade = new();
    private readonly ToolStripMenuItem menuGradeEditar = new() { Text = "Editar", Image = CriarIcone("editar") };
    private readonly ToolStripMenuItem menuGradeExcluir = new() { Text = "Excluir", Image = CriarIcone("excluir") };

    private void MontarTela()
    {
        Text = "Sistemas de inscrições";
        ClientSize = new Size(760, 480);
        MinimumSize = new Size(600, 400);
        StartPosition = FormStartPosition.CenterScreen;
        AutoScaleMode = AutoScaleMode.Font;
        AcceptButton = btnSalvar;

        menuPrincipal.Items.Add(menuArquivo);
        menuPrincipal.Items.Add(menuEditar);
        menuPrincipal.Items.Add(menuAjuda);
        MainMenuStrip = menuPrincipal;

        var separador = new ToolStripSeparator();
        var separador2 = new ToolStripSeparator();
        barraFerramentas.Items.AddRange(new ToolStripItem[] { tsbNovo, separador, tsbSalvar, separador2, tsbExcluir });

        Controls.Add(barraFerramentas);
        Controls.Add(menuPrincipal);

        menuGrade.Items.AddRange(new ToolStripItem[] { menuGradeEditar, menuGradeExcluir });
        grade.ContextMenuStrip = menuGrade;

        cmbCurso.Items.AddRange(new object[] {
            "Administração", "Agronomia", "Ciências Biológicas",
            "Engenharia Florestal", "Matemática", "Pedagogia", "Sistemas de Informação"});
        cmbCurso.SelectedIndex = 0;

        var lblTituloForm = new Label
        {
            Text = "Dados da Inscrição",
            AutoSize = true,
            Font = new Font("Segoe UI", 12F, FontStyle.Bold),
            ForeColor = Color.DarkBlue,
            Padding = new Padding(0, 2, 0, 3)
        };
        var lblNome = new Label { Text = "Nome:", AutoSize = true };
        var lblCurso = new Label { Text = "Curso:", AutoSize = true };
        var lblDataNasc = new Label { Text = "Nascimento:", AutoSize = true, Margin = new Padding(50, 4, 0, 0) };
        var lblModalidade = new Label { Text = "Modalidade:", AutoSize = true, Margin = new Padding(50, 4, 0, 0) };
        var lblDependentes = new Label { Text = "Dependentes:", AutoSize = true, Margin = new Padding(50, 4, 0, 0) };

        var layout = new TableLayoutPanel
        {
            Dock = DockStyle.Fill,
            Padding = new Padding(12),
            ColumnCount = 4,
            RowCount = 6
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
        layout.RowStyles.Add(new RowStyle(SizeType.Percent, 100));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));
        layout.RowStyles.Add(new RowStyle(SizeType.AutoSize));

        layout.Controls.Add(lblTituloForm, 0, 0);
        layout.SetColumnSpan(lblTituloForm, 4);

        layout.Controls.Add(lblNome, 0, 1);
        layout.Controls.Add(txtNome, 1, 1);
        layout.SetColumnSpan(txtNome, 3);

        layout.Controls.Add(lblCurso, 0, 2);
        layout.Controls.Add(cmbCurso, 1, 2);
        layout.Controls.Add(lblDataNasc, 2, 2);
        layout.Controls.Add(dtpDataNasc, 3, 2);

        layout.Controls.Add(lblModalidade, 1, 3);
        layout.SetColumnSpan(lblModalidade, 3);

        layout.Controls.Add(chkAvisos, 0, 4);
        painelModalidade.Controls.AddRange(new Control[] { rdbPresencial, rdbRemota });
        layout.Controls.Add(painelModalidade, 1, 4);
        layout.Controls.Add(lblDependentes, 2, 4);
        layout.Controls.Add(numDependentes, 3, 4);

        var botoes = new FlowLayoutPanel
        {
            Dock = DockStyle.Fill,
            AutoSize = true,
            TabIndex = 6,
            FlowDirection = FlowDirection.RightToLeft
        };
        botoes.Controls.AddRange(new Control[]{
        btnSalvar, btnNovo
        });
        layout.Controls.Add(botoes, 4, 5);


        layout.Controls.Add(grade, 0, 6);
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Nome", HeaderText = "Nome" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Curso", HeaderText = "Curso" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "DataNascimento", HeaderText = "Nascimento" });
        grade.Columns.Add(new DataGridViewTextBoxColumn { DataPropertyName = "Modalidade", HeaderText = "Modalidade" });
        grade.ColumnHeadersDefaultCellStyle.Font = new Font("Segoe UI", 9F, FontStyle.Bold);
        layout.SetColumnSpan(grade, 4);

        barraStatus.Items.AddRange(new ToolStripItem[] { lblStatusTexto, lblContadorInscricoes });
        Controls.Add(barraStatus);

        lblNome.Click += (s, e) => txtNome.Focus();
        lblCurso.Click += (s, e) => cmbCurso.Focus();
        lblDataNasc.Click += (s, e) => dtpDataNasc.Focus();
        lblModalidade.Click += (s, e) => rdbPresencial.Focus();
        lblDependentes.Click += (s, e) => numDependentes.Focus();

        Controls.Add(layout);
        layout.BringToFront();
    }

    private static Bitmap CriarIcone(string tipo)
    {
        var bmp = new Bitmap(16, 16);
        using var g = Graphics.FromImage(bmp);
        g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;

        switch (tipo)
        {
            case "novo":
                g.FillRectangle(Brushes.White, 3, 1, 10, 14);
                g.DrawRectangle(Pens.DimGray, 3, 1, 10, 14);
                break;
            case "salvar":
                using (var pen = new Pen(Color.RoyalBlue, 2f))
                    g.DrawLines(pen, new[] { new Point(2, 8), new Point(6, 12), new Point(14, 4) });
                break;
            case "excluir":
                using (var pen = new Pen(Color.Crimson, 2f))
                {
                    g.DrawLine(pen, 3, 3, 13, 13);
                    g.DrawLine(pen, 13, 3, 3, 13);
                }
                break;
            case "editar":
                using (var pen = new Pen(Color.DarkOrange, 2f))
                {
                    g.DrawLine(pen, 3, 13, 13, 3);
                }
                g.FillRectangle(Brushes.DimGray, 2, 12, 3, 3);
                break;
        }
        return bmp;
    }
}