package com.mycompany.soma;

public class Soma {
    
    public static void main(String[] args) {
        SomaMaiorMenor s = new SomaMaiorMenor();
        System.out.println("Resultado soma: " + s.SomaMaior(2, 3, 4));
        System.out.println("Resultado menor: " + s.MenorNum(2, 3, 7));
        System.out.println("Resultado maior: " + s.MaiorNum(2, 3, 7));
    }
}
