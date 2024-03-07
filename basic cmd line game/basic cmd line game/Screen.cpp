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

    screenMatrix = new char*[height];
    for (int i = 0; i < height; i++) {
        screenMatrix[i] = new char[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = ' ';
        }
    }
}

Screen::~Screen() {
    for (int i = 0; i < height; i++) {
        delete[] screenMatrix[i];
    }
    delete[] screenMatrix;
}

Screen& Screen::operator=(const Screen& screen) {
    for (int i = 0; i < height; i++) {
        delete[] screenMatrix[i];
    }
    delete[] screenMatrix;

    width = screen.width;
    height = screen.height;

    screenMatrix = new char*[screen.height];
    for (int i = 0; i < screen.height; i++) {
        screenMatrix[i] = new char[screen.width];
    }

    for (int i = 0; i < screen.height; i++) {
        for (int j = 0; j < screen.width; j++) {
            screenMatrix[i][j] = screen.screenMatrix[i][j];
        }
    }

    return *this;
}

void Screen::reset() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = ' ';
        }
    }
}

void Screen::input(char text, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    screenMatrix[y][x] = text;
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
    String printout = "\x1b[?25l\x1b[1;1H";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            printout += screenMatrix[i][j];
        }
        if (i < height - 1) {
            printout += '\n';
        }
    }
    printout += "\x1b[?25h";
    
    std::cout << printout.CStr();
}