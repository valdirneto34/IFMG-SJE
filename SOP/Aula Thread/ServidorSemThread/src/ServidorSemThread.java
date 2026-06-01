public class ServidorSemThread {

    public static void atenderCliente(int id) {
        System.out.println("Atendendo cliente " + id + "...");
        try {
            Thread.sleep(1000);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
        System.out.println("Cliente " + id + " atendido.\n");
    }

    public static void main(String[] args) throws Exception {
        System.out.println("Servidor iniciado (sem threads)");
        long inicio = System.currentTimeMillis();
        for (int i = 1; i <= 10; i++) {
            atenderCliente(i);
        }

        long fim = System.currentTimeMillis();
        System.out.println("Todos os clientes foram atendidos.");
        System.out.println("Tempo total: " + (fim - inicio) + " ms.");
    }
}
