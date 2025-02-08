#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include "Sparsematrix.h"

using namespace std;

// Função para ler uma matriz esparsa de um arquivo
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

// Função para somar duas matrizes
SparseMatrix Soma(SparseMatrix& A, SparseMatrix& B) {
    SparseMatrix C = A + B; // Usa o operador sobrecarregado
    cout << "Matriz C (A + B):" << endl;
    C.print();
    return C; // Retorna a matriz resultante
}

// Função para multiplicar duas matrizes
SparseMatrix Mult(SparseMatrix& A, SparseMatrix& B) {
    SparseMatrix C = A * B; // Usa o operador sobrecarregado
    cout << "Matriz C (A * B):" << endl;
    C.print();
    return C; // Retorna a matriz resultante
}

// Função para obter as dimensões de uma matriz a partir de um arquivo
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
    vector <SparseMatrix> matrizes;
    int posicao = 0;
    /*string nome_arquivoA, nome_arquivoB;

    cout << "Olá, digite o nome do arquivo referente à Matriz (A) a ser aberto." << endl;
    getline(cin, nome_arquivoA);
    nome_arquivoA += ".txt";

    pair<int, int> dimensoesA = Dimensions(nome_arquivoA);
    if (dimensoesA.first == -1 || dimensoesA.second == -1) {
        cout << "Erro ao ler as dimensões da matriz A." << endl;
        return 1;
    }

    SparseMatrix A(dimensoesA.first, dimensoesA.second);
    readSparseMatrix(A, nome_arquivoA);

    cout << "Olá, digite o nome do arquivo referente à Matriz (B) a ser aberto." << endl;
    getline(cin, nome_arquivoB);
    nome_arquivoB += ".txt";

    pair<int, int> dimensoesB = Dimensions(nome_arquivoB);
    if (dimensoesB.first == -1 || dimensoesB.second == -1) {
        cout << "Erro ao ler as dimensões da matriz B." << endl;
        return 1;
    }

    SparseMatrix B(dimensoesB.first, dimensoesB.second);
    readSparseMatrix(B, nome_arquivoB);

    cout << "Matriz A:" << endl;
    A.print();
    cout << "Matriz B:" << endl;
    B.print();

    Mult(A, B);
    Soma(A, B);
    */

    while(true) {
		string comando, token;
		getline(cin, comando);
		stringstream ss{ comando };
        ss >> token;

        cout << "$" << ss.str() << endl;

        if(token == "create") {
			int l, c;
            ss >> l >> c;
			matrizes.emplace_back(l, c);
            cout << "Matriz de tamanho:" << l << "x" << c << " criada na posição " << matrizes.size() - 1 << endl;
		}
		// exit
		if(token == "exit") {
			matrizes.clear();
			break;
		}

        if(token == "print") {
            int x;
            ss >> x;
			matrizes[x].print();
			break;
		}

	if(token == "inserir"){
            int x, c, l, v;
            ss >> x >> c >> l >> v;
            
            matrizes[x].inserir(c, l, v);

            cout << "o valor: " << v << ", foi adicionado na linha: " << l << ",e coluna: " << c << endl;
        }
    }

    return 0;
}
