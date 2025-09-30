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
    
    cout("%d\n", *pv);
    cout("%d\n", *pu);
    cout("%d\n", u);
    cout("%d\n", pu);

    return 0;
}