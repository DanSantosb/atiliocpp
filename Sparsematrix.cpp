#ifndef Sparse_matrix
#define Sparse_matrix
#include <iostream>
#include "Node.h"
using namespace std;

class SparseMatrix {
private:
    Node* head_linhas; // ponteiro para o sentinela
    Node* head_colunas; // ponteiro para o sentinela
    int linhas;
    int colunas;
public:

    SparseMatrix(){
        head_colunas = new Node(0, nullptr, nullptr, 0, 0);
        head_linhas = new Node(0, nullptr, nullptr, 0, 0);
        head_colunas -> direita = head_colunas;        
        head_colunas -> abaixo = head_colunas;
        head_linhas -> direita = head_linhas;
        head_linhas -> abaixo = head_linhas;
        linhas = 0;
        colunas = 0;
    }

    //recebe o numero de linhas e colunas, e analisa se os valores são validos
    SparseMatrix(int m, int n){
        if(m <= 0 || n <= 0){
            throw invalid_argument("ERRO: Valores de M e N invalidos, tente novamente.");
        }
        linhas = m;
        colunas = n;
        head_linhas = head_linhas;
        head_colunas = head_colunas;
    }

    //função para desalocar memoria
    void desalocar() {
        Node* linha_atual = head_linhas; //caminha pelos nós
        while (linha_atual) {
            Node* atual = linha_atual;
            linha_atual = linha_atual->abaixo;

            // Libera os nós da linha atual
            while (atual) {
                Node* aux = atual;
                atual = atual->direita;
                delete aux;
            }
        }

        // Libera os ponteiros para os sentinelas
        delete head_linhas;
        delete head_colunas;
        head_linhas = nullptr;
        head_colunas = nullptr;
    }

    //chamada do destrutor
    ~SparseMatrix(){
       desalocar();
    }

    void inserir(int n){
        
    }

};  


#endif // Fim da classe
