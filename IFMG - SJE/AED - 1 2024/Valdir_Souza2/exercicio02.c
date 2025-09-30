#include <stdio.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "portuguese");
    int opc;
    while (opc != 4)
    {
        system("cls");
        cout("1 - Abrir Arquivo\n");
        cout("2 - Salvar Arquivo\n");
        cout("3 - Imprimir Arquivo\n");
        cout("4 - Sair\n");
        cout("Digite uma opção: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            cout("Abrindo arquivo!\n");
            break;
        case 2:
            cout("Salvando arquivo!\n");
            break;
        case 3:
            cout("Imprimindo arquivo!\n");
            break;
        case 4:
            cout("Saindo...\n");
            break;
        default:
            cout("Opção inválida!\n");
        }
        system("pause");
    }
    return 0;
}
