public class Soma {
    // Atributos privados
    private int a, b, c;

    //Metodos publicos
        public void inicializa(int a,int b){
            this.a = a;
            this.b = b;
        }

        public int soma(){
            this.c =  this.a + this.b;
            return this.c;
        }
}
