namespace FichaInscricao;

public partial class CadastroForm : Form
{
    private readonly System.ComponentModel.BindingList<Aluno> alunos = new();
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
        btnSalvar.Click += SalvarAluno;
        btnNovo.Click += NovoAluno;
        grade.CellClick += SelecionarAluno;

        grade.MouseDown += SelecionarComBotaoDireito;

        menuGradeEditar.Click += (s, e) => txtNome.Focus();
        menuGradeExcluir.Click += ExcluirAluno;

        tsbNovo.Click += NovoAluno;
        tsbSalvar.Click += SalvarAluno;
        tsbExcluir.Click += ExcluirAluno;

        alunos.ListChanged += (s, e) => AtualizarStatus();
    }

    private void NovoAluno(object? sender, EventArgs args)
    {
        PrepararNovo();
        lblStatusTexto.Text = "Pronto";
    }

    private void PrepararNovo()
    {
        alunoEmEdicao = null;
        txtNome.Clear();
        cmbCurso.SelectedIndex = 0;
        dtpDataNasc.Value = DateTime.Today;
        chkAvisos.Checked = true;
        rdbPresencial.Checked = true;
        numDependentes.Value = 0;
        grade.ClearSelection();
        erros.Clear();
        btnSalvar.Text = "Salvar";

        tsbExcluir.Enabled = false;
        menuGradeExcluir.Enabled = false;
        menuGradeEditar.Enabled = false;

        txtNome.Focus();
    }

    private bool ValidarCampos()
    {
        erros.Clear();
        if (txtNome.Text.Trim().Length < 3)
        {
            erros.SetError(txtNome, "Informe pelo menos 3 caracteres.");
            txtNome.Focus();
            return false;
        }
        if (cmbCurso.SelectedIndex < 0)
        {
            erros.SetError(cmbCurso, "Selecione um curso.");
            cmbCurso.Focus();
            return false;
        }
        return true;
    }

    private void SalvarAluno(object? sender, EventArgs args)
    {
        if (!ValidarCampos())
            return;

        string nome = txtNome.Text.Trim();
        string curso = cmbCurso.SelectedItem?.ToString() ?? "";
        DateTime dataNasc = dtpDataNasc.Value.Date;
        bool avisos = chkAvisos.Checked;
        ModalidadeCurso modalidadeSelecionada = rdbPresencial.Checked
            ? ModalidadeCurso.Presencial
            : ModalidadeCurso.Remota;
        int numDepen = (int)numDependentes.Value;

        if (alunoEmEdicao is null)
        {
            alunos.Add(new Aluno
            {
                Nome = nome,
                Curso = curso,
                DataNascimento = dataNasc,
                ReceberAvisos = avisos,
                Modalidade = modalidadeSelecionada,
                NumDependentes = numDepen
            });
        }
        else
        {
            alunoEmEdicao.Nome = nome;
            alunoEmEdicao.Curso = curso;
            alunoEmEdicao.DataNascimento = dataNasc;
            alunoEmEdicao.ReceberAvisos = avisos;
            alunoEmEdicao.Modalidade = modalidadeSelecionada;
            alunoEmEdicao.NumDependentes = numDepen;
            alunos.ResetItem(alunos.IndexOf(alunoEmEdicao));
        }
        lblStatusTexto.Text = alunoEmEdicao is null ? "Inscrição criada com sucesso!" : "Inscrição atualizada!";
        PrepararNovo();
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
        cmbCurso.SelectedItem = alunoEmEdicao.Curso;
        dtpDataNasc.Value = alunoEmEdicao.DataNascimento;
        chkAvisos.Checked = alunoEmEdicao.ReceberAvisos;
        (alunoEmEdicao.Modalidade == ModalidadeCurso.Presencial ? rdbPresencial : rdbRemota).Checked = true;
        numDependentes.Value = alunoEmEdicao.NumDependentes;
        btnSalvar.Text = "Atualizar";

        tsbExcluir.Enabled = true;
        menuGradeExcluir.Enabled = true;
        menuGradeEditar.Enabled = true;

        erros.Clear();
    }

    private void SelecionarComBotaoDireito(object? sender, MouseEventArgs e)
    {
        if (e.Button == MouseButtons.Right)
        {
            var hit = grade.HitTest(e.X, e.Y);
            if (hit.RowIndex >= 0)
            {
                grade.ClearSelection();
                grade.Rows[hit.RowIndex].Selected = true;

                SelecionarAluno(grade, new DataGridViewCellEventArgs(hit.ColumnIndex, hit.RowIndex));
            }
        }
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
        lblStatusTexto.Text = "Inscrição excluída com sucesso!";
        PrepararNovo();
    }

    private void AtualizarStatus()
    {
        int total = alunos.Count;
        if (total == 0)
            lblContadorInscricoes.Text = "Nenhuma inscrição";
        else if (total == 1)
            lblContadorInscricoes.Text = "1 inscrição";
        else
            lblContadorInscricoes.Text = $"{total} inscrições";
    }

    protected override void Dispose(bool disposing)
    {
        if (disposing)
            erros.Dispose();
        base.Dispose(disposing);
    }
}