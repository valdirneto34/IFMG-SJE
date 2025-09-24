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
        printf("\n\n1 - POP\n");
        printf("2 - FUNK\n");
        printf("3 - ROCK\n");
        printf("Digite o tipo de musica: ");
        scanf("%d", &bandas[i].tipoMusica);
        printf("Digite o numero de integrantes: ");
        scanf("%d", &bandas[i].numeroIntegrantes);
        printf("Digite o ranking da banda: ");
        scanf("%d", &bandas[i].ranking);
    }
    printf("\nInsira um numero de 1 a 3: ");
    scanf("%d", &resp);

    for (int i = 0; i < 3; i++)
    {
        if (bandas[i].ranking == resp)
        {
            printf("Banda de ");
            if (bandas[i].tipoMusica == 1)
                printf("POP");
            else if (bandas[i].tipoMusica == 2)
                printf("FUNK");
            else if (bandas[i].tipoMusica == 3)
                printf("ROCK");
            printf(" esta em %d lugar.\n", bandas[i].ranking);
            cont = 1;
            break;
        }
    }
    if (cont == 0)
    {
        printf("\nERRO: O ranking so contem as 3 primeiras colocacoes.\n");
    }
    system("pause");
    return 0;
}
