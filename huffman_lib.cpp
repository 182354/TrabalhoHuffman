#include <iostream>
#include <string>
#include <fstream>
#include <cwchar>
#include <vector>
#include <map>

namespace Huffman {

    void ler_arquivo() {
        std::wstring filename;

        std::wcout << L"Digite o nome do arquivo que queira compactar: ";
        std::getline(std::wcin, filename);

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

        for(const auto& c : frequencia){
            std::wcout << L"Caractere: " << c.first << L" - Frequência: " << c.second << std::endl;
        }
    
        std:: cout << std::endl;

        arq.close();
    }
}
