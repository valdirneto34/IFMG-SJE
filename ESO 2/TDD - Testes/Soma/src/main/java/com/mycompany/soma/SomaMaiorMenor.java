package com.mycompany.soma;

public class SomaMaiorMenor {

    public int SomaMaior(int a, int b, int c) {
        return a + b + c;
    }

    public int MenorNum(int a, int b, int c) {
        int menor = a;
        if (b < menor) {
            menor = b;
        }
        if (c < menor) {
            menor = c;
        }
        return menor;
    }

    public int MaiorNum(int a, int b, int c) {
        int maior = a;
        if (b > maior) {
            maior = b;
        }
        if (c > maior) {
            maior = c;
        }
        return maior;
    }
}
