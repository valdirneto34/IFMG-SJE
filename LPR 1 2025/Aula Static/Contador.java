public class Contador {
    /*public static int total = 0;

    Contador() {
        total++;
    }
    */
    private static int total = 0;

    public Contador() {
        total++;
    }

    public static int getTotal() {
        return total;
    }
    
}
