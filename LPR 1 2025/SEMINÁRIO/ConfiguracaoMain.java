public class ConfiguracaoMain {
    public static void main(String[] args) {
        // Configuracao c = new Configuracao(); // ERRO!
        
        Configuracao c1 = Configuracao.getInstance();
        Configuracao c2 = Configuracao.getInstance();
        
        // Prova real: c1 e c2 são o MESMO objeto na memória?
        if (c1 == c2) {
            System.out.println("É a mesma instância! Singleton funcionou." );
        }
    }
}