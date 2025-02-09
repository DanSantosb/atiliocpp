//João Victor de Sousa Medeiros & Danilo Santos Batista
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
SparseMatrix Soma(vector<SparseMatrix*>& matrizes, int idxA, int idxB) {
    SparseMatrix C = *matrizes[idxA] + *matrizes[idxB]; // Usa o operador sobrecarregado
    cout << "Matriz Resultante:" << endl;
    cout << "x---------------------------------------------x" << endl;
    C.print();
    cout << "x---------------------------------------------x" << endl;
    return C; // Retorna a matriz resultante
}


// Função para multiplicar duas matrizes
SparseMatrix Mult(vector<SparseMatrix*>& matrizes, int idxA, int idxB) {
    SparseMatrix C = *matrizes[idxA] * *matrizes[idxB]; // Usa o operador sobrecarregado
    cout << "Matriz Resultante:" << endl;
    cout << "x---------------------------------------------x" << endl;
    C.print();
    cout << "x---------------------------------------------x" << endl;
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
    vector <SparseMatrix*> matrizes;

    cout<<"Digite \"Help\" para acessar o bloco de comandos"<<endl;
    while(true) {
		string comando, token;
        getline(cin, comando);
		stringstream ss{ comando };
        ss >> token;

        cout << "----->" << ss.str() << endl;

        if(token == "Criar") {
			int l, c;
            string Tamanho;

            cout<<"Digite quantidade de linhas e colunas da Matriz"<<endl;
            getline(cin, Tamanho);
            stringstream ss{ Tamanho };
            ss >> l >> c;

            matrizes.push_back(new SparseMatrix(l, c));
            cout << "Matriz de tamanho:" << l << "x" << c << " criada na posicao " << matrizes.size() - 1 << endl;

		}else if(token == "Exit") {
			matrizes.clear();
			break;
		}else if(token == "Print") {
            cout<<"Digite a posicao da Matriz:"<<endl;
            int x;
            cin >> x;
            cout << "x---------------------------------------------x" << endl;
			matrizes[x]->print();
            cout << "x---------------------------------------------x" << endl;

			break;

		}else if(token == "Inserir"){
            int x, c, l, v;
            cout<<"Digite a posicao da matriz que o valor sera inserido"<<endl;
            cin >> x;

            cout<<"Digite a coluna, a linha e o valor a ser inserido respectivamente"<<endl;
            cin>> c >> l >> v;
            
            matrizes[x]->inserir(c, l, v);

            cout << "o valor: " << v << ", foi adicionado na linha: " << l << ", e coluna: " << c << endl;

        }else if (token == "Limpar"){
            int i;
            cout<<"Digite a posicao da matriz a ser excluida:"<<endl;           
            cin>>i;
            delete matrizes[i]; // Libera a memória da matriz
            matrizes.erase(matrizes.begin() + i); // Remove a posição i do vetor
            cout << "Matriz na posicao " << i << " foi excluida." << endl;

        }else if (token == "Valor"){
            cout << "Digite a posição da matriz que voce quer ler :" << endl;
            int i,c, l;
            cin >> i;
            cout << "Digite a coluna e a linha:" << endl;
            cin >> c, l;

            cout << "o Valor da linha " << l <<" e coluna " << c << "e: " << matrizes[i]->devolver(l,c)<<endl;

        }else if (token == "TXT"){
            string nome_arquivo;

            cout << "Ola, digite o nome do arquivo referente a Matriz a ser aberto:" << endl;
            getline(cin, nome_arquivo);
            nome_arquivo += ".txt";
    
            pair<int, int> dimensoesA = Dimensions(nome_arquivo);
            if (dimensoesA.first == -1 || dimensoesA.second == -1) {
                cout << "Erro ao ler as dimensoes da matriz A." << endl;
                return 1;
            }
    
            matrizes.push_back(new SparseMatrix(dimensoesA.first, dimensoesA.second));
            readSparseMatrix(*matrizes.back(), nome_arquivo);
    
            cout << "Matriz" << " criada na posicao " << matrizes.size() - 1 <<endl;

        } else if (token == "Soma") {
            cout<<"Digite a posicao das matrizes a serem somadas"<<endl;
            int idxA, idxB;
            cin >> idxA >> idxB;
        
            SparseMatrix resultado = Soma(matrizes, idxA, idxB);
            matrizes.push_back(new SparseMatrix(resultado));
            cout << "Resultado da soma armazenado na posicao " << matrizes.size() - 1 << endl;
        
        }else if (token == "Mult"){
            cout<<"Digite a posicao das matrizes a serem multiplicadas"<<endl;
            int idxA, idxB;
            cin >> idxA >> idxB;
        
            SparseMatrix resultado = Mult(matrizes, idxA, idxB);
            matrizes.push_back(new SparseMatrix(resultado));
            cout << "Resultado da multiplicacao armazenado na posicao " << matrizes.size() - 1 << endl;

        }else if (token == "Printfull"){
            if(matrizes.empty()){
                cout << "nenhuma matriz encontrada" <<endl;
               break;
            }
            for (int i = 0; i < matrizes.size(); i++){
                cout << "x---------------------------------------------x" << endl;
			    matrizes[i]->print();   
            }
            cout << "x---------------------------------------------x" << endl;

        }else if (token == "Limparfull"){
            while(!matrizes.empty()){
                delete matrizes[matrizes.size() - 1];
                matrizes.pop_back();
            }

        }else if(token == "Help"){
            cout<<"------------------------------------------------------------"<<endl;
            cout<<"Criar:       Cria a Matriz"<<endl;
            cout<<"Inserir:     Insere os valores"<<endl;
            cout<<"Valor:       Retorna o valor da celula escolhida"<<endl;
            cout<<"TXT:         Le uma Matriz pre definida em um arquivo txt"<<endl;
            cout<<"Soma:        Soma 2 matrizes"<<endl;
            cout<<"Mult:        Multiplica 2 matrizes"<<endl;
            cout<<"Print:       Mostra a Matriz criada"<<endl;
            cout<<"Printfull:   Mostra todas as matrizes"<<endl;
            cout<<"Limpar:      Exclue uma Matriz em especifico"<<endl;
            cout<<"Limparfull:  Exclue TODAS as matrizes"<<endl; 
            cout<<"Exit:        Encerra o programa"<<endl;
            cout<<"------------------------------------------------------------"<<endl;
        }
        
    }

    return 0;
}
