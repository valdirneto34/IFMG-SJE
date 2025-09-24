#include <iostream>

using namespace std;

int main()
{
    int x, i = 1;
    cin >> x;
    while (i <= 10)
    {
        cout << x << " * ";
        cout << i << " = ";
        cout << x * i << endl;
        i++;
    }
    return 0;
}

/*
#include <iostream>

using namespace std;

int main(){
    // Seu código vai aqui
    int i, x;
    cin >> x;
    for(i=1;i<=10;i++){
        cout << x << " * ";
        cout << i << " = ";
        cout << x*i << endl;
    }

    return 0;
}
*/