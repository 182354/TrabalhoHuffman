#include <iostream>
#include <fstream>
#include <codecvt>
#include <locale>
#include "huffman_lib.cpp"

using namespace std;

int main() {
    // Solicitar o nome do arquivo do usuário
    string filename;
    cout << "Digite o nome do arquivo a ser comprimido: ";
    cin >> filename;

    // Abrir o arquivo de entrada para leitura em formato UTF-8
    wifstream inputFile("../docs/" + filename);
    inputFile.imbue(locale(inputFile.getloc(), new codecvt_utf8<wchar_t>));

    // Abrir o arquivo de saída para escrita em formato UTF-8
    wofstream outputFile("../output/resultado.txt");
    outputFile.imbue(locale(outputFile.getloc(), new codecvt_utf8<wchar_t>));

    // Verificar se o arquivo de entrada foi aberto corretamente
    if (!inputFile) {
        cout << "Erro ao abrir o arquivo.\n";
        return 1;
    }

    // Verificar se o arquivo de saída foi aberto corretamente
    if (!outputFile) {
        cout << "Erro ao criar o arquivo de saída.\n";
        return 2;
    }


    return 0;
}