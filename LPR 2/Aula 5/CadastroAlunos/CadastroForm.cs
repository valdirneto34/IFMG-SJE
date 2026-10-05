using System.ComponentModel;

namespace CadastroAlunos;

public partial class CadastroForm : Form
{
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
        btnSalvar.Click += SalvarAluno;
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
        txtMatricula.Clear();
        txtNome.Clear();
        cmbCurso.SelectedIndex = -1;
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
        if (txtMatricula.Text.Trim().Length == 0)
        {
            erros.SetError(txtMatricula, "Informe pelo menos 1 caractere.");
            lblStatus.Text = "Revise a matrícula do aluno.";
            txtMatricula.Focus();
            return false;
        }
        else if (alunoEmEdicao == null)
        {
            foreach (Aluno a in alunos)
            {
                if (txtMatricula.Text.Trim() == a.Matricula)
                {
                    erros.SetError(txtMatricula, "Já existe um aluno com essa matrícula.");
                    lblStatus.Text = "Revise a matrícula do aluno.";
                    txtMatricula.Focus();
                    return false;
                }
            }
        }
        if (txtNome.Text.Trim().Length < 3)
        {
            erros.SetError(txtNome, "Informe pelo menos 3 caracteres.");
            lblStatus.Text = "Revise o nome do aluno.";
            txtNome.Focus();
            return false;
        }
        if (cmbCurso.SelectedIndex < 0)
        {
            erros.SetError(cmbCurso, "Selecione um curso.");
            lblStatus.Text = "Revise o curso do aluno.";
            cmbCurso.Focus();
            return false;
        }
        return true;
    }

    private void SalvarAluno(object? sender, EventArgs args)
    {
        if (!ValidarCampos())
            return;

        string matricula = txtMatricula.Text.Trim();
        string nome = txtNome.Text.Trim();
        string curso = cmbCurso.SelectedItem?.ToString() ?? "";
        bool novoCadastro = alunoEmEdicao is null;

        if (alunoEmEdicao is null)
        {
            alunos.Add(new Aluno { Matricula = matricula, Nome = nome, Curso = curso });
        }
        else
        {
            alunoEmEdicao.Matricula = matricula;
            alunoEmEdicao.Nome = nome;
            alunoEmEdicao.Curso = curso;
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
        txtMatricula.Text = alunoEmEdicao.Matricula;
        txtNome.Text = alunoEmEdicao.Nome;
        cmbCurso.SelectedItem = alunoEmEdicao.Curso;
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

    protected override void Dispose(bool disposing)
    {
        if (disposing)
            erros.Dispose();
        base.Dispose(disposing);
    }
}