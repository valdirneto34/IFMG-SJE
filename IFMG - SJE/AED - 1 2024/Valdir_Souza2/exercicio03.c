#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int num = 1;
    cout("Digite um número entre 0 e 10 para vê-lo por extenso: ");
    scanf("%d", &num);

    switch (num)
    {
    case 0:
        cout("Zero\n");
        break;
    case 1:
        cout("Um\n");
        break;
    case 2:
        cout("Dois\n");
        break;
    case 3:
        cout("Três\n");
        break;
    case 4:
        cout("Quatro\n");
        break;
    case 5:
        cout("Cinco\n");
        break;
    case 6:
        cout("Seis\n");
        break;
    case 7:
        cout("Sete\n");
        break;
    case 8:
        cout("Oito\n");
        break;
    case 9:
        cout("Nove\n");
        break;
    case 10:
        cout("Dez\n");
        break;
    default:
        cout("Número inválido!.\n");
    }
    return 0;
}
