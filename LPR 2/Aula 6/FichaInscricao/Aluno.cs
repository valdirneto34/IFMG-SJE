namespace FichaInscricao;

public enum ModalidadeCurso
{
    Presencial,
    Remota
}

public class Aluno
{
    public string Nome { get; set; } = "";
    public string Curso { get; set; } = "";
    public DateTime DataNascimento { get; set; }
    public bool ReceberAvisos { get; set; }
    public ModalidadeCurso Modalidade { get; set; }
    public int NumDependentes { get; set; }
}