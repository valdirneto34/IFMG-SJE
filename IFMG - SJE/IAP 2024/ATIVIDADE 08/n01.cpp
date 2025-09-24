#include <iostream>

using namespace std;

int main()
{
    int n, l, c, quebrados = 0, i = 0;
    cin >> n;
    while (i < n)
    {
        cin >> l;
        cin >> c;
        if (l > c)
        {
            quebrados += c;
        }
        i++;
    }
    cout << quebrados << endl;
    return 0;
}

/*
#include <iostream>

using namespace std;

int main(){
    int n, l, c, quebrados = 0;
    cin >> n;
    for(int i=0; i<n; i++){
        cin >> l;
        cin >> c;
        if(l>c){
            quebrados += c;
    }
    }
    cout << quebrados << endl;
    return 0;
}
*/