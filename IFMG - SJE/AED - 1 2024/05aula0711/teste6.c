#include <stdio.h>

int main()
{
    float a, b, c;
    float *pa, *pb;
    a = 2;
    b = 7;
    pa = &a;
    *pa = 2 * a;
    pb = &b;
    c = 3 * (*pb - *pa);

    printf("%d\n", pa);
    printf("%d\n", *pa);
    printf("%d\n", *pb);
    printf("%d\n", c);
    return 0;
}
