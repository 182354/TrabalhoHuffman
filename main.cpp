#include <iostream>
#include <fstream>
#include <string>
#include "huffman_lib.cpp"

using namespace std;

int main() {
    int option;

    wstring filename;

    wcout << L"Digite o nome do arquivo que queira compactar: ";
    getline(std::wcin, filename);

    Huffman::ler_arquivo(filename);

    do {
        wcout << L"===== Menu de Codificação Huffman =====" << endl;
        wcout << L"1. Mostrar o texto lido" << endl;
        wcout << L"2. Exibir a árvore" << endl;
        wcout << L"3. Exibir tabela" << endl;
        wcout << L"4. Exibir o tamanho do arquivo original" << endl;
        wcout << L"5. Exibir o tamanho do resultante da compactação e a diferença entre ambos (valores absoluto e percentual)" << endl;
        wcout << L"6. Sair" << endl;
        wcout << L"Escolha uma opção: ";

        cin >> option;

        switch(option) {
            case 1:
                Huffman::exibir_texto(filename);
                cout << endl;
                break;
            case 2:
                // Implementar a operação de exibir árvore de Huffman
                break;
            case 3:
                // Implementar a operação de exibir tabela de codificação
                break;
            case 4:
                // Implementar a operação de exibir o tamanho do arquivo original
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
