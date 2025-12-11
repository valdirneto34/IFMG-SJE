import java.util.Scanner;

public class SomaMain {

    
    public static void main(String[] args) {
        // Criar um objeto da classe soma
        Soma s; // s é uma referência (ponteiro)
        s = new Soma(); // Instanciando o objeto
        Scanner cin = new Scanner(System.in);
        int num1, num2;

        System.out.println("Digite um número: ");
        num1 = cin.nextInt();

        System.out.println("Digite outro número: ");
        num2 = cin.nextInt();

        // Chamando (invocando) métodos do objeto
        // Enviando mensagens para o objeto
        s.inicializa(num1, num2);
        System.out.println(s.soma());

        cin.close();
    }

}
