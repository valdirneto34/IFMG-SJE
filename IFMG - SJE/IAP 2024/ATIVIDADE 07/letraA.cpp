#include <iostream>

using namespace std;

int main(){
    // Seu código vai aqui
    int l, c;
    cin >> l;
    cin >> c;
    cout << c * l + (c-1) * (l-1) ;
    cout << ((l-1)*2) + ((c-1)*2) ;
    
    system("pause");
    return 0;
}
