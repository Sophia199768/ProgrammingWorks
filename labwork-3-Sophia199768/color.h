#pragma once
#include <iostream>
#include <vector>

struct Color {
    int r, g, b;
    Color(int r, int g, int b);
};

class Image {
public:
    Image(int width, int height);
    const Color& GetColor(int x, int y) const;

    void SetColor(const Color color, int x, int y);

    void Export(const char* path) const;
private:
    int m_width;
    int m_height;
    std::vector<Color> m_colors;
};
