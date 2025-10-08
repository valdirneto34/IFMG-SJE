#include <stdio.h>

int main()
{
    int u, v;
    int *pu, *pv;
    u = 5;
    v = 5;
    pv = &v;
    *pv = v + 1;
    pu = &u;
    
    printf("%d\n", *pv);
    printf("%d\n", *pu);
    printf("%d\n", u);
    printf("%d\n", pu);

    return 0;
}