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
std::string to_utf8(const std::wstring& wstr) {
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
void encode(Node *root, std::wstring code, std::unordered_map<wchar_t, std::wstring> &huffmanCodes) {
    if (!root) return;

    // Nodo folha: armazenar código no mapa
    if (!root->left && !root->right) {
        huffmanCodes[root->c] = code;
    }

    encode(root->left, code + L'0', huffmanCodes);
    encode(root->right, code + L'1', huffmanCodes);
}

void export_to_dot(const Node* root, const std::string& filename, const std::unordered_map<wchar_t, std::wstring> &huffmanCodes) {
    std::ofstream dotFile(filename);
    dotFile << "digraph G {\n";

    std::queue<const Node*> nodeQueue;
    nodeQueue.push(root);

    while (!nodeQueue.empty()) {
        const Node* currentNode = nodeQueue.front();
        nodeQueue.pop();

        std::string nodeName = "Node" + std::to_string(reinterpret_cast<uintptr_t>(currentNode));
        std::string label;

        bool isInternalNode = false;

        if (currentNode->c == L'\0') {
            label = std::to_string(currentNode->freq);
            isInternalNode = true;
        } else {
            std::string valueStr;
            if (currentNode->c == L' ') valueStr = "SPACE";
            else if (currentNode->c == L'\n') valueStr = "NEWLINE";
            else if (currentNode->c == L'"') valueStr = "QUOTE";
            else if (currentNode->c == L'>') valueStr = "GREATER_THAN";
            else if (currentNode->c == L'<') valueStr = "LESS_THAN";
            else if (currentNode->c == L'{') valueStr = "OPEN_BRACE";
            else if (currentNode->c == L'}') valueStr = "CLOSE_BRACE";
            else if (currentNode->c == L'|') valueStr = "PIPE";
            else valueStr = to_utf8(std::wstring(1, currentNode->c));

            std::string binaryCode = to_utf8(huffmanCodes.at(currentNode->c));
            label = "{{'" + valueStr + "'|" + std::to_string(currentNode->freq) + "}|" + binaryCode + "}";
        }
        
        dotFile << "\t" << nodeName << (isInternalNode ? " [label=\"" : " [shape=record, label=\"") << label << "\"];\n";

        if (currentNode->left) {
            std::string leftNodeName = "Node" + pointer_to_string(currentNode->left);
            dotFile << "\t" << nodeName << " -> " << leftNodeName << " [label=\"0\"];\n";
            nodeQueue.push(currentNode->left);
        }
        if (currentNode->right) {
            std::string rightNodeName = "Node" + pointer_to_string(currentNode->right);
            dotFile << "\t" << nodeName << " -> " << rightNodeName << " [label=\"1\"];\n";
            nodeQueue.push(currentNode->right);
        }
    }
    dotFile << "}\n";
}

// Função para desenhar a árvore de Huffman usando o Graphviz
void draw_tree(const Node* root, const std::unordered_map<wchar_t, std::wstring>& huffmanCodes) {
    std::string dotFilename = "../output/arvore.dot";
    export_to_dot(root, dotFilename, huffmanCodes);
}

// Função para liberar a memória da árvore
void free_tree(Node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    delete root;
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

    Node* root = create_tree(freq);
    std::unordered_map<wchar_t, std::wstring> huffmanCodes;
    encode(root, L"", huffmanCodes);

    outputFile << L"\nCódigos binários gerados pela árvore de Huffman:\n";
    for (const auto &it : huffmanCodes) {
        if (it.first == L' ') outputFile << L"ESPAÇO: " << it.second << std::endl;
        else if (it.first == L'\n') outputFile << L"\\n: " << it.second << std::endl;
        else outputFile << it.first << L": " << it.second << std::endl;
    }

    // Calcular a taxa de compressão
    inputFile.clear();
    inputFile.seekg(0, std::ios::end);
    int originalSize = inputFile.tellg();
    int compressedSize = 0;
    for (const auto &it : freq) {
        compressedSize += it.second * huffmanCodes[it.first].length();
    }
    compressedSize = (compressedSize + 7) / 8;

    double compressionRatio = ((double)(originalSize - compressedSize) / originalSize) * 100;

    outputFile << L"\nTamanho original: " << originalSize << L" bytes" << std::endl;
    outputFile << L"Tamanho compactado: " << compressedSize << L" bytes" << std::endl;
    outputFile << L"Redução: " << compressionRatio << L"%\n";

    draw_tree(root, huffmanCodes);
    free_tree(root);
}

