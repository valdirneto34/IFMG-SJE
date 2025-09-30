#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int dia = 1;
    cout("Digite um número de dia da semana: ");
    scanf("%d", &dia);

    switch (dia)
    {
    case 1:
        cout("Você digitou Domingo.\n");
        break;
    case 2:
        cout("Você digitou Segunda-Feira.\n");
        break;
    case 3:
        cout("Você digitou Terça-Feira.\n");
        break;
    case 4:
        cout("Você digitou Quarta-Feira.\n");
        break;
    case 5:
        cout("Você digitou Quinta-Feira.\n");
        break;
    case 6:
        cout("Você digitou Sexta-Feira.\n");
        break;
    case 7:
        cout("Você digitou Sábado.\n");
        break;
    default:
        cout("Dia inválido!.\n");
    }
    return 0;
}
