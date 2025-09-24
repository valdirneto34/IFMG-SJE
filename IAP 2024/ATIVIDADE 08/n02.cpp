#include <iostream>

using namespace std;

int main()
{
    int x;
    cin >> x;
    for (int i = 1; i <= x; i++)
    {
        if (x % i == 0)
        {
            cout << i << " ";
        }
    }
    return 0;
}

/*
#include <iostream>

using namespace std;

int main(){
    int x, i=1;
    cin >> x;
    while(i <= x){
        if(x % i == 0){
            cout << i << " ";
        }
        i++;
    }
    return 0;
}
*/