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
string pointer_to_string(const void* ptr) {
    stringstream ss;
    ss << reinterpret_cast<uintptr_t>(ptr);
    return ss.str();
}

// Função para converter uma string wide (unicode) para UTF-8
string to_uft8(const wstring& wstr) {
    wstring_convert<codecvt_utf8<wchar_t>> converter;
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