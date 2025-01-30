#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>
#include "Node.h"
using namespace std;

class SparseMatrix {
private:
    Node* head_linhas;  // Sentinela das linhas
    Node* head_colunas; // Sentinela das colunas
    int linhas;      
    int colunas;        

public:

    SparseMatrix(int l, int c) {
        if (l <= 0 || c <= 0) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }

        linhas = l;
        colunas = c;

        // cria sentinelas para as linhas e colunas
        head_linhas = new Node(0, nullptr, nullptr, 0, 0);
        head_colunas = new Node(0, nullptr, nullptr, 0, 0); 

       
        Node* atual = head_linhas;
        for (int i = 1; i <= l; i++) {
            Node* novo = new Node(0, nullptr, nullptr, i, 0); // cria um novo sentinela para a linha
            atual->abaixo = novo; // conecta os sentinelas das linhas
            novo->direita = novo; 
            atual = novo;
        }
        atual->abaixo = head_linhas; // Torna circular

      
        atual = head_colunas;
        for (int i = 1; i <= c; i++) {
            Node* novo = new Node(0, nullptr, nullptr, 0, i); // Cria um novo sentinela para a coluna
            atual->direita = novo; // conecta os sentinelas das colunas
            novo->abaixo = novo;
            atual = novo;
        }
        atual->direita = head_colunas;  // Torna circular
    }

    // Destrutor
    ~SparseMatrix() {
        desalocar();
    }

    void inserir(int l, int c, double valor) {
        if (l > linhas || c > colunas || l <= 0 || c <= 0) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        } else if (valor == 0) {
            return; 
        }
        // procura a linha
        Node* atualLinha = head_linhas;
        while (atualLinha->linha != l) {
            atualLinha = atualLinha->abaixo;
        }
        // Encontra a posição correta na linha
        Node* prevLinha = atualLinha;
        while (prevLinha->direita != atualLinha && prevLinha->direita->coluna < c) {
            prevLinha = prevLinha->direita;
        }
        // Verifica se já existe um valor na posição (l, c)
        if (prevLinha->direita != atualLinha && prevLinha->direita->coluna == c) {
            prevLinha->direita->valor = valor; // Atualiza o valor
            return;
        }
        // procura a coluna
        Node* atualColuna = head_colunas;
        while (atualColuna->coluna != c) {
            atualColuna = atualColuna->direita;
        }
        // Encontra a posição correta na coluna
        Node* prevColuna = atualColuna;
        while (prevColuna->abaixo != atualColuna && prevColuna->abaixo->linha < l) {
            prevColuna = prevColuna->abaixo;
        }

        // Cria o novo nó
        Node* novo = new Node(valor, prevLinha->direita, prevColuna->abaixo, l, c);
        prevLinha->direita = novo;
        prevColuna->abaixo = novo;
    }

    double devolver(int l, int c) {
        if (l <= 0 || l > linhas || c <= 0 || c > colunas) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }
        // procura a linha correta
        Node* atualLinha = head_linhas;
        while (atualLinha->linha != l) {
            atualLinha = atualLinha->abaixo;
        }
        // procura a coluna correta
        Node* atual = atualLinha->direita;
        while (atual != atualLinha) {
            if (atual->coluna == c) {
                return atual->valor;
            }
            atual = atual->direita;
        }
        // se não achar nada retorna 0
        return 0;
    }

    void print() {
        Node* atualLinha = head_linhas->abaixo;
        while (atualLinha != head_linhas) { // Percorre as linhas
            Node* atual = atualLinha->direita;

            for (int j = 1; j <= colunas; j++) { // Percorre as colunas
                if (atual != atualLinha && atual->coluna == j) {
                    cout << atual->valor << " ";
                    atual = atual->direita;
                } else {
                    cout << "0 ";
                }
            }
            cout << endl;
            atualLinha = atualLinha->abaixo;
        }
    }

    void desalocar() {
        Node* linha_atual = head_linhas->abaixo;
        while (linha_atual != head_linhas) {
            Node* atual = linha_atual;
            linha_atual = linha_atual->abaixo;

            Node* coluna_atual = atual->direita;
            while (coluna_atual != atual) {
                Node* aux = coluna_atual;
                coluna_atual = coluna_atual->direita;
                delete aux;
            }
            delete atual;
        }

        // Libera os sentinelas
        delete head_linhas;
        delete head_colunas;
        head_linhas = nullptr;
        head_colunas = nullptr;
    }

    SparseMatrix operator+(const SparseMatrix& outra) {
    if (this->linhas != outra.linhas || this->colunas != outra.colunas) {
        cout<< "ERRO: As matrizes devem ter as mesmas dimensões para serem somadas.";
    }

    SparseMatrix resultado(this->linhas, this->colunas);

    // Percorre as linhas da matriz atual
    Node* atualLinha = this->head_linhas->abaixo;
    while (atualLinha != this->head_linhas) {
        Node* atual = atualLinha->direita;
        while (atual != atualLinha) {
            resultado.inserir(atual->linha, atual->coluna, atual->valor);
            atual = atual->direita;
        }
        atualLinha = atualLinha->abaixo;
    }

    // Percorre as linhas da outra matriz
    atualLinha = outra.head_linhas->abaixo;
    while (atualLinha != outra.head_linhas) {
        Node* atual = atualLinha->direita;
        while (atual != atualLinha) {
            double valorAtual = resultado.devolver(atual->linha, atual->coluna);
            resultado.inserir(atual->linha, atual->coluna, valorAtual + atual->valor);
            atual = atual->direita;
        }
        atualLinha = atualLinha->abaixo;
    }

    return resultado;
    }

    SparseMatrix operator*(const SparseMatrix& outra) {
        if (this->colunas != outra.linhas) {
            cout<<"ERRO: O número de colunas da primeira matriz deve ser igual ao número de linhas da segunda matriz.";
        }

        SparseMatrix resultado(this->linhas, outra.colunas);

        // Percorre as linhas da matriz atual
        Node* atualLinha = this->head_linhas->abaixo;
        while (atualLinha != this->head_linhas) {
            // Percorre as colunas da outra matriz
            Node* atualColuna = outra.head_colunas->direita;
            while (atualColuna != outra.head_colunas) {
                double soma = 0;

                // Percorre os elementos da linha da matriz atual e da coluna da outra matriz
                Node* atual = atualLinha->direita;
                Node* outraAtual = atualColuna->abaixo;
                while (atual != atualLinha && outraAtual != atualColuna) {
                    if (atual->coluna == outraAtual->linha) {
                        soma += atual->valor * outraAtual->valor;
                        atual = atual->direita;
                        outraAtual = outraAtual->abaixo;
                    } else if (atual->coluna < outraAtual->linha) {
                        atual = atual->direita;
                    } else {
                        outraAtual = outraAtual->abaixo;
                    }
                }

                if (soma != 0) {
                    resultado.inserir(atualLinha->linha, atualColuna->coluna, soma);
                }

                atualColuna = atualColuna->direita;
            }
            atualLinha = atualLinha->abaixo;
        }

        return resultado;
    }

};

#endif
