#include <iostream>
using namespace std;

int main()
{
    int golf1, golf2, golf3, golf4, golf5, golr1, golr2, golr3, golr4, golr5, saldo;
    cout << "Gols feitos no primeiro jogo: ";
    cin >> golf1;
    cout << "Gols recebidos no primeiro jogo: ";
    cin >> golr1;
    cout << "Gols feitos no segundo jogo: ";
    cin >> golf2;
    cout << "Gols recebidos no segundo jogo: ";
    cin >> golr2;
    cout << "Gols feitos no terceiro jogo: ";
    cin >> golf3;
    cout << "Gols recebidos no terceiro jogo: ";
    cin >> golr3;
    cout << "Gols feitos no quarto jogo: ";
    cin >> golf4;
    cout << "Gols recebidos no quarto jogo: ";
    cin >> golr4;
    cout << "Gols feitos no quinto jogo: ";
    cin >> golf5;
    cout << "Gols recebidos no quinto jogo: ";
    cin >> golr5;
    saldo = (golf1 + golf2 + golf3 + golf4 + golf5) - (golr1 + golr2 + golr3 + golr4 + golr5);
    cout << "Saldo de Gols: " << saldo << endl;

    return 0;
}