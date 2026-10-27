namespace FichaInscricao;

public class Aluno
{
    public string Nome { get; set; } = "";
    public string Curso { get; set; } = "";
    public DateTime DataNascimento { get; set; }
    public bool ReceberAvisos { get; set; }
    public bool EhPresencial { get; set; }
    public int NumDependentes { get; set; }
}