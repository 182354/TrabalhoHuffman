#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>
#include <vector> 
#include <fstream>
#include <codecvt>
#include <locale>
#include <sstream>

// Estrutura que representa um nodo na árvore de Huffman  
struct Node {
    wchar_t c;
    int freq;
    Node *left, *right;
};

// Função de comparação para a fila de prioridade 
struct CompareNodes {
    bool operator()(Node* left, Node* right) {
        return left->freq > right->freq;
    }
};

// Função para contar a frequência de cada caractere
std::unordered_map<wchar_t, int> count_frequency(std::wifstream &inputFile) {
    std::unordered_map<wchar_t, int> freq;
    wchar_t c;
    while (inputFile.get(c)) {
        freq[c]++;
    }
    return freq;
}

// Função para criar um nodo na memória
Node *create_node(const wchar_t c, int freq, Node *left, Node *right) {
    Node *pointer = new Node;
    pointer->c = c;
    pointer->freq = freq;
    pointer->left = left;
    pointer->right = right;
    return pointer;
}

// Função para converter ponteiro em string para identificação única dos nodo
std::string pointer_to_string(const void* ptr) {
    std::stringstream ss;
    ss << reinterpret_cast<uintptr_t>(ptr);
    return ss.str();
}

// Função para converter uma string wide (unicode) para UTF-8
std::string to_uft8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

// Função para criar a árvore de Huffman
Node* create_tree(const std::unordered_map<wchar_t, int>& freq) {
    std::priority_queue<Node*, std::vector<Node*>, CompareNodes> priorityQueue;
    for (const auto &it : freq) {
        priorityQueue.push(create_node(it.first, it.second, nullptr, nullptr));
    }

    while (priorityQueue.size() != 1) {
        Node *left = priorityQueue.top();
        priorityQueue.pop();
        Node *right = priorityQueue.top();
        priorityQueue.pop();

        int sumFrequency = left->freq + right->freq;
        priorityQueue.push(create_node(L'\0', sumFrequency, left, right));
    }

    return priorityQueue.top();
}


// Função para percorrer a árvore de Huffman e gerar os códigos binários
void encode(Node *root, std::wstring code, unordered_map<wchar_t, std::wstring> &huffmanCodes) {
    if (!root) return;

    // Nodo folha: armazenar código no mapa
    if (!root->left && !root->right) {
        huffmanCodes[root->c] = code;
    }

    encode(root->left, code + L'0', huffmanCodes);
    encode(root->right, code + L'1', huffmanCodes);
}

// Função principal para construir a árvore de Huffman, gerar frequência de caracteres e tabela de codificaçao
void build_tree_n_table(std::wifstream &inputFile, std::wofstream &outputFile) {
    if (!inputFile) return;

    std::unordered_map<wchar_t, int> freq = count_frequency(inputFile);

    outputFile << L"Frequência de caracteres:\n";
    for (const auto &it : freq) {
        if (it.first == L' ') outputFile << L"ESPAÇO: " << it.second << std::endl;
        else if (it.first == L'\n') outputFile << L"\\n: " << it.second << std::endl;
        else outputFile << it.first << L": " << it.second << std::endl;
    }

    //To do
}