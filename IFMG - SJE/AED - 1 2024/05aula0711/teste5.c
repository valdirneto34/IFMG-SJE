#include <stdio.h>

int main()
{
    int x = 10;
    float y = 20.5;
    char z = 'a';

    int *px;
    px = &x;
    float *py;
    py = &y;
    char *pz;
    pz = &z;

    printf("Endereco de x=%d  valor de x=%d \n\n", px, *px);
    printf("Endereco de y=%d  valor de y=%f \n\n", py, *py);
    printf("Endereco de z=%d  valor de z=%c \n\n", pz, *pz);

    return 0;
}
