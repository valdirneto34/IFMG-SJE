#include <stdio.h>
#include <locale.h>

int main()
{
    setlocale(LC_ALL, "portuguese");
    int x1 = 11, x2 = 22, x3 = 33;
    int *p = &x1;
    x2 = *p;
    *p = x3;
    p = &x3;
    *p = 0;

    cout("cont: %d  %d  %d  %d\n\n", x1, x2, x3, *p);
    cout("cont: %d  %d  %d  %d\n\n", &x1, &x2, &x3, p);

    return 0;
}