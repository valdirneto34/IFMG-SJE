public class DemoFactory {
    public static void main(String[] args) {
        // CENÁRIO 1: Precisamos de entrega terrestre
        // Instanciamos a FABRICA Rodoviária
        Logistica logistica1 = new LogisticaRodoviaria();

        // Chamamos o método que executa a lógica
        // Por baixo dos panos, ele vai criar um Caminhão
        logistica1.realizarEntrega();
        // Saída: "Entrega via terra."

        // CENÁRIO 2: Mudou a necessidade, agora é marítima
        // Instanciamos a FABRICA Marítima
        Logistica logistica2 = new LogisticaMaritima();

        // O código de chamada é idêntico (realizarEntrega),
        // mas o comportamento mudou.
        logistica2.realizarEntrega();
        // Saída: "Entrega via mar."
    }
}

// Interface comum (ou classe abstrata)
interface Transporte {
    void entregar();
}

// Implementações concretas
class Caminhao implements Transporte {
    @Override
    public void entregar() {
        System.out.println("Entrega via terra.");
    }
}

class Navio implements Transporte {
    @Override
    public void entregar() {
        System.out.println("Entrega via mar.");
    }
}

// Classe Criadora (Base)ff
abstract class Logistica {
    // O MÉTODO FÁBRICA
    public abstract Transporte criarTransporte();

    // Regra de negócio
    public void realizarEntrega() {
        // Note: Não existe 'new Caminhao()' aqui!
        Transporte t = criarTransporte();
        t.entregar();
    }
}

// Fábrica especializada em Caminhões
class LogisticaRodoviaria extends Logistica {
    @Override
    public Transporte criarTransporte() {
        return new Caminhao();
    }
}

// Fábrica especializada em Navios
class LogisticaMaritima extends Logistica {
    @Override
    public Transporte criarTransporte() {
        return new Navio();
    }
}