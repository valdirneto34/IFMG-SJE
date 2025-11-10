package controller;

import java.util.*;
import model.PalavraSecreta;

public class Jogar {
    
    private static final Random RANDOM = new Random();
    private static final List<PalavraSecreta> PALAVRAS_SECRETAS = criarListaPalavrasSecretas();
    
    private int jogo = 1;
    private String palavraSecreta;
    private char palavraAdvinha[];
    private boolean finalizado;
    
    public PalavraSecreta iniciarPartida(){
        PalavraSecreta palavraSelecionada = PALAVRAS_SECRETAS.get(RANDOM.nextInt(PALAVRAS_SECRETAS.size()));
        this.palavraSecreta = palavraSelecionada.getPalavra().toUpperCase();
        this.palavraAdvinha = new char[palavraSecreta.length()];
        for (int i = 0; i < palavraAdvinha.length; i++) {
            palavraAdvinha[i] = '_';
        }
        this.finalizado = false;
        return palavraSelecionada;
    }
    
    private static List<PalavraSecreta> criarListaPalavrasSecretas(){
        List<PalavraSecreta> lista = new ArrayList();
        
        lista.add(new PalavraSecreta(1, "Cai em pe e corre deitado", "CHUVA"));
        lista.add(new PalavraSecreta(2, "Quebra quando se fala", "SILENCIO"));
        lista.add(new PalavraSecreta(3, "Anda com os pes na cabeca", "PIOLHO"));
        lista.add(new PalavraSecreta(4, "Te segue o dia inteiro, em silencio", "SOMBRA"));
        
        return lista;
    }

    public int getJogo() {
        return jogo;
    }

    public boolean isFinalizado() {
        return finalizado;
    }
    
    
}
