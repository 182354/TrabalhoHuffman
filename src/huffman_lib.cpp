#include <iostream>
#include <string>
#include <fstream>
#include <cwchar>
#include <vector>
#include <map>
#include <algorithm>

namespace Huffman{
    

    std::map<wchar_t, int> ler_arquivo(std::wstring &filename){
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
        return frequencia;
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
        file.close();
        return fileSize;
    }

    struct node {
        wchar_t value;
        int freq;
        node* left, *right;
    };

    node *criar_nodo(const wchar_t c, int freq){
        node *pointer = new node;
        pointer->value = c;
        pointer->freq = freq;
        pointer->left = nullptr;
        pointer->right = nullptr;
        return pointer;
    }

    node* criar_arvore(const std::map<wchar_t, int>& frequencia){
        std::vector<node*> nodos;
        
        for(auto it = frequencia.begin(); it != frequencia.end(); it++){
            wchar_t c = it->first;
            int freq = it->second;

            node *nodo = criar_nodo(c, freq);
            nodos.push_back(nodo);
        }

        while(nodos.size() > 1){
            std::sort(nodos.begin(), nodos.end(), [](node* a, node* b){
                return a->freq < b->freq;
            });

            node* esquerda = nodos[0];
            node* direita = nodos[1];

            node* pai = criar_nodo(L'\0', esquerda->freq + direita->freq);
            pai->left = esquerda;
            pai->right = direita;

            nodos.erase(nodos.begin(), nodos.begin() + 2);
            nodos.push_back(pai);
            }
            return nodos[0];    
    }

    void show(node *root, int level = 0, const std::string &prefix = "Root: ") {
        if (!root) return;

        std::string ident(level * 4, ' ');

        std::cout << ident << prefix << root->value << std::endl;
        show(root->left, level + 1, "Left: ");
        show(root->right, level + 1, "Right: ");
    } 
}
