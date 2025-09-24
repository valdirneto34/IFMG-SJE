/*
4. Escreva um programa que cria duas matrizes com alocação dinâmica,
preencha com dados lidos do usuário, faça a multiplicação das matrizes e mostre o resultado.
*/
#include <iostream>

using namespace std;

int main()
{
    int **m1, **m2, **m3, nL1, nC1, nL2, nC2, soma = 0;
    cout << "Quantidade de linhas e colunas da primeira matriz: ";
    cin >> nL1 >> nC1;
    cout << "Quantidade de linhas e colunas da segunda matriz: ";
    cin >> nL2 >> nC2;
    if (nL1 == nC2)
    {
        m1 = new int[nL1];
        cout << "Lendo primeira matriz:" << endl;
        for (int i = 0; i < nL1; i++)
        {
            m1[i] = new int[nC1];
            for (int j = 0; j < nC1; j++)
            {
                printf("Valor da linha %d e coluna %d: ", i + 1, j + 1);
                cin >> m1[i][j];
            }
        }
        cout << "Lendo segunda matriz:" << endl;
        m2 = new int *[nL2];
        for (int i = 0; i < nL2; i++)
        {
            m2[i] = new int[nC2];
            for (int j = 0; j < nC2; j++)
            {
                printf("Valor da linha %d e coluna %d: ", i + 1, j + 1);
                cin >> m2[i][j];
            }
        }
        // CALCULA O PRODUTO DAS MATRIZES
        m3 = new int *[nL1];
        for (int i = 0; i < nL1; i++)
        {
            m3[i] = new int[nC2];
            for (int j = 0; j < nC2; j++)
            {
                m3[i][j] = 0;
                for (int k = 0; k < nL2; k++)
                {
                    soma += m1[i][k] * m2[k][j];
                }
                m3[i][j] = soma;
                soma = 0;
            }
        }
        cout << "\nMatriz 1: " << endl;
        for (int i = 0; i < nL1; i++)
        {
            for (int j = 0; j < nC1; j++)
            {
                cout << m1[i][j] << "   ";
            }
            cout << endl;
        }
        cout << "\nMatriz 2: " << endl;
        for (int i = 0; i < nL2; i++)
        {
            for (int j = 0; j < nC2; j++)
            {
                cout << m1[i][j] << "   ";
            }
            cout << endl;
        }

        // IMPRIME O RESULTADO
        cout << "\nResultado: " << endl;
        for (int i = 0; i < nL1; i++)
        {
            for (int j = 0; j < nC2; j++)
            {
                cout << m3[i][j] << "   ";
            }
            cout << endl;
        }
    }
    else
        cout << "Calculo impossivel! Tente novamente!" << endl;
    return 0;
}
