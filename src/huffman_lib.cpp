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
    unordered_map<wchar_t, int> freq;
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