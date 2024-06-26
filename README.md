# Árvore Huffman
No mundo da compressão de dados, a codificação de Huffman se destaca como um algoritmo criado por David A. Huffman em 1952. Este método atribui códigos binários mais curtos aos símbolos que aparecem com mais frequência e códigos binários mais longos aos símbolos menos frequentes. 

Essa estratégia permite reduzir o tamanho geral do arquivo, otimizando o espaço de armazenamento e a transmissão de dados. A codificação de Huffman é utilizada para o processo de compressão de dados em diversas aplicações como zip, jpeg, png, mp3 entre outros.

## Sobre
Este é um software em desenvolvido em C++ que constrói árvores de Huffmann a partir de arquivos de texto.

* Leitura e análise de arquivos de texto: Extração da frequência de cada símbolo (caractere) no arquivo de texto. O programa aceita arquivos Unicode em vez de ASCII (utilizando wifstream, wstring e wchar_t).

* Construção de uma árvore de Huffman: As frequências dos símbolos serão inseridas em uma árvore binária onde, cada nó representa um símbolo e sua frequência.

* Tabela de codificação: Códigos binários únicos serão atribuidos para cada símbolo com base na estrutura da árvore.

* Exibição da árvore e da tabela: O resultado do processamento do arquivo será em uma interface ----

* Exibição do tamanho do arquivo original, o tamanho resultante da compactação e a diferença entre ambos (valores absoluto e percentual).

## Extensões Utilizadas no Windows 

* C/C++ Compile Run -- Autor -- danielPinto8zz6

* No windows Fazer a instalacao tdm-gcc https://jmeubank.github.io/tdm-gcc/download/

* Para vizualizar a Arvore gerada utilizar a extensão Graphviz Interactive Preview -- Autor -- tintinWeb

## Funcionamento

* O programa funciona da seguite maneira.

* O usuario devera selecionar o arquivo txt que deseja compactar.

* Caso encontrado, o programa ira realizar compreensão, trazendo os dados no arquivo resultado.txt e tambem ira realizar a montagem da árvore no arquivo arvore.dot.

* A arvore podera ser visualizada utilizando a extesão posteriormente baixada.

## Pontos Importantes na Execucao

* Para execucao utilizar o terminal -- Segue a ordem dos comandos:

* "g++ main.cpp -o main"

* "./main.exe"

## Autores

 * [Guilherme S. Machado](https://github.com/guilhermesvm)
 * [Luiz Henrique Frandoloso](https://github.com/182354)
