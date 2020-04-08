//
// Created by Maria Manakhova on 05.04.2020.
//

#include "huffman.h"

Huffman::Node::Node(Node *first, Node *second) {
    this->frequency = first->frequency + second->frequency;
    value = '\0';
    left = first;
    right = second;
}

Huffman::Node::~Node() {
    delete left;
    delete right;
}

Huffman::Node::Node(int frequency, char value) {
    this->frequency = frequency;
    this->value = value;
    left = nullptr;
    right = nullptr;
}

char Huffman::Node::getValue() {
    return value;
}

int Huffman::Node::getFrequency() {
    return frequency;
}

Huffman::Node *Huffman::Node::getLeft() {
    return left;
}

Huffman::Node *Huffman::Node::getRight() {
    return right;
}

Huffman::Node *Huffman::Node::join(Node *first, Node *second) {
    return new Node(first, second);
}

void Huffman::deleteData() {
    for (int i = 0; i < tree.size(); ++i) {
        delete tree[0];
    }

    tree.clear();
    codes.clear();
    buffer.clear();
}

string Huffman::getCode(char value) {
    return codes.find(value) == codes.end() ? "" : codes[value];
}

char Huffman::getChar(string &code, bool &wasFound) {
    for (const auto& p : codes) {
        if (p.second == code) {
            wasFound = true;
            return p.first;
        }
    }

    wasFound = false;
    return ' ';
}

void Huffman::openPackingFile(string &path) {
    ifstream file(path, ios::in | ios::binary);

    // Получение размера файла
    file.seekg(0, ios::end);
    long long fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Изменения размера буфера под размер файла
    buffer.resize((unsigned long long) fileSize);
    // Считывание файла в буфер
    file.read((char *) (&buffer[0]), fileSize);

    file.close();
}

bool Huffman::frequencyComparator(pair<char, int> &a, pair<char, int> &b) {
    return a.second > b.second;
}

void Huffman::buildFrequencyTable() {
    // Построение таблицы соответствия символов файла и частоты их встречаемости
    map<char, int> frequencyTable;

    for (unsigned char & byte : buffer) {
        auto it = frequencyTable.find(byte);
        if (it != frequencyTable.end()) {
            ++it->second;
        } else {
            frequencyTable.emplace_hint(frequencyTable.end(), byte, 1);
        }
    }

    vector<pair<char, int>> sortedFrequencyTable;

    for (auto item : frequencyTable) {
        sortedFrequencyTable.emplace_back(item);
    }

    // Задание числа уникальных символов в файле
    size = (int) sortedFrequencyTable.size();

    // Сортировка таблицы частот
    sort(sortedFrequencyTable.begin(), sortedFrequencyTable.end(), frequencyComparator);

    for (auto item : sortedFrequencyTable) {
        tree.emplace_back(new Node(item.second, item.first));
    }
}

bool Huffman::nodesComparator(Huffman::Node *first, Huffman::Node *second) {
    return first->getFrequency() > second->getFrequency();
}

void Huffman::buildTree() {
    while (tree.size() != 1) {
        // Сортировка вершин, для того, чтобы в конце всегда оставались вершины с минимальной частотой
        sort(tree.begin(), tree.end(), nodesComparator);

        Node *left = tree.back();
        tree.pop_back();
        Node *right = tree.back();
        tree.pop_back();

        Node *parent = Node::join(left, right);
        tree.push_back(parent);
    }
}

void Huffman::buildCodes(Node *root, const string& code) {
    if (root->getLeft() != nullptr) {
        buildCodes(root->getLeft(), code + '0');
    }

    if (root->getRight() != nullptr) {
        buildCodes(root->getRight(), code + '1');
    }

    if (root->getLeft() == nullptr && root->getRight() == nullptr) {
        codes.emplace(pair<char, string>(root->getValue(), code));
    }
}

void Huffman::buildCodeTable() {
    buildTree();

    string code;
    buildCodes(tree[0], code);
}

void Huffman::encode(ofstream &out) {
    int bitsCount = 0;
    char value = ' ';

    // Кодирование информации в файле с помощью таблицы кодов
    for (auto byte: buffer) {
        for (auto bit: getCode(byte)) {
            if (bitsCount == 8) {
                out << value;
                bitsCount = 0;
            }

            if (bit == '0') {
                value &= ~(1 << bitsCount);
            } else if (bit == '1') {
                value |= 1 << bitsCount;
            }

            ++bitsCount;
        }
    }

    // Подсчет количества неиспользованных битов последнего байта файла
    int count = 0;
    while (bitsCount != 8) {
        value |= 1 << bitsCount;
        ++bitsCount;
        ++count;
    }

    out << value;
    out << count;
}

void Huffman::createOutputFile(string &path, bool isUnpacking) {
    trimExtension(path);
    ofstream out(path + extension, ios::out | ios::binary);

    // Запись в упакованный файл числа уникальных символов и таблицы частот
    outInt(out, size);
    for (int i = 0; i < size; ++i) {
        out << tree[i]->getValue();
        outInt(out, tree[i]->getFrequency());
    }

    // Построение таблицы кодов и кодирование информации в архивированном файле с ее помощью
    buildCodeTable();
    encode(out);

    out.close();
}

void Huffman::openUnpackingFile(string &path) {
    trimExtension(path);
    path += extension;
    ifstream file(path, ios::in | ios::binary);

    file.seekg(0, ios::end);
    long long fileSize = file.tellg();
    file.seekg(0, ios::beg);

    int frequencyTableSize;
    inInt(file, frequencyTableSize);

    for (int i = 0; i < frequencyTableSize; ++i) {
        int frequency;
        char value;
        file.get(value);
        inInt(file, frequency);
        tree.emplace_back(new Node(frequency, value));
    }

    fileSize = fileSize - file.tellg() - 1;

    buffer.resize((unsigned long long) fileSize);
    file.read((char *) (&buffer[0]), fileSize);

    file >> unusedBits;

    file.close();
}

void Huffman::decode(string &path) {
    ofstream out(path.insert(path.size() - 4, "un"), ios::out | ios::binary);

    int position = 0;
    int length = (int) buffer.size() * 8 - unusedBits;

    string code;

    while (position < length) {
        int bit = position % 8;
        int currentByte = buffer[position / 8];
        code += bool((1 << bit) & currentByte) ? '1' : '0';
        // Если такой код был найден в таблице кодов, вывести в файл значение, соответствующее этому коду
        bool wasFound = false;
        char value = getChar(code, wasFound);
        if (wasFound) {
            out << value;
            code = "";
        }

        ++position;
    }

    out.close();
}

Huffman::~Huffman() {
    for (int i = 0; i < tree.size(); ++i) {
        delete tree[0];
    }
}

string Huffman::getExtension() {
    return ".haff";
}

void Huffman::pack(string &path) {
    deleteData();
    openPackingFile(path);
    buildFrequencyTable();
    createOutputFile(path);
}

void Huffman::unpack(string &path) {
    deleteData();
    openUnpackingFile(path);
    buildCodeTable();
    decode(path);
}
