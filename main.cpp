#include <iostream>
#include <string>
#include <fstream>
#include "Sparsematrix.h"
#include "Node.h"

using namespace std;
// Função para ler uma matriz esparsa de um arquivo
void readSparseMatrix(SparseMatrix& m, const string& matrizA) {
    ifstream arquivo(matrizA);
    
    if (!arquivo.is_open()) { //verifica se o arquiuvo foi aberto corretamente 
        cout << "Erro ao abrir o arquivo"<<endl;
        return;
    }

    //bloco que verifica o formato da matrix
    int linhas, colunas;
    arquivo >> linhas >> colunas;
    m = SparseMatrix(linhas, colunas);

    //bloco de posição e valor dos produtos da matrix
    int i, j;
    double valor;
    while (arquivo >> i >> j >> valor) {
        m.inserir(i, j, valor);
    }

    arquivo.close();

    
}


int main() {
    SparseMatrix A, B;
    fstream arquivo;
    string horizonte;

    readSparseMatrix(A, "matrizA.txt");
    readSparseMatrix(B, "matrizB.txt");

    arquivo.open("matrizA.txt", fstream::in);
    if (arquivo.is_open()){
        while (getline(arquivo,horizonte)){//le a linha do arquivo e add na variavel linha
            cout<<horizonte<<endl;
        }
    }else{
        cout<<"erro"<<endl;
    }
    arquivo.close();

    cout << "Matriz A:" << endl;
    A.print();

    //cout << "Matriz B:" << endl;
    //B.print();

    return 0;
}

