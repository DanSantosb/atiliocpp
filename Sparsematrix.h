#ifndef SPARSE_MATRIX_H
#define SPARSE_MATRIX_H

#include <iostream>
#include "Node.h"
using namespace std;


class SparseMatrix {
private:
    Node* head_linhas;  // sentinela das linhas
    Node* head_colunas; // sentinela das colunas
    int linhas;         
    int colunas;        

public:
    //recebe o numero de linhas e colunas, e analisa se os valores são validos
    SparseMatrix(int l, int c) {
        if (l <= 0 || c <= 0) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }

        linhas = l;
        colunas = c;

        // cria os sentinelas para as linhas e colunas
        head_linhas = new Node(0, nullptr, nullptr, 0, 0);
        head_colunas = new Node(0, nullptr, nullptr, 0, 0);

       
        Node* atual = head_linhas;
        for(int i = 1; i <= l; i++){
            Node* novo = new Node(0, nullptr, nullptr, i, 0); //cria um novo sentinela para a linha
            atual -> abaixo = novo; // conecta os sentinelas das linhas
            novo -> direita = novo;
            atual = novo;
        }
        atual -> abaixo = head_linhas; // tornacircular

        atual = head_colunas; //axiliar para conectar os sentinelas
        for(int i = 1; i <= c; i++){
            Node* novo = new Node(0, nullptr, nullptr, 0, i); //cria um novo sentinela para a coluna
            atual -> direita = novo; // conecta os sentinelas das colunas
            novo -> direita = novo;
            atual = novo;
        }
        atual -> direita = head_colunas;// torna circular
    }

    // Destrutor
    ~SparseMatrix() {
        desalocar();
    }

    void print() {
        Node* atualLinha = head_linhas->abaixo;
        while (atualLinha != head_linhas) { // Anda pelas linhas
            Node* atual = atualLinha->direita;

            for (int j = 1; j <= colunas; j++) {   // Anda pelas colunas
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

    void inserir(int l, int c, double valor) {
        if (l > linhas || c > colunas || l <= 0 || c <= 0) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }else if (valor == 0) {
            return;
        }
        //procura a linha certa
        Node* atualLinha = head_linhas;
        while (atualLinha -> linha != l) {
            atualLinha = atualLinha->abaixo;
        }
        // encontra a posição correta na linha
        Node* prevLinha = atualLinha;
        while (prevLinha -> direita != atualLinha && prevLinha -> direita -> coluna < c) {
            prevLinha = prevLinha->direita;
        }
        // procura a coluna certa
        Node* atualColuna = head_colunas;
        while (atualColuna -> coluna != c) {
            atualColuna = atualColuna->direita;
        }
        // encontra a posição correta na coluna
        Node* prevColuna = atualColuna;
        while (prevColuna -> abaixo != atualColuna && prevColuna -> abaixo -> linha < l) {
            prevColuna = prevColuna->abaixo;
        }
        // cria o novo nó
        Node* novo = new Node(valor, nullptr, nullptr, l, c);
        novo -> direita = prevLinha->direita;
        novo -> abaixo = prevColuna->abaixo;
        prevLinha->direita = novo;
        prevColuna->abaixo = novo;
    }

    double devolver(int l, int c) {
        if (l <= 0 || l > linhas || c <= 0 || c > colunas) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }else{
        // procura a linha certa
        Node* atualLinha = head_linhas;
        while (atualLinha->linha != l) {
            atualLinha = atualLinha->abaixo;
        }
        // procura a  coluna certa
        Node* atual = atualLinha->direita;
        while (atual != atualLinha) {
            if (atual->coluna == c) {
                return atual -> valor;
            }
            atual = atual -> direita;
        }

        // se não encontrar retorna 0
        return 0;
        }
    }

    void desalocar() {
        Node* linha_atual = head_linhas -> abaixo;
        while (linha_atual != head_linhas) {
            Node* atual = linha_atual;
            linha_atual = linha_atual -> abaixo;

            Node* coluna_atual = atual -> direita;
            while (coluna_atual != atual) {
                Node* aux = coluna_atual;
                coluna_atual = coluna_atual -> direita;
                delete aux;
            }
            delete atual;
        }
        // libera os sentinelas
        delete head_linhas;
        delete head_colunas;
        head_linhas = nullptr;
        head_colunas = nullptr;
    }
};
#endif
