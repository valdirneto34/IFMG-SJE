#include <stdio.h>
#include <locale.h>


int main()
{
    setlocale(LC_ALL, "portuguese");
    int opc;
    while (opc != 4)
    {
        system("cls");
        printf("1 - Abrir Arquivo\n");
        printf("2 - Salvar Arquivo\n");
        printf("3 - Imprimir Arquivo\n");
        printf("4 - Sair\n");
        printf("Digite uma opção: ");
        scanf("%d", &opc);

        switch (opc)
        {
        case 1:
            printf("Abrindo arquivo!\n");
            break;
        case 2:
            printf("Salvando arquivo!\n");
            break;
        case 3:
            printf("Imprimindo arquivo!\n");
            break;
        case 4:
            printf("Saindo...\n");
            break;
        default:
            printf("Opção inválida!\n");
        }
        system("pause");
    }
    return 0;
}
