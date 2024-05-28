#include <iostream>
#include <string>
#include <fstream>
#include <cwchar>
#include <vector>
#include <map>

namespace Huffman {

    void ler_arquivo(std::wstring& filename) {
        std::wifstream arq(filename.c_str());
        if (!arq) {
            std::wcout << L"\nNão foi possível abrir o arquivo.\n\n";
            exit(1);
        }

        std::map<wchar_t, int> frequencia;

        wchar_t c;  

        while(arq.get(c)){
            frequencia[c]++;
        }
    
        std::wcout << std::endl;

        arq.close();
    }

    void exibir_texto(std::wstring& filename) {
        std::wifstream arq(filename.c_str());
        if (!arq) {
            std::wcout << L"\nNão foi possível abrir o arquivo.\n\n";
            exit(2);
        }

        wchar_t c;
        while(arq.get(c)){
            std::wcout << c;
        }
        std::wcout << std::endl;

        arq.close();
    }
}
