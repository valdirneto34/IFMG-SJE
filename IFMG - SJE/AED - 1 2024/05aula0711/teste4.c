#include <stdio.h>

int main()
{
    int s, a = 2, b = 3;
    int *pS, *pA, *pB;
    pA = &a;
    pB = &b;
    pS = &s;
    *pS = *pA + *pB;
    printf("O ponteiro pS vale: %d\n", *pS);

    return 0;
}
