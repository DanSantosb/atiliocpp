#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>
#include "Node.h"
using namespace std;
class SparseMatrix {
private:
    Node* head_linhas; // ponteiro para o sentinela das linhas
    Node* head_colunas; // ponteiro para o sentinela das colunas
    int linhas;
    int colunas;

public:
    SparseMatrix(int l, int c) : linhas(l), colunas(c) {
        if (l <= 0 || c <= 0) {
            throw std::invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }

        head_linhas = new Node(0, nullptr, nullptr, 0, 0);
        head_colunas = new Node(0, nullptr, nullptr, 0, 0);

        Node* atual = head_linhas;
        for (int i = 1; i <= l; i++) {
            Node* novo = new Node(0, nullptr, nullptr, i, 0);
            atual->abaixo = novo;
            novo->direita = novo;
            atual = novo;
        }
        atual->abaixo = head_linhas;

        atual = head_colunas;
        for (int i = 1; i <= c; i++) {
            Node* novo = new Node(0, nullptr, nullptr, 0, i);
            atual->direita = novo;
            novo->abaixo = novo;
            atual = novo;
        }
        atual->direita = head_colunas;
    }

    ~SparseMatrix() {
        desalocar();
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

        delete head_linhas;
        delete head_colunas;
        head_linhas = nullptr;
        head_colunas = nullptr;
    }

    void inserir(int l, int c, double valor) {
        if (l <= 0 || l > linhas || c <= 0 || c > colunas) {
            throw std::invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }
        if (valor == 0) {
            return;
        }

        Node* novo = new Node(valor, nullptr, nullptr, l, c);

        // Inserir na linha
        Node* linha_atual = head_linhas;
        while (linha_atual->linha != l) {
            linha_atual = linha_atual->abaixo;
        }

        Node* coluna_atual = linha_atual;
        while (coluna_atual->direita != linha_atual && coluna_atual->direita->coluna < c) {
            coluna_atual = coluna_atual->direita;
        }
        novo->direita = coluna_atual->direita;
        coluna_atual->direita = novo;

        // Inserir na coluna
        Node* coluna_sent = head_colunas;
        while (coluna_sent->coluna != c) {
            coluna_sent = coluna_sent->direita;
        }

        Node* linha_coluna = coluna_sent;
        while (linha_coluna->abaixo != coluna_sent && linha_coluna->abaixo->linha < l) {
            linha_coluna = linha_coluna->abaixo;
        }
        novo->abaixo = linha_coluna->abaixo;
        linha_coluna->abaixo = novo;
    }

    double devolver(int l, int c) {
        if (l <= 0 || l > linhas || c <= 0 || c > colunas) {
            throw std::invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }

        Node* linha_atual = head_linhas;
        while (linha_atual->linha != l) {
            linha_atual = linha_atual->abaixo;
        }

        Node* coluna_atual = linha_atual->direita;
        while (coluna_atual != linha_atual) {
            if (coluna_atual->coluna == c) {
                return coluna_atual->valor;
            }
            coluna_atual = coluna_atual->direita;
        }

        return 0;
    }

    void print() {
        Node* linha_atual = head_linhas->abaixo;
        while (linha_atual != head_linhas) {
            Node* coluna_atual = linha_atual->direita;

            for (int j = 1; j <= colunas; j++) {
                if (coluna_atual != linha_atual && coluna_atual->coluna == j) {
                    std::cout << coluna_atual->valor << " ";
                    coluna_atual = coluna_atual->direita;
                } else {
                    std::cout << "0 ";
                }
            }

            std::cout << std::endl;
            linha_atual = linha_atual->abaixo;
        }
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

#endif // SPARSE_MATRIX_H
