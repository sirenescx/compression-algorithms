//
// Created by Maria Manakhova on 05.04.2020.
//

#ifndef KDZ_HUFFMAN_H
#define KDZ_HUFFMAN_H

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <string>
#include "utils.h"
#include "iarchiver.h"

using std::vector;
using std::pair;
using std::swap;
using std::string;
using std::ifstream;
using std::ios;
using std::ofstream;
using std::map;
using std::sort;

/**
 * Класс архиватора с использованием алгоритма Хаффмана
 */
class Huffman : public IArchiver {
private:
    class Node {
    private:
        int frequency;
        char value;
        Node *left;
        Node *right;

        Node(Node *first, Node *second);

    public:
        ~Node();

        Node(int frequency, char value);

        char getValue();

        int getFrequency();

        Node *getLeft();

        Node *getRight();

        /**
         * Метод для объединения двух вершин в одну
         * @param first
         * @param second
         * @return вершину, частота встречаемости которой – сумма частот двух объединяемых вершин
         */
        static Node *join(Node *first, Node *second);
    };

    /**
     * Дерево частот
     */
    vector<Node*> tree;
    /**
     * Таблица кодов
     */
    map<char, string> codes;
    /**
     * Байтовое представление файла
     */
    vector<unsigned char> buffer;
    /**
     * Количество уникальных символов в файле
     */
    int size;
    /**
     * Число неиспользуемых битов
     */
    int unusedBits;
    /**
     * Расширение файла при архивировании
     */
    string extension = ".haff";

    /**
     * Метод для очищения всех контейнеров-таблиц и буфера файла
     */
    void deleteData();

    /**
     * Метод для поиска кода для символа в таблице
     * @param value значение символа
     * @return пустую строку, если символ не найден в таблице, иначе код символа
     */
    string getCode(char value);

    /**
     * Метод для поиска символа по коду в таблице
     * @param code значение кода
     * @param wasFound был ли найден такой код в таблице
     * @return символ, если такой код был найден в таблице и ' ', если не найден
     *         вообще говоря, метод мог бы возвращать любой символ, так как если wasFound имеет значение
     *         false, значение символа далее никак не используется
     */
    char getChar(string &code, bool &wasFound);

    /**
     * Открывает и загружает в буфер файл для архивирования
     * @param path путь к файлу
     */
    void openPackingFile(string &path);

    /**
     * Метод для сравнения двух пар из таблицы частот по частотам
     * @param a
     * @param b
     * @return a.frequency > b.frequency
     */
    static bool frequencyComparator(pair<char, int> &a, pair<char, int> &b);

    /**
     * Метод для построения таблицы частот
     */
    void buildFrequencyTable();

    /**
     * Метод для сравнения двух вершин по частотам
     * @param first
     * @param second
     * @return first.frequency > second.frequency
     */
    static bool nodesComparator(Node *first, Node *second);

    /**
     * Метод для построения кодов Хаффмана по дереву зависимости частот
     * @param root корень дерева
     * @param code строка с кодом
     */
    void buildCodes(Node *root, const string& code);

    /**
     * Метод для построения дерева зависимости частот символов
     */
    void buildTree();

    /**
     * Метод для построения таблицы кодов
     */
    void buildCodeTable();

    /**
     * Метод для кодирования архивируемого файла алгоритмом Хаффмана
     * @param out поток для записи данных в файл с расширением .haff
     */
    void encode(ofstream &out);

    /**
     * Метод, в котором в выходной файл записывается таблица частот,
     * строится таблица кодов и кодируется архивируемый файл
     * @param path путь к файлу
     * @param isUnpacking всегда false, так как в этом классе метод используется только при упаковке
     */
    void createOutputFile(string& path, bool isUnpacking = false);

    /**
     * Метод для считывания дерева кодов и информации в файле в буфер
     * @param path путь к файлу
     */
    void openUnpackingFile(string& path);

    /**
     * Метод для распаковки архивированного файла
     * @param path путь к файлу
     */
    void decode(string& path);

public:
    Huffman() {}

    ~Huffman();

    /**
     * Метод для получения расширения упакованного файла
     * @return
     */
    string getExtension();

    /**
     * Метод, в котором вызываются все методы, необхлдимые для упаковки файла алгоритмом Хаффмана
     * @param path путь к файлу
     */
    void pack(string& path);

    /**
     * Метод, в котором вызываются все методы, необхлдимые для распаковки файла алгоритмом Хаффмана
     * @param path путь к файлу
     */
    void unpack(string& path);
};

#endif //KDZ_HUFFMAN_H
