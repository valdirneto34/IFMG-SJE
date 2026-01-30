public class ConfiguracaoMain {
    public static void main(String[] args) {
        // Configuracao c = new Configuracao(); // ERRO!

        Configuracao c1 = Configuracao.getInstance();
        Configuracao c2 = Configuracao.getInstance();

        // Prova real: c1 e c2 são o MESMO objeto na memória?
        if (c1 == c2) {
            System.out.println("É a mesma instância! Singleton funcionou.");
        }
    }
}

class Configuracao {
    // 1. Atributo estático que guarda a instância única
    private static Configuracao instance;

    private final String apiUrl = "http://api.ifmg.edu.br";

    // 2. Construtor privado (ninguém faz new Configuracao())
    private Configuracao() {
        System.out.println("Carregando configs...");
    }

    // 3. Método público estático para acesso global
    public static Configuracao getInstance() {
        if (instance == null) {
            instance = new Configuracao(); // Cria só na 1ª vez
        }
        return instance;
    }

    public String getUrl() {
        return apiUrl;
    }
}