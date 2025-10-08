#include <iostream>
using namespace std;

int main()
{
    int n, i = 1, num_atual, num_anterior, cont = 1, maior_seq = 0;
    cin >> n;
    while (true)
    {
        cin >> num_atual;
        if (i == 1)
            num_anterior = num_atual;
        else
        {
            if (num_anterior == num_atual)
            {
                cont++;
                if (cont > maior_seq)
                    maior_seq = cont;
                num_anterior = num_atual;
            }
            else
            {
                cont = 1;
                num_anterior = num_atual;
            }
        }
        i++;
        if (i == n)
            break;
    }
    cout << maior_seq;
    return 0;
}

/*
#include <iostream>
using namespace std;

int main()
{
    int n, num_atual, num_anterior, cont = 1, maior_seq = 0;
    cin >> n;
    for (int i = 1;; i++)
    {
        cin >> num_atual;
        if (i == 1)
            num_anterior = num_atual;
        else
        {
            if (num_anterior == num_atual)
            {
                cont++;
                if (cont > maior_seq)
                    maior_seq = cont;
                num_anterior = num_atual;
            }
            else
            {
                cont = 1;
                num_anterior = num_atual;
            }
        }
        if (i == n)
            break;
    }
    cout << maior_seq;
    return 0;
}
*/
/*
11
30 30 30 40 40 40 40 40 30 30 30

14
1 1 1 20 20 20 20 3 3 3 3 3 3 3
*/