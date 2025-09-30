#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int x = 100, y = 20;
    int *pont;
    pont = &x;
    *pont = y;

    cout("%d\n", x);
    cout("%d\n", y);
    cout("%d  %d  %d\n", x, y, *pont);

    return 0;
}