#include <iostream>
using namespace std;

int main()
{

    float celsius, fahrenheit;
    cout << "Graus Celsius: ";
    cin >> celsius;
    fahrenheit = (1.8 * celsius) + 32;
    cout << "Graus Fahrenheit: " << fahrenheit << endl;

    system("pause");
    return 0;
}
