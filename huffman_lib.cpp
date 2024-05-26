#include <iostream>
#include <string>
#include <fstream>

namespace Huffman{

    void ler_arquivo_w(){
        std::wstring filename;

        std::wcout << L"Digite o nome do arquivo que queira compactar: ";
        //std::getline(std::wcin, filename);
        std::wcin >> filename;

        std::wifstream arq;
        arq.open(filename.c_str());

        if (!arq){
            std:: cout << std::endl;
            std::wcout << L"Could not open.\n";
            std:: cout << std::endl;
            return;
        }

        std::wstring line;
        std:: cout << std::endl;

        while(getline(arq, line)){
            std:: wcout<< line << std::endl;
        }

        arq.close();
    }
}