//João Victor de Sousa Medeiros & Danilo Santos Batista
#ifndef NODE_H
#define NODE_H
#include <iostream>

struct Node {
    Node * direita ; // Nó para o proximo elemento da linha
    Node * abaixo ; // Nó para o proximo elemento da coluna
    int linha ; 
    int coluna ;
    double valor; 

    // construtor do node
    Node( double valor, Node* direita = nullptr, Node* abaixo = nullptr, int linha = 0, int coluna = 0) {
        this->valor = valor;
        this->direita = direita;
        this->abaixo = abaixo;
        this->linha = linha;
        this->coluna = coluna;
    }
};

#endif
