public class Carro2 {
    private Motor motor;

    public Carro2(){
        this.motor = new Motor();
        System.out.println("Carro montado com um novo motor.");
    }

    public void dirigir(){
        System.out.println("\nIniciando...");
        motor.ligar();
        System.out.println("Carro está se movendo!");
    }
}
