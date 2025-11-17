package Model;

public class PalavraSecreta {
    private int idPalavra;
    private String dica;
    private String palavra;

    public PalavraSecreta(int idPalavra, String dica, String palavra) {
        this.idPalavra = idPalavra;
        this.dica = dica;
        this.palavra = palavra;
    }
    
    /**
     * @return the idPalavra
     */
    public int getIdPalavra() {
        return idPalavra;
    }

    /**
     * @param idPalavra the idPalavra to set
     */
    public void setIdPalavra(int idPalavra) {
        this.idPalavra = idPalavra;
    }

    /**
     * @return the dica
     */
    public String getDica() {
        return dica;
    }

    /**
     * @param dica the dica to set
     */
    public void setDica(String dica) {
        this.dica = dica;
    }

    /**
     * @return the palavra
     */
    public String getPalavra() {
        return palavra;
    }

    /**
     * @param palavra the palavra to set
     */
    public void setPalavra(String palavra) {
        this.palavra = palavra;
    }
}
