public class Ex01Main {
    public static void main(String[] args) {
        Stack1 A = new Stack1();
        for (int i = 10; i <= 50; i += 10) {
            A.push(i);
        }

        Stack1 B = new Stack1(A);

        try {
            System.out.println(A.imprime());
        } catch (Exception e) {

        }

        try {
            System.out.println(B.imprime());
        } catch (Exception e) {

        }

    }
}
