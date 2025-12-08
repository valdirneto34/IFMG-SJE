#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    double x, y;
    cin >> x;
    cin >> y;
    cout << setprecision(4) << fixed;
    cout << pow(x, y) << endl;
    return 0;
}
