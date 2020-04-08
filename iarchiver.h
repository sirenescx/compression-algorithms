//
// Created by Maria Manakhova on 05.04.2020.
//

#ifndef KDZ_IARCHIVER_H
#define KDZ_IARCHIVER_H

#include <string>
#include <fstream>

using std::string;
using std::ofstream;

/**
 * Интерфейс архиватора
 */
class IArchiver {
public:
    /**
     * Метод для упаковки файла
     * @param path путь к файлу
     */
    virtual void pack(string &path) = 0;

    /**
     * Метод для распаковки файла
     * @param path путь к файлу
     */
    virtual void unpack(string &path) = 0;

    /**
     * Метод для получения расширения архивированного файла
     * @return строку с расширением
     */
    virtual string getExtension() = 0;

private:
    /**
     * Метод для открытия и считывания архивируемого файла
     * @param path путь к файлу
     */
    virtual void openPackingFile(string &path) = 0;

    /**
     * Метод для открытия и считывания разархивируемого файла
     * @param path путь к файлу
     */
    virtual void openUnpackingFile(string& path) = 0;

    /**
     * Метод для создания выходного файла
     * @param path
     * @param isUnpacking имеет значение true, если файл распаковывается, false – если упаковывается
     *        параметр не используется в классе Huffman, так как там этот метод нужен только для упаковки
     */
    virtual void createOutputFile(string& path, bool isUnpacking) = 0;
};

#endif //KDZ_IARCHIVER_H
