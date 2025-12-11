public class Agenda {
    private String[] compromissos;

    public Agenda() {
        // Inicializa a agenda com 31 dias, sem compromissos
        compromissos = new String[31];
        for (int i = 0; i < compromissos.length; i++) {
            compromissos[i] = "";
        }
    }

    // Retorna o compromisso do dia (se houver)
    public String getCompromisso(int dia) {
        if (dia < 1 || dia > 31) {
            return "Dia inválido.";
        }
        return compromissos[dia - 1];
    }
}