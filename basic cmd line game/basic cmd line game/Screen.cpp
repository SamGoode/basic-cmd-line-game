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

    screenMatrix = new unsigned int*[height];
    for (int i = 0; i < height; i++) {
        screenMatrix[i] = new unsigned int[width];
    }

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            screenMatrix[i][j] = 0x20FFFFFF;
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

    screenMatrix = new unsigned int*[screen.height];
    for (int i = 0; i < screen.height; i++) {
        screenMatrix[i] = new unsigned int[screen.width];
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
            screenMatrix[i][j] = 0x20FFFFFF;
        }
    }
}

void Screen::input(unsigned char text, unsigned char r, unsigned char g, unsigned char b, int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }

    unsigned char* ptr = (unsigned char*) &(screenMatrix[y][x]);
    *(ptr + 3) = text;
    *(ptr + 2) = r;
    *(ptr + 1) = g;
    *ptr = b;
}

void Screen::rect(char text, int x, int y, int width, int height) {
    for (int i = x; i < x + width; i++) {
        for (int j = y; j < y + height; j++) {
            input(text, 255, 255, 255, i, j);
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
        input(text[i], 255, 100, 255, x + j, y + k);
    }
}

void Screen::print() {
    String printout = "\x1b[?25l\x1b[1;1H";
    //printout += "\x1b[38;2;255;100;255m";
    String* lines = new String[height]{};
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            unsigned char* ptr = (unsigned char*) &(screenMatrix[i][j]);
            //unsigned int a = 0x30FFFFFF;
            //char* ptr = (char*) &a;

            lines[i] += "\x1b[38;2;";
            lines[i] += toString(*(ptr + 2));
            lines[i] += ";";
            lines[i] += toString(*(ptr + 1));
            lines[i] += ";";
            lines[i] += toString(*ptr);
            lines[i] += "m";

            lines[i] += *(ptr + 3);
        }
        if (i < height - 1) {
            lines[i] += '\n';
        }
    }

    for (int i = 0; i < height; i++)
    {
        printout += lines[i];
    }

    delete[] lines;

    printout += "\x1b[?25h";

    std::cout << printout.CStr();
}