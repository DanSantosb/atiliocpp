#include <iostream>
#include <string>
#include <fstream>
#include "Sparsematrix.h"

using namespace std;

void readSparseMatrix(SparseMatrix& m, const string& texto) {
    ifstream arquivo(texto);
    if (!arquivo.is_open()) {
        cout << "Erro ao abrir o arquivo " << texto << endl;
        return;
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;

    int i, j;
    double valor;
    while (arquivo >> i >> j >> valor) {
        m.inserir(i, j, valor);
    }

    arquivo.close();
}
void Soma(){}
void Mult(){}
pair<int, int> Dimensions(const string& texto) {
    ifstream arquivo(texto);
    if (!arquivo) {
        return {-1, -1}; 
    }

    int linhas, colunas;
    arquivo >> linhas >> colunas;
    arquivo.close();

    return {linhas, colunas};
}

int main() {
    string nome_arquivoA, nome_arquivoB;

    cout << "Olá, digite o nome do arquivo referente à Matriz (A) a ser aberto." << endl;
    getline(cin, nome_arquivoA);
    nome_arquivoA += ".txt";

    pair<int, int> dimensoesA = Dimensions(nome_arquivoA);//pega as dimensoes da matriz

    SparseMatrix A(dimensoesA.first, dimensoesA.second);
    readSparseMatrix(A, nome_arquivoA);

    cout << "Olá, digite o nome do arquivo referente à Matriz (B) a ser aberto." << endl;
    getline(cin, nome_arquivoB);
    nome_arquivoB += ".txt";

    pair<int, int> dimensoesB = Dimensions(nome_arquivoB);

    SparseMatrix B(dimensoesB.first, dimensoesB.second);
    readSparseMatrix(B, nome_arquivoB);

    cout << "Matriz A:" << endl;
    A.print();
    cout << "Matriz B:" << endl;
    B.print();

    return 0;
}
