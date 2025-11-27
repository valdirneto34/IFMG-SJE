public class Configuracao {
    // 1. Atributo estático que guarda a instância única
    private static Configuracao instance;

    private String apiUrl = "http://api.ifmg.edu.br";

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