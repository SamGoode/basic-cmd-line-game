#include "Screen.h"
#include <iostream>
#include "String.h"

Screen::Screen() {
    width = 0;
    height = 0;
    screenMatrix = nullptr;
}

Screen::Screen(int width, int height) {
    this->width = width;
    this->height = height;

    screenMatrix = new char[this->width * this->height + 1];

    for (int i = 0; i < this->width * this->height; i++) {
        screenMatrix[i] = ' ';
    }
    screenMatrix[this->width * this->height] = 0;
}

Screen::~Screen() {
    delete[] screenMatrix;
}

Screen& Screen::operator=(const Screen& screen) {
    delete[] screenMatrix;

    width = screen.width;
    height = screen.height;

    screenMatrix = new char[width * height + 1];

    for (int i = 0; i < width * height; i++) {
        screenMatrix[i] = screen.screenMatrix[i];
    }
    screenMatrix[width * height] = 0;

    return *this;
}

void Screen::reset() {
    for (int i = 0; i < width * height; i++) {
        screenMatrix[i] = ' ';
    }
    screenMatrix[width * height] = 0;
}

void Screen::input(char text, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    screenMatrix[x + y * width] = text;
}

void Screen::rect(char text, int x, int y, int width, int height) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            input(text, i, j);
        }
    }
}

void Screen::text(String text, int x, int y) {
    for (int i = 0, j = 0, k = 0; i < text.Length(); i++, j++) {
        if (text[i] == '\n') {
            j = -1;
            k++;
            continue;
        }
        input(text[i], x + j, y + k);
    }
}

void Screen::print() {
    std::cout << "\x1b[?25l\x1b[1;1H";

    //printout += "\x1b[38;2;255;255;0m";

    std::cout << screenMatrix;
}