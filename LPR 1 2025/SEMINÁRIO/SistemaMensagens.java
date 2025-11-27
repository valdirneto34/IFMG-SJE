public class SistemaMensagens {
    public static void main(String[] args) {
        NotificacaoFactory fabrica = new NotificacaoFactory();

        // Usuario escolheu enviar por SMS
        // Note que a variavel 'n1' e do tipo generico
        Notificacao n1 = fabrica.criarNotificacao("sms");
        n1.enviar("Ola, seu codigo e 1234");

        // Usuario mudou para Email
        Notificacao n2 = fabrica.criarNotificacao("email");
        n2.enviar("Bem-vindo ao sistema!");
    }
}

// Interface Comum
interface Notificacao {
    void enviar(String mensagem);
}

// Implementacoes Concretas
class EmailNotificacao implements Notificacao {
    public void enviar(String msg) {
        System.out.println("Enviando EMAIL: " + msg);
    }
}

class SMSNotificacao implements Notificacao {
    public void enviar(String msg) {
        System.out.println("Enviando SMS: " + msg);
    }
}

class NotificacaoFactory {

    public Notificacao criarNotificacao(String tipo) {
        if (tipo == null || tipo.isEmpty()) {
            return null;
        }
        // A logica de criacao fica encapsulada aqui
        if ("email".equalsIgnoreCase(tipo)) {
            return new EmailNotificacao();
        } else if ("sms".equalsIgnoreCase(tipo)) {
            return new SMSNotificacao();
        }

        return null;
    }
}