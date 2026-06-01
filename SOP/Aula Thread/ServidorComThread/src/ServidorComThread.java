public class ServidorComThread {

    static class ClienteAtendimento implements Runnable {
        private int id;

        public ClienteAtendimento(int id) {
            this.id = id;
        }

        @Override
        public void run() {
            System.out.println("Atendendo cliente " + id +
                    " (thread: " + Thread.currentThread().getName() + ") ");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            System.out.println("Cliente " + id + " atendido.\n");
        }
    }

    public static void main(String[] args) throws Exception {
        System.out.println("Servidor iniciado (com threads)");
        long inicio = System.currentTimeMillis();

        Thread[] threads = new Thread[10];

        for (int i = 0; i < 10; i++) {
            threads[i] = new Thread(new ClienteAtendimento(i + 1));
            threads[i].start();
        }

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        long fim = System.currentTimeMillis();
        System.out.println("Todos os clientes foram atendidos.");
        System.out.println("Tempo total: " + (fim - inicio) + " ms.");
    }
}
