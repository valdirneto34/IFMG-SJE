package Controller;

import java.util.List;
import Model.PalavraSecreta;
import java.util.ArrayList;
import java.util.Random;

public class Jogar {
    
    private static final Random RANDOM = new Random();
    private static final List<PalavraSecreta> PALAVRAS_SECRETAS = criarListaPalavrasSecretas();
    
    private int jogo = 1;
    private String palavraSecreta;
    private char[] palavraAdivinhada;
    private boolean finalizado;
    
    public PalavraSecreta iniciarPartida() {
        PalavraSecreta palavraSelecionada = PALAVRAS_SECRETAS.get(RANDOM.nextInt(PALAVRAS_SECRETAS.size()));
        this.palavraSecreta = palavraSelecionada.getPalavra().toUpperCase();
        this.palavraAdivinhada = new char[palavraSecreta.length()];
        for (int i = 0; i < palavraAdivinhada.length; i++) {
            palavraAdivinhada[i] = '_';
        }
        this.finalizado = false;
        
        return palavraSelecionada;
    }
    
    public String tentarLetra(char letra_param) {
        if(isFinalizado()) {
            return getPalavraAdivinhada() + " - Jogo Encerrado!";
        }
        
        char letraUpper = Character.toUpperCase(letra_param);
        
        for(int i = 0; i < palavraSecreta.length(); i++) {
            if(palavraSecreta.charAt(i) == letraUpper) {
                palavraAdivinhada[i] = letraUpper;
            }
        }
        
        if(isPartidaFinalizada()) {
            finalizado = true;
            jogo++;
            return getPalavraAdivinhada() + " - Parabéns!!";
        }
        
        return getPalavraAdivinhada();
    }
    
    private boolean isPartidaFinalizada () {
        for (char c : palavraAdivinhada) {
            if(c == '_') {
                return false;
            }
        }
        return true;
    }
    
    public String getPalavraAdivinhada() {
        return new String(this.palavraAdivinhada);
    }
    
    private static List<PalavraSecreta> criarListaPalavrasSecretas() {
        List<PalavraSecreta> lista = new ArrayList<>();
        
        lista.add(new PalavraSecreta(1, "Cai em pé e corre deitado.", "CHUVA"));
        lista.add(new PalavraSecreta(2, "Tem água, mas não é rio. Tem casca, mas não é ovo.", "COCO"));
        lista.add(new PalavraSecreta(3, "Quebra quando se fala.", "SILENCIO"));
        lista.add(new PalavraSecreta(4, "Tem dentes e cabeça, mas não come nem pensa.", "CHAVE"));
        lista.add(new PalavraSecreta(5, "Passa o tempo todo, mas não se move.", "RELOGIO"));
        lista.add(new PalavraSecreta(6, "Tem montanhas e rios, mas não tem árvores nem peixes.", "MAPA"));
        lista.add(new PalavraSecreta(7, "Tem capa e folhas, mas não é herói nem árvore.", "LIVRO"));
        lista.add(new PalavraSecreta(8, "Te segue o dia inteiro, em silêncio.", "SOMBRA"));
        lista.add(new PalavraSecreta(9, "Tem listras pretas e brancas, mas não é código de barras.", "ZEBRA"));
        lista.add(new PalavraSecreta(10, "Quando o tiramos, aumenta.", "ZERO"));
        lista.add(new PalavraSecreta(11, "Tem unha e carne, mas não arranha e nem é bife.", "DEDO"));
        lista.add(new PalavraSecreta(12, "Corre sem ter pés e é pai de peixes.", "RIO"));
        lista.add(new PalavraSecreta(13, "Entra na água, mas nunca se molha.", "BOTA"));
        lista.add(new PalavraSecreta(14, "Pode ser doce ou salgado, mas sempre tem casca.", "OVOS"));
        lista.add(new PalavraSecreta(15, "Te vê e te imita, mas não tem olhos ou braços.", "ESPELHO"));
        
        return lista;
    }

    public int getNivel() {
        return jogo;
    }

    public boolean isFinalizado() {
        return finalizado;
    }
    
}
