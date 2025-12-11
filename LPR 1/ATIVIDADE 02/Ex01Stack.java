public class Ex01Stack {

    private Node top;
    private int size;

    public Ex01Stack() { // Criando uma pilha vazia
        this.top = null;
        this.size = 0;
    }

    public Ex01Stack(Ex01Stack copia) {
        Node t = copia.top;
        Ex01Stack S = new Ex01Stack();
        while (t != null) {
            S.push(t.item);
            t = t.next;
        }
        this.size = 0;
        this.top = null;
        try {
            while (!S.isEmpty()) {
                this.push(S.pop());
            }
        } catch (Exception e) {
        }
    }

    public void push(int item) { // Empilhar
        Node t = new Node(item);
        t.next = this.top;
        this.top = t;
        this.size++;
    }

    public boolean isEmpty() {
        return this.top == null;
    }

    public int size() {
        return this.size;
    }

    public int pop() throws Exception {
        if (this.isEmpty()) {
            throw new Exception("A pilha está vazia");
        }
        int item = this.top.item;
        this.top = this.top.next;
        this.size--;
        return item;
    }

    public int top() {
        if (this.isEmpty()) {
            throw new IllegalStateException("A pilha está vazia");
        }
        return this.top.item;
    }

    public String imprime() throws Exception {
        if (this.isEmpty()) {
            throw new Exception("A pilha está vazia");
        }
        String result = "";
        Node t = this.top;
        while (t != null) {
            Integer aux = t.item;
            result += aux.toString();
            if (t.next != null) {
                result += ", ";
            }
            t = t.next;
        }
        return result;
    }
}

class Node {
    public int item;
    public Node next;

    public Node(int item) {
        this.item = item;
        this.next = null;
    }
}
