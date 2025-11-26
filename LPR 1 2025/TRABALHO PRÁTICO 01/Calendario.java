import java.util.*;

public class Calendario {

    /**
     * Função que recebe como parâmetro o dia, mês e o ano;
     * e retorna o dia da semana equivalente a esta data:
     * 0 -> Domingo
     * 1 -> Segunda-feira
     * 2 -> Terça-feira
     * ...
     * 6 -> Sábado
     */
    private String nomeMes[] = { " ", "Janeiro", "Fevereiro", "Março", "Abril", "Maio", "Junho", "Julho", "Agosto",
            "Setembro", "Outubro", "Novembro", "Dezembro" };

    public int diaSemana(int dia, int mes, int ano) {
        int f;

        f = ano + dia + 3 * (mes - 1) - 1;

        if (mes < 3) {
            ano = ano - 1;
        }

        if (mes >= 3) {
            f = f - (int) (0.4 * mes + 2.3);
        }

        f = f + (ano / 4) - (int) ((ano / 100 + 1) * 0.75);
        f = f % 7;

        return f;
    }

    /**
     * Função que recebe como parâmetro o ano e retorna um valor lógico
     * indicando se o ano é bissexto (true) ou não (false).
     */
    public boolean ehBissexto(int ano) {
        return (ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0);
    }

    /**
     * Função que recebe como parâmetro o mês e o ano e retorna a
     * quantidade de dias do mês.
     */
    public int diasNoMes(int mes, int ano) {
        if (mes < 1 || mes > 12) {
            return -1; // Mês inválido
        }

        switch (mes) {
            case 4:
            case 6:
            case 9:
            case 11:
                return 30;
            case 2:
                return ehBissexto(ano) ? 29 : 28;
            default:
                return 31;
        }
    }

    public void imprimeMes(int mes, int ano) {
        int matriz[][] = new int[6][7];
        int semanaInicio = diaSemana(1, mes, ano);
        int qtd = diasNoMes(mes, ano);
        String mesString = "";
        int contador = 1;

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                matriz[i][j] = 0;
            }
        }

        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                if (i == 0 && j < semanaInicio || contador > qtd) {
                    matriz[i][j] = 0;
                } else {
                    matriz[i][j] = contador;
                    contador++;
                }
            }
        }

        System.out.printf("%30s\n", nomeMes[mes]);
        System.out.println("D\tS\tT\tQ\tQ\tS\tS");
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 7; j++) {
                System.out.printf("%d\t", matriz[i][j]);
            }
            System.out.printf("\n");
        }

    }

    public void imprimeCalenadrio(int ano) {

    }
}