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
    SparseMatrix(int l, int c){
        if(l <= 0 || c <= 0){
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }
        linhas = l;
        colunas = c;
        // Criar nó sentinela para as linhas e colunas
        head_linhas = new Node(0, nullptr, nullptr, 0, 0);
        head_colunas = new Node(0, nullptr, nullptr, 0, 0);

        Node* atual = head_linhas; // Criar um axiliar para conectar os sentinelas
        for(int i = 0; i <= l; i++){
            Node* novo = new Node(0, nullptr, nullptr, i, 0); //cria um novo sentinela para a linha
            atual -> abaixo = novo; // conecta os sentinelas das linhas
            novo -> direita = novo;
            atual = novo;
        }
        atual -> abaixo = head_linhas; // torna linha circular

        atual = head_colunas; //axiliar para conectar os sentinelas
        for(int i = 0; i <= c; i++){
            Node* novo = new Node(0, nullptr, nullptr, 0, i); //cria um novo sentinela para a coluna
            atual -> direita = novo; // conecta os sentinelas das colunas
            novo -> direita = novo;
            atual = novo;
        }
        atual -> direita = head_colunas;// torna linha circular
    }

    void print(){ 
    Node* atualLinha = head_linhas->abaixo;
        while (atualLinha != head_linhas) { // Andar pelas linhas
            Node* atual = atualLinha->direita;

            for (int j = 1; j <= colunas; j++) { // Andar pelas colunas
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

    //função para desalocar memoria
    void desalocar(){
        Node* linha_atual = head_linhas->abaixo; //caminha pelos nós
        while (linha_atual != head_linhas) { // Enquanto não voltar ao sentinela de linha
            Node* atual = linha_atual;
            linha_atual = linha_atual->abaixo;

            Node* coluna_atual = atual->direita;
            while (coluna_atual != atual) { // Enquanto não voltar ao sentinela de coluna
                Node* aux = coluna_atual;
                coluna_atual = coluna_atual->direita;
                delete aux;
            }

            delete atual;
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

    void inserir(int l, int c, double valor){
        if( l > linhas || c > colunas || l <= 0 || c <= 0 ){
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }else if(valor == 0){
            return;
        }else{

        Node* atualLinha = head_linhas;
        while (atualLinha -> linha != l) {
            atualLinha = atualLinha -> abaixo;
        }

        // Procura pela posição correta na coluna
        Node* atualColuna = head_colunas;
        while (atualColuna -> coluna != c) {
            atualColuna = atualColuna -> direita;
        }

        // Insere o novo valor
        Node* novo = new Node(valor, nullptr, nullptr, l, c);
        novo -> direita = atualLinha -> direita;
        atualLinha -> direita = novo;

        novo -> abaixo = atualColuna -> abaixo;
        atualColuna -> abaixo = novo;
        }
    }

    double devolver(int l, int c){
        if (l <= 0 || l > linhas || c <= 0 || c > colunas) {
            throw invalid_argument("ERRO: Valores de linha e(ou) coluna invalidos, tente novamente.");
        }
        Node* atual = head_linhas;

        while (atual -> linha != l) { //procura a linha certa
            atual = atual -> abaixo;
        }

    Node* linhaAtual = atual->direita;
    while (linhaAtual != atual) {
        if (linhaAtual->coluna == c) {
            return linhaAtual->valor;
        }
        linhaAtual = linhaAtual->direita;
    }
        return 0;
    }
};  


#endif // Fim da classe
