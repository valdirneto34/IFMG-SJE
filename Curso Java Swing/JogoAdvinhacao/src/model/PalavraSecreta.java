package model;

public class PalavraSecreta {
    private int idPalavra;
    private String dica;
    private String palavra;

    public PalavraSecreta(int idPalavra, String dica, String palavra) {
        this.idPalavra = idPalavra;
        this.dica = dica;
        this.palavra = palavra;
    }

    public int getIdPalavra() {
        return idPalavra;
    }

    public void setIdPalavra(int idPalavra) {
        this.idPalavra = idPalavra;
    }

    public String getDica() {
        return dica;
    }

    public void setDica(String dica) {
        this.dica = dica;
    }

    public String getPalavra() {
        return palavra;
    }

    public void setPalavra(String palavra) {
        this.palavra = palavra;
    }
    
    
}
