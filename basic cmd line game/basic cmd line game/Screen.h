#pragma once
#include "String.h"

class Screen {
    public:    
        char** screenMatrix;
    
    public:
        int width;
        int height;

        Screen();

        Screen(int width, int height);

        ~Screen();

        void reset();

        void input(char text, int x, int y);

        void rect(char text, int x, int y, int width, int height);

        void text(String text, int x, int y);

        void print();
};