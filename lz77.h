//
// Created by Maria Manakhova on 05.04.2020.
//

#ifndef KDZ_LZ77_H
#define KDZ_LZ77_H

#include <iostream>
#include <vector>
#include <fstream>
#include "iarchiver.h"
#include "utils.h"

using std::string;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::ios;
using std::min;
using std::to_string;

/**
 * Класс архиватора с использованием алгоритма Хаффмана
 */
class LZ77 : public IArchiver {
private:
    /**
     * Класс троек
     */
    class Triplet {
    private:
        /**
         * Смещение относительно начала буфера предыстории (словаря)
         */
        int offset;
        /**
         * Длина совпадения
         */
        int length;
        /**
         * Первый символ буфера предпросмотра после найденного фрагмента
         */
        char value;

        Triplet() {};

    public:
        int getOffset();

        int getLength();

        char getValue();

        Triplet(int offset, int length, char value) : offset(offset), length(length), value(value) {};
    };

    /**
     * Байтовое представление файла
     */
    string buffer;
    /**
     * Максимальный размер словаря
     */
    int historyBufferSize;
    /**
     * Максимальный размер буфера предпросмотра
     */
    int previewBufferSize;
    /**
     * Коды-тройки
     */
    vector<Triplet> triplets;

    /**
     * Метод для очищения всех контейнеров-таблиц и буфера файла
     */
    void deleteData();

    /**
     * Открывает и загружает в буфер файл для архивирования
     * @param path путь к файлу
     */
    void openPackingFile(string &path);

    /**
     * Метод для поиска максимально подстроки из буфера предпросмотра в словаре и буфере предпросмотра
     * @param historyBuffer словарь
     * @param previewBuffer буфер предпросмотра (скользящее окно)
     * @return
     */
    static Triplet findMaximumSubstring(string &historyBuffer, string &previewBuffer);

    /**
     * Метод для кодирования архивируемого файла алгоритмом LZ77
     * @param out поток для записи данных в файл с расширением .lz7705, .lz7710 или .lz7720 в зависимости
     *        от размера окна предпросмотра
     */
    void encode();

    /**
     * Метод для записи раскодированного буфера или кодов-троек в выходной файл
     * @param path путь к файлу
     * @param isUnpacking метод используется для упаковки или распаковки
     */
    void createOutputFile(string &path, bool isUnpacking);

    /**
     * Метод для считывания кодов-троек из файла в список кодов
     * @param path путь к файлу
     */
    void openUnpackingFile(string &path);

    /**
     * Метод для декодирования в буфер разархивируемого файла алгоритмом LZ77
     */
    void decode();

    LZ77() {};

public:
    LZ77(int windowBufferSize, int historyBufferSize) :
            historyBufferSize(historyBufferSize * 1024), previewBufferSize(windowBufferSize * 1024) {};

    /**
     * Метод для получения расширения упакованного файла в зависимости от размера окна предпросмотра
     * @return
     */
    string getExtension();

    /**
     * Метод, в котором вызываются все методы, необхлдимые для упаковки файла алгоритмом LZ77
     * @param path путь к файлу
     */
    void pack(string &path);

    /**
     * Метод, в котором вызываются все методы, необхлдимые для распаковки файла алгоритмом LZ77
     * @param path путь к файлу
     */
    void unpack(string &path);
};

#endif //KDZ_LZ77_H
