#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int tipoMusica, numeroIntegrantes, ranking;

} Playlist;

Playlist bandas[3];

int main()
{
    int resp, cont = 0;
    for (int i = 0; i < 3; i++)
    {
        cout("\n\n1 - POP\n");
        cout("2 - FUNK\n");
        cout("3 - ROCK\n");
        cout("Digite o tipo de musica: ");
        scanf("%d", &bandas[i].tipoMusica);
        cout("Digite o numero de integrantes: ");
        scanf("%d", &bandas[i].numeroIntegrantes);
        cout("Digite o ranking da banda: ");
        scanf("%d", &bandas[i].ranking);
    }
    cout("\nInsira um numero de 1 a 3: ");
    scanf("%d", &resp);

    for (int i = 0; i < 3; i++)
    {
        if (bandas[i].ranking == resp)
        {
            cout("Banda de ");
            if (bandas[i].tipoMusica == 1)
                cout("POP");
            else if (bandas[i].tipoMusica == 2)
                cout("FUNK");
            else if (bandas[i].tipoMusica == 3)
                cout("ROCK");
            cout(" esta em %d lugar.\n", bandas[i].ranking);
            cont = 1;
            break;
        }
    }
    if (cont == 0)
    {
        cout("\nERRO: O ranking so contem as 3 primeiras colocacoes.\n");
    }
    system("pause");
    return 0;
}
