public class Stack1 {

    private Node top;
    private int size;

    public Stack1() { // Criando uma pilha vazia
        this.top = null;
        this.size = 0;
    }

    public Stack1(Stack1 copia) {
        Node t = copia.top;
        Stack1 S = new Stack1();
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
        String resp = "";
        Node t = this.top;
        Integer aux;
        while(t != null){
            aux = t.item;
            resp += aux.toString() + " - ";
            t = t.next;
        }
        return resp;
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
