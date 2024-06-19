#include <iostream>
#include <string>
#include <fstream>
#include <cwchar>
#include <vector>
#include <map>

namespace Huffman
{
    void ler_arquivo(std::wstring &filename){
        std::wifstream file(filename.c_str());
        if (!file){
            std::wcout << L"\nNão foi possível abrir o arquivo.\n\n";
            exit(1);
        }

        std::map<wchar_t, int> frequencia;

        wchar_t c;

        while (file.get(c)){
            frequencia[c]++;
        }

        file.close();
    }

    void exibir_arquivo(std::wstring &filename){
        std::wifstream file(filename.c_str());
        if (!file){
            std::wcout << L"\nNão foi possível abrir o arquivo.\n\n";
            exit(2);
        }

        wchar_t c;

        while (file.get(c)){
            std::wcout << c;
        }

        file.close();
    }

    std::streampos exibir_tamanho_arquivo(std::wstring &filename){
        std::wifstream file(filename.c_str(), std::ios::binary);
        if (!file) {
            std::wcout << "Erro ao abrir o arquivo." << std::endl;
        } 

        file.seekg(0, std::ios::end);
        std::streampos fileSize = file.tellg(); 
        file.seekg(0, std::ios::beg); 
        
        return fileSize;

        file.close();
    }
}
