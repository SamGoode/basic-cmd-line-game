#pragma once
#include "String.h"

class Screen {
    private:    
        unsigned int** screenMatrix;
    
    public:
        int width;
        int height;

        Screen();

        Screen(int width, int height);

        ~Screen();

        Screen& operator=(const Screen& screen);

        void reset();

        void input(unsigned char text, unsigned char r, unsigned char g, unsigned char b, int x, int y);

        void rect(char text, int x, int y, int width, int height);

        void text(String text, int x, int y);

        void print();
};
//int* ptr;
//char* ptr2 = (char*)ptr
//* (ptr2);//0x30
//*(ptr2+1)//