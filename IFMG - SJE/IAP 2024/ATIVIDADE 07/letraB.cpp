#include <iostream>

using namespace std;

int main()
{
    int t1, t2, t3;
    cin >> t1 >> t2 >> t3;
    if (t1 <= t2 && t2 <= t3)
    {
        cout << "1" << endl;
        cout << "2" << endl;
        cout << "3";
    }
    else if (t1 <= t3 && t3 <= t2)
    {
        cout << "1" << endl;
        cout << "3" << endl;
        cout << "2";
    }
    else if (t2 <= t3 && t3 <= t1)
    {
        cout << "2" << endl;
        cout << "3" << endl;
        cout << "1";
    }
    else if (t2 <= t1 && t1 <= t3)
    {
        cout << "2" << endl;
        cout << "1" << endl;
        cout << "3";
    }
    else if (t3 <= t1 && t1 <= t2)
    {
        cout << "3" << endl;
        cout << "1" << endl;
        cout << "2";
    }
    else if (t3 <= t2 && t2 <= t1)
    {
        cout << "3" << endl;
        cout << "2" << endl;
        cout << "1";
    }

    return 0;
}

/*
t1 = tempo1
t2 = tempo2
t3 = tempo3
*/