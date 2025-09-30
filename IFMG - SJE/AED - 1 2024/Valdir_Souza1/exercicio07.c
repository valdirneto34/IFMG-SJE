#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL,"portuguese");
    int matriz[3][3], somatodoselementos = 0, cont = 0;
    int somacoluna1 = 0, produtolinha1 = 1;
    float mediaelementos = 0;
    cout("Preencha a matriz:\n");
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout("Linha %d e a coluna %d: ", i, j);
            scanf("%d", &matriz[i][j]);
            if (j == 0)
                somacoluna1 += matriz[i][j];
            if (i == 0)
                produtolinha1 *= matriz[i][j];
            somatodoselementos += matriz[i][j];
            cont++;
        }
    }
    cout("\nMatriz inserida:\n");
    for (int i = 0; i < 3; i++)
    {
        cout("\n");
        for (int j = 0; j < 3; j++)
        {
            cout("%4d",matriz[i][j]);
        }
    }
    mediaelementos = somatodoselementos / cont;
    cout("\n\nSoma dos elementos da 1ª coluna: %d\n", somacoluna1);
    cout("Produto dos elementos da 1ª linha: %d\n", produtolinha1);
    cout("Soma de todos os elementos da matriz: %d\n", somatodoselementos);
    cout("Média dos elementos da matriz: %.0f\n", mediaelementos);
    return 0;
}