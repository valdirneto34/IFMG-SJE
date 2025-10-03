#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int dia = 1;
    printf("Digite um número de dia da semana: ");
    scanf("%d", &dia);

    switch (dia)
    {
    case 1:
        printf("Você digitou Domingo.\n");
        break;
    case 2:
        printf("Você digitou Segunda-Feira.\n");
        break;
    case 3:
        printf("Você digitou Terça-Feira.\n");
        break;
    case 4:
        printf("Você digitou Quarta-Feira.\n");
        break;
    case 5:
        printf("Você digitou Quinta-Feira.\n");
        break;
    case 6:
        printf("Você digitou Sexta-Feira.\n");
        break;
    case 7:
        printf("Você digitou Sábado.\n");
        break;
    default:
        printf("Dia inválido!.\n");
    }
    return 0;
}
