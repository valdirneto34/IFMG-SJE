public class Main {
    public static void main(String[] args) {
        Personagem p = new Personagem(new Espada());

        p.atacar();
        p.setArma(new Arco());
        p.atacar();
    }
}

interface Arma {
    void usar();
}

class Espada implements Arma {
    public void usar() {
        System.out.println("Espada!");
    }
}

class Arco implements Arma {
    public void usar() {
        System.out.println("Arco!");
    }
}

class Personagem {
    private Arma arma;

    public Personagem(Arma a) {
        this.arma = a;
    }

    public void setArma(Arma arma) {
        this.arma = arma;
    }

    public Arma getArma() {
        return arma;
    }

    void atacar() {
        arma.usar();
    }
}