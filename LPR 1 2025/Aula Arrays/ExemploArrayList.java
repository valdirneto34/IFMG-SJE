import java.util.ArrayList;

public class ExemploArrayList {
    public static void main(String[] args) {
        ArrayList<Integer> a = new ArrayList<>();

        a.add(10);
        a.add(20);
        a.add(30);
        a.add(1, 50);
        a.set(3, 90);

        
        System.out.println("Tamanho: " + a.size());

        for(int i = 0; i < a.size(); i++){
            System.out.println("Elemento na posição " + i + ": " + a.get(i));
        }
    }
}
