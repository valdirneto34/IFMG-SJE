#include <iostream>

using namespace std;

int main()
{
    int n, a, acessos = 0, i = 0;
    cin >> n;
    while (i < n)
    {
        cin >> a;
        acessos += a;
        i++;
        if (acessos >= 1000000)
        {
            break;
        }
    }
    cout << i << endl;
    return 0;
}

/*
#include <iostream>

using namespace std;

int main(){
    int n, a, acessos, i;
    cin >> n;
    for(i=0; acessos<1000000;i++){
        cin >> a;
        acessos += a;
    }
    cout << i << endl;
    return 0;
}
*/
