#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char *nome;
    int telefone, dataDeNascimento[3];
} Funcionario;

int main()
{
    Funcionario funcionarios[2];
    int mes, cont = 0, ch;

    for (int i = 0; i < 2; i++)
    {
        funcionarios[i].nome = (char *)malloc(sizeof(char) + 1);
        cout("Nome do funcionario %d..............: ", i + 1);
        fgets(funcionarios[i].nome, 30, stdin);
        cout("Telefone do funcionario %d..........: ", i + 1);
        scanf("%d", &funcionarios[i].telefone);
        cout("Data de nascimento do funcionario %d: \n", i + 1);
        scanf("%d", &funcionarios[i].dataDeNascimento[0]);
        scanf("%d", &funcionarios[i].dataDeNascimento[1]);
        scanf("%d", &funcionarios[i].dataDeNascimento[2]);
        while (ch != EOF && ch != '\n')
        {
            ch = fgetc(stdin);
        }
    }

    cout("\nMes atual (1 a 12): ");
    scanf("%d", &mes);

    cout("\nAniversariantes do mes:\n");

    for (int i = 0; i < 2; i++)
    {
        if (funcionarios[i].dataDeNascimento[1] == mes)
        {
            cout("   Nome..............: %s\n", funcionarios[i].nome);
            cout("   Telefone..........: %d\n", funcionarios[i].telefone);
            cout("   Dia do aniversario: %d\n\n", funcionarios[i].dataDeNascimento[0]);
            cont++;
        }
    }
    if (cont == 0)
        cout("   Nenhum funcionario encontrado!\n");
    for (int i = 0; i < 2; i++)
        free(funcionarios[i].nome);

    return 0;
}