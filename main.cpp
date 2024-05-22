#include <iostream>
#include <fstream>
#include <string>
#include "huffman_lib.cpp"

using namespace std;

int main() {
    int option;

    do {
        wcout << L"===== Menu de Codificação Huffman =====" << endl;
        wcout << L"1. Ler e analisar arquivos de texto" << endl;
        wcout << L"2. Construir uma árvore de Huffman" << endl;
        wcout << L"3. Gerar tabela de codificação" << endl;
        wcout << L"4. Exibir a árvore e a tabela" << endl;
        wcout << L"5. Exibir o tamanho do arquivo original, o tamanho resultante da compactação e a diferença entre ambos (valores absoluto e percentual)" << endl;
        wcout << L"6. Sair" << endl;
        wcout << L"Escolha uma opção: ";

        cin >> option;

        switch(option) {
            case 1:
                Huffman::ler_arquivo_w();
                break;
            case 2:
                // Implementar a operação de construir uma árvore de Huffman
                break;
            case 3:
                // Implementar a operação de gerar e exibir tabela de codificação
                break;
            case 4:
                // Implementar a operação de exibir a árvore e a tabela
                break;
            case 5:
                // Implemente a operação de exibir o tamanho do arquivo
                break;
            case 6:
                cout << "Encerrando programa..." << endl;
                break;
            default:
                cout << "Opção inválida. Escolha novamente." << endl;
                break;
        }
    } while(option != 6);

    return 0;
}