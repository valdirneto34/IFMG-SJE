#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    int n, i = 0;
    cin >> n;
    double numeros[n];
    while (i < n)
    {
        cin >> numeros[i];
        cout << setprecision(4) << fixed;
        cout << sqrt(numeros[i]) << endl;
        i++;
    }

    return 0;
}

/*
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main(){
    // Seu código vai aqui
    int n, i;
    cin >> n;
    float raiz, lista[n];
    for(i=0;i<n;i++){
        cin >> lista[n];
        raiz = sqrt(lista[n]);
        cout << setprecision(4) << fixed;
        cout << raiz << endl;
    }
    return 0;
}

*/