#include "color.h"

#include <iostream>
#include <fstream>

Color::Color(int r = 0, int g = 0, int b = 0)
    : r(r), g(g), b(b) {
}

Image::Image(int width, int height)
    : m_width(width), m_height(height), m_colors(std::vector<Color>(width* height)) {
}

const Color& Image::GetColor(int x, int y) const {
    return m_colors[y * m_width + x];
}

void Image::SetColor(const Color color, int x, int y) {
    m_colors[y * m_width + x].r = color.r;
    m_colors[y * m_width + x].g = color.g;
    m_colors[y * m_width + x].b = color.b;
}

void Image::Export(const char* path) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File could not be opened\n";
        return;
    }
    unsigned char bmpPad[3] = { 0, 0, 0 };

    const int paddingAmount = ((4 - (m_width * 3) % 4) % 4);

    const int fileHeaderSize = 14; // Const size of header file
    const int informationHeaderSize = 40; // Const size of information Header
    const int fileSize = fileHeaderSize + informationHeaderSize + m_width * m_height * 3 + paddingAmount * m_height;
    unsigned char fileHeader[fileHeaderSize];

    fileHeader[0] = 'B';
    fileHeader[1] = 'M';

    fileHeader[2] = fileSize;
    fileHeader[3] = fileSize >> 8;
    fileHeader[4] = fileSize >> 16;
    fileHeader[5] = fileSize >> 24;

    std::memset(fileHeader + 6, 0, 8);

    unsigned char informationHeader[informationHeaderSize];

    informationHeader[0] = informationHeaderSize;
    informationHeader[1] = 0;
    informationHeader[2] = 0;
    informationHeader[3] = 0;

    informationHeader[4] = m_width;
    informationHeader[5] = m_width >> 8;
    informationHeader[6] = m_width >> 16;
    informationHeader[7] = m_width >> 24;

    informationHeader[8] = m_height;
    informationHeader[9] = m_height >> 8;
    informationHeader[10] = m_height >> 16;
    informationHeader[11] = m_height >> 24;

    informationHeader[12] = 1;
    informationHeader[13] = 0;

    informationHeader[14] = 24;
    std::memset(informationHeader + 15, 0, 25);

    f.write(reinterpret_cast<char*>(fileHeader), fileHeaderSize);
    f.write(reinterpret_cast<char*>(informationHeader), informationHeaderSize);

    for (int y = 0; y < m_height; y++) {
        for (int x = 0; x < m_width; x++) {
            unsigned  char r = static_cast<unsigned char>(GetColor(x, y).r);
            unsigned  char g = static_cast<unsigned char>(GetColor(x, y).g);
            unsigned  char b = static_cast<unsigned char>(GetColor(x, y).b);

            unsigned  char color[] = { b, g, r };

            f.write(reinterpret_cast<char*>(color), 3); // One pixel 3 bytes
        }
        f.write(reinterpret_cast<char*>(bmpPad), paddingAmount);
    }
    f.close();
}
