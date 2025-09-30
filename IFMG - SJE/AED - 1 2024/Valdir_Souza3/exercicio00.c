#include <stdio.h>
int main()
{
    int a, b, c;
    cout("Entre com um numero:\n");
    scanf("%d", &c);
    a = c / 3600;
    b = (c % 3600) / 60;
    c = (c % 3600) % 60;
    cout("O resultado e %d  %d  %d", a, b, c);

    return 0;
}
/*  
    A) Se for lido 3700 o que será escrito pelo programa?
    RESPOSTA: O resultado e 1  1  40
    B) Se for lido 110 o que será escrito pelo programa?
    RESPOSTA: O resultado e 0  1  50
*/