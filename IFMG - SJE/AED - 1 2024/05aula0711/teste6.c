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

    cout("%d\n", pa);
    cout("%d\n", *pa);
    cout("%d\n", *pb);
    cout("%d\n", c);
    return 0;
}
