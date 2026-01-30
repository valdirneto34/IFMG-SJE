public class Stack {
    private Node top;
    private int size;

    public Stack() { // Criando uma pilha vazia
        this.top = null;
        this.size = 0;
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

    public int pop() {
        if (this.isEmpty()) {
            throw new IllegalStateException("A pilha está vazia");
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
}

class Node {
    public int item;
    public Node next;

    public Node(int item) {
        this.item = item;
        this.next = null;
    }
}