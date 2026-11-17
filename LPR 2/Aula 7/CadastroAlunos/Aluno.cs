namespace CadastroAlunos;

public class Aluno
{
    public int Id { get; }
    public string Nome { get; set; } = "";
    public string Email { get; set; } = "";
    public string Curso { get; set; } = "";
    public DateTime DataIngresso { get; set; }
    public string Telefone { get; set; } = "";
    public string Cidade { get; set; } = "";
}