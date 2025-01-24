#include <iostream>
#include <string>
using namespace std;

int main() {
    int linhas, colunas;
    cin >> linhas >> colunas;

    SparseMatrix matriz(linhas, colunas);

    for (int i = 1; i <= linhas; ++i) {
        for (int j = 1; j <= colunas; ++j) {
            double valor;
            cin >> valor;
            matriz.insert(i, j, valor);
        }
    }

    cout << "Matriz inserida:\n";
    matriz.print();

    return 0;
}