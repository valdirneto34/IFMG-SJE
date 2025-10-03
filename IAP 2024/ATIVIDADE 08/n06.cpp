#include <iostream>

using namespace std;

int main()
{
    int n, lampadas;
    bool l1 = false;
    bool l2 = false;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> lampadas;
        if (lampadas == 1)
        {
            l1 = not l1;
        }
        else if(lampadas == 2)
        {
            l1 = not l1;
            l2 = not l2;
        }
    }
    cout << l1 << endl;
    cout << l2;
    return 0;
}

/*
#include <iostream>

using namespace std;

int main()
{
    int n, lampadas, i=0;
    bool l1 = false, l2 = false;
    cin >> n;
    while(i < n)
    {
        cin >> lampadas;
        if (lampadas == 1)
        {
            l1 = !l1;
        }
        else if(lampadas == 2)
        {
            l1 = !l1;
            l2 = !l2;
        }
    i++;
    }
    cout << l1 << endl;
    cout << l2;
    return 0;
}
*/