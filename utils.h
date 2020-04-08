//
// Created by Maria Manakhova on 05.04.2020.
//
#ifndef KDZ_UTILS_H
#define KDZ_UTILS_H

#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <cmath>
#include <filesystem>

namespace fs = std::filesystem;

using std::string;
using std::map;
using std::ifstream;
using std::ios;
using std::vector;
using std::pair;
using fs::file_size;
using std::to_string;

/**
 * Метод, обрезающий расширение файла
 * @param filePath путь к файлу
 */
static void trimExtension(string &filePath) {
    string separator(".");
    int lastIndex = filePath.rfind(separator);
    filePath = filePath.substr(0, lastIndex);
}

/**
 * Метод для считывания файла
 * @param path путь к файлу
 * @param buffer битовое представление файла
 */
static void readFile(string &path, vector<unsigned char> &buffer) {
    ifstream file(path, ios::in | ios::binary);

    file.seekg(0, ios::end);
    long long fileSize = file.tellg();
    file.seekg(0, ios::beg);

    buffer.resize((unsigned long long) fileSize);
    file.read((char *) (&buffer[0]), fileSize);

    file.close();
}

/**
 * Подсчитывает частоты встречаемости символов в файле
 * @param buffer битовое представление файла
 * @param numberOfSymbols общее число символов в файле
 * @return таблицу символ-частота встречаемости
 */
static map<char, int> countFrequency(vector<unsigned char> &buffer, int &numberOfSymbols) {
    map<char, int> frequencyTable;

    for (unsigned char & byte : buffer) {
        ++numberOfSymbols;
        auto it = frequencyTable.find(byte);
        if (it != frequencyTable.end()) {
            ++it->second;
        } else {
            frequencyTable.emplace_hint(frequencyTable.end(), byte, 1);
        }
    }

    buffer.clear();

    return frequencyTable;
}

/**
 * Метод для вычисления энтропии файла
 * @param path путь к файлу
 * @return энтропию файла
 */
static double calculateEntropy(string &path) {
    vector<unsigned char> buffer;
    readFile(path, buffer);
    int numberOfSymbols = 0;
    map<char, int> frequencyTable = countFrequency(buffer, numberOfSymbols);

    double entropy = 0.0;
    for (pair<char, int> p : frequencyTable) {
        if (p.second != 0) {
            double frequency = (double) p.second / numberOfSymbols;
            entropy += (-1) * frequency * log2(frequency);
        }
    }

    return entropy;
}

/**
 * Метод для получения имени файла
 * @param path
 * @return
 */
static string getFileName(const string& path) {
    string separator("/");
    int lastIndex = path.rfind(separator);
    return path.substr(lastIndex + 1, path.size() - 1);
}

/**
 * Метод для получения коэффициента сжатия файла
 * @param sourceFileSize исходный размер файла
 * @param path путь к файлу
 * @param extension расширение упакованного файла
 * @return
 */
static double findCompression(double sourceFileSize, const string& path, const string& extension) {
    double compressedFileSize = file_size(path + extension);
    return compressedFileSize / sourceFileSize;
}

/**
 * Метод для создания в таблице строки, содержащей информацию об имени файла и его энтропии
 * @param path
 * @return
 */
static string createTableLine(string path) {
    return getFileName(path) + ";" + to_string(calculateEntropy(path)) + ";";
}

/**
 * Метод для добавления к строке таблице информации о коэффициенте сжатия файла, времени его упаковки и распаковки
 * @param tableLine строка, к которой необходимо добавить информацию
 * @param compression коэффицент сжатия
 * @param pTime время упаковки
 * @param uTime время распаковки
 */
static void addToTableLine(string &tableLine, double compression, double pTime, double uTime) {
    tableLine += to_string(compression) + ";" + to_string(pTime) + ";" + to_string(uTime) + ";";
}

/**
 * Метод для чтения числа из файла
 * @param istream поток входных данных
 * @param value
 */
static void inInt(std::istream &istream, int &value) {
    const size_t nBytes = 4;
    char bytes[nBytes];
    for (char & byte : bytes) {
        istream.get(byte);
    }

    value = *static_cast<int*>(static_cast<void*>(bytes));
}

/**
 * Метод для вывода числа в файл
 * @param ostream поток выходных данных
 * @param value
 */
static void outInt(std::ostream &ostream, int value) {
    ostream.write(static_cast<char*>(static_cast<void*>(&value)), sizeof(int));
}

#endif //KDZ_UTILS_H
