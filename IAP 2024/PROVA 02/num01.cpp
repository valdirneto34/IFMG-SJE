#include <iostream>
using namespace std;
int main()
{
    int n, m, album[105], X, cont = 0;
    cout << "Digite quantas figurinhas faltam: ";
    cin >> n;
    cout << "Digite quantas figurinhas voce comprou: ";
    cin >> m;
    for (int i = 1; i <= n; i++)
    {
        album[i] = 0;
    }
    for (int i = 0; i < m; i++)
    {
        cin >> X;
        album[X] = 1;
    }
    for (int i = 1; i <= n; i++)
    {
        if (album[i] == 0)
        {
            cont++;
        }
    }
    cout("Faltam %d figurinhas.\n", cont);
    return 0;
}
/*
#include <iostream>
using namespace std;
int main()
{
    int NN, MM, *figurinhas, figurinhas_faltam = 0, cont = 1, antpenum = 0, penum = 0, ultim = 0;
    cin >> NN;
    cout << "Digite quantas figurinhas voce comprou: ";
    cin >> MM;
    figurinhas = new int[MM];
    for (int i = 0; i < MM; i++)
    {
        cin >> ultim;
        if (ultim != penum && penum != antpenum)
        {
            figurinhas[i] = ultim;
            cont++;
        }
        antpenum = penum;
        penum = ultim;
        ultim = 0;
    }
    figurinhas_faltam = NN - cont;
    cout << "Faltam " << figurinhas_faltam;
    cout << " figurinhas." << endl;
    return 0;
}
*/
