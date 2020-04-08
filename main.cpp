// КДЗ по дисциплине Алгоритмы и структуры данных, 2019-2020 уч.год
// Манахова Мария Сергеевна, группа БПИ-184, дата (06.04.2020)
// Среда разработки: CLion
// Состав проекта: main.cpp, huffman.h, huffman.cpp, lz77.h, lz77.cpp, iarchiver.h, utils.h
// Что сделано:
//  сжатие и распаковка методом Хаффмана,
//  сжатие и распаковка методом LZ77
//  проведен вычислительный эксперимент
//  построены таблицы c коэффициентами сжатия файлов и временем упаковки и распаковки файлов,
//  построены графики, отражающие коэффициент сжатия каждого файла для каждого алгоритма, время упаковки каждого файла
//  для каждого алгоритма, время распаковки каждого файла для каждого алгоритма
//  для измерения времени выполнения использовалось chrono,
//  оформлен отчет
// Что не сделано:
//  не построена таблица частоты появления символов в файле
//  не построен график, отражающий распределения частот встречаемости символов

#include <iostream>
#include "huffman.h"
#include "lz77.h"
#include <chrono>
#include <filesystem>
#include <set>

namespace fs = std::filesystem;

using std::chrono::system_clock;
using std::chrono::duration;
using std::set;
using fs::file_size;

// Директория с исходными файлами
const string fileDirectory = "cmake-build-release/DATA";
// Директория с файлом результатов
const string resultsPath = "cmake-build-release/DATA/results/results.csv";
// Заголовок таблицы результатов
const string csvHeader = "filename;entropy;;huffman;;;lz77 (5, 4);;;lz77 (10, 8);;;lz77(20, 10);;;;";
// Подзаголовок таблицы результатов
const string csvSubheader = ";;compression;packing time;unpacking time;compression;packing time;unpacking time;"
                            "compression;packing time;unpacking time;compression;packing time;unpacking time;";
// Список тестируемых файлов
set<string> testingFiles = { "1.txt",
                             "2.docx",
                             "3.pptx",
                             "4.pdf",
                             "5.exe",
                             "6.jpg",
                             "7.jpg",
                             "8.bmp",
                             "9.bmp",
                             "10.avi"
};

int main() {
    // Алгоритмы архивирования и разархивирования
    IArchiver *algorithms[4] = {new Huffman(),
                                new LZ77(5, 4),
                                new LZ77(10, 8),
                                new LZ77(20, 10)};

    string path = "cmake-build-release/DATA/1.txt";
    Huffman *huffman = new Huffman();
    huffman->pack(path);
    huffman->unpack(path);

//
//    // Поток для вывода результатов в CSV-файл
//    ofstream resultsStream;
//    resultsStream.open(resultsPath);
//    resultsStream << csvHeader << '\n';
//    resultsStream << csvSubheader << '\n';
//
//    //  Проход по всем тестируемым файлам в директории
//    for (const auto &entry : fs::directory_iterator(fileDirectory)) {
//        string path = entry.path();
//        if (testingFiles.find(getFileName(path)) == testingFiles.end()) {
//            continue;
//        }
//
//        // Вычисление размера исходного файла
//        double fileSize = file_size(path);
//        string tableLine = createTableLine(path);
//
//        // Архивирование и разархивирование файла каждым из алгоритмов
//        for (auto &algorithm : algorithms) {
//            auto start = system_clock::now();
//            algorithm->pack(path);
//            auto end = system_clock::now();
//            duration<double> packingTime = end - start;
//            // Вычисление коэффициента сжатия файла при упаковке
//            double compression = findCompression(fileSize, path, algorithm->getExtension());
//
//            start = system_clock::now();
//            algorithm->unpack(path);
//            end = system_clock::now();
//            duration<double> unpackingTime = end - start;
//
//            addToTableLine(tableLine, compression, packingTime.count(), unpackingTime.count());
//        }
//
//        resultsStream << tableLine << '\n';
//    }
//
//    resultsStream.close();

    return 0;
}
