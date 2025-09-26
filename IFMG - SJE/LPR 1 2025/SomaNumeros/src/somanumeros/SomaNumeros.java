package somanumeros;

import java.util.Scanner;

public class SomaNumeros {

    public static void main(String[] args) {
        // Criando uma referência para entrada de dados
        // e alocando memória
        Scanner cin = new Scanner(System.in);

        int num1, num2, soma;
        System.out.println("Digite um numero:");
        num1 = cin.nextInt();

        System.out.println("Digite outro:");
        num2 = cin.nextInt();

        soma = num1 + num2;
        System.out.println("A soma é " + soma);

        cin.close();

    }
    
}
