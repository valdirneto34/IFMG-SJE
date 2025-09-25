#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int x = 100, y = 20;
    int *pont;
    pont = &x;
    *pont = y;

    printf("%d\n", x);
    printf("%d\n", y);
    printf("%d  %d  %d\n", x, y, *pont);

    return 0;
}