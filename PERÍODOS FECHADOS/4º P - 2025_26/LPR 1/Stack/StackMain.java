public class StackMain {
    public static void main(String[] args) {
        Stack A = new Stack();

        try {
            A.push(10);
            A.push(20);
            A.push(30);

            while (!A.isEmpty()) {
                System.out.println(A.top());
                A.pop();
            }
            A.pop();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
