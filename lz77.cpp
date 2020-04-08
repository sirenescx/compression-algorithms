//
// Created by Maria Manakhova on 05.04.2020.
//

#include "lz77.h"

int LZ77::Triplet::getOffset() {
    return offset;
}

int LZ77::Triplet::getLength() {
    return length;
}

char LZ77::Triplet::getValue() {
    return value;
}

void LZ77::deleteData() {
    triplets.clear();
    buffer.clear();
}

void LZ77::openPackingFile(string &path) {
    ifstream file(path, ios::in | ios::binary);

    file.seekg(0, ios::end);
    long long fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Считывание всего файла в буфер
    buffer.resize((unsigned long long) fileSize);
    file.read((&buffer[0]), fileSize);

    file.close();
}

LZ77::Triplet LZ77::findMaximumSubstring(string &historyBuffer, string &previewBuffer) {
    // Единственная возможная код-тройка для вставки при пустом буфере предыстории
    Triplet t(0, 0, previewBuffer[0]);

    // -1 так как после вышепроизведенного взятия тройке, в окне предпросмотра находится один символ
    size_t previewBufferLength = previewBuffer.length() - 1;
    size_t historyBufferLength = historyBuffer.length();

    // Проход по всем возможным подстрокам окна предпросмотра
    for (int i = 1; i <= min(previewBufferLength, historyBufferLength); ++i) {
        string s = previewBuffer.substr(0, i);
        // Поиск подстроки в словаре
        int index = historyBuffer.find(s);
        if (index == -1) {
            break;
        }

        if (s.substr(i) == historyBuffer.substr(historyBufferLength - i, i) &&
            previewBuffer[0] == previewBuffer[i]) {
            index = historyBufferLength - i;
        }

        // Подсчет количества повторений символов
        int repeats = 0;
        if (index + i == historyBufferLength) {
            while (previewBufferLength >= repeats + 2 * i &&
                   s.substr(i) == previewBuffer.substr(i + repeats, i)) {
                repeats += i;
            }

            // Подсчет количества повторов строки
            int sRepeats = i - 1;
            while (sRepeats > 0) {
                if (i + repeats + sRepeats <= previewBufferLength &&
                    s.substr(sRepeats) == previewBuffer.substr(i + repeats, sRepeats)) {
                    break;
                }
                --sRepeats;
            }

            repeats += sRepeats;
        }

        // Если длина повторения увеличилась, изменяем код-тройку
        if (t.getLength() <= i + repeats) {
            t = Triplet(historyBufferLength - index, i + repeats, previewBuffer[i + repeats]);
        }
    }

    return t;
}

void LZ77::encode() {
    string historyBuffer;
    string previewBuffer;

    while (true) {
        if ((previewBuffer.length() < previewBufferSize) && (buffer.length() != 0)) {
            int length = previewBufferSize - previewBuffer.length();
            previewBuffer.append(buffer, 0, length);
            buffer.erase(0, length);
        }

        if (previewBuffer.length() == 0) {
            break;
        }

        Triplet t = findMaximumSubstring(historyBuffer, previewBuffer);

        // Добавление кода-тройки в буфер предыстории
        historyBuffer.append(previewBuffer, 0, t.getLength() + 1);
        // Удаление код-тройеи из буфера предпросмотра
        previewBuffer.erase(0, t.getLength() + 1);

        if (historyBuffer.length() > historyBufferSize) {
            historyBuffer.erase(0, historyBuffer.length() - historyBufferSize);
        }

        // Добавление кода-тройки в список кодов
        triplets.push_back(t);
    }
}

string LZ77::getExtension() {
    string extension = ".lz77";

    switch (previewBufferSize / 1024) {
        case 5:
            extension += "05";
            break;
        case 10:
            extension += "10";
            break;
        case 20:
            extension += "20";
            break;
    }

    return extension;
}

void LZ77::createOutputFile(string &path, bool isUnpacking) {
    if (isUnpacking) {
        ofstream out(path.insert(path.size() - 6, "un"), ios::out | ios::binary);
        // Запись буфера в выходной файл
        out << buffer;
        out.close();
    } else {
        trimExtension(path);
        string filePath = path + getExtension();
        ofstream out(filePath, ios::out | ios::binary);

        // Запись кодов-троек в выходной файл
        for (auto triplet: triplets) {
            outInt(out, triplet.getOffset());
            out << triplet.getValue();
            outInt(out, triplet.getLength());
        }

        out.close();
    }
}

void LZ77::openUnpackingFile(string &path) {
    trimExtension(path);
    path += getExtension();
    ifstream file(path, ios::in | ios::binary);

    int offset;
    int length;
    char value;

    // Считывание кодов-троек из файла и добавление в список кодов
    inInt(file, offset);
    while (file.get(value)) {
        inInt(file, length);
        triplets.emplace_back(Triplet(offset, length, value));
        inInt(file, offset);
    }

    file.close();
}

void LZ77::decode() {
    for (auto triplet : triplets) {
        int length = triplet.getLength();
        if (length > 0) {
            string s = buffer.substr(buffer.length() - triplet.getOffset(), min(length, triplet.getOffset()));
            // Учет возможных повторений в строке
            while (length > 0) {
                int repeats = min(length, (int) s.length());
                buffer.append(s, 0, repeats);
                length -= repeats;
            }
        }

        buffer.append(1, triplet.getValue());
    }
}

void LZ77::pack(string &path) {
    deleteData();
    openPackingFile(path);
    encode();
    createOutputFile(path, false);
}

void LZ77::unpack(string &path) {
    deleteData();
    openUnpackingFile(path);
    decode();
    createOutputFile(path, true);
}
