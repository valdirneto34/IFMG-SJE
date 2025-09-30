#include <iostream>
#include <fstream>

using namespace std;

int main() {

    ofstream arq;
    arq.open("arquivo.txt");
    if(!arq.is_open()){
        cout << "Erro ao abrir o arquivo!" << endl;
        return 1;
    }

    arq << "Exemplo de texto para arquivo" << endl;
    arq.flush();
    arq.close();
    
    return 0;
}