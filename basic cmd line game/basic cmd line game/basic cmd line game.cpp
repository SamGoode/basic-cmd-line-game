#include <iostream>
#include <windows.h>
#include "Game.h"

int main() {
    std::cout << "toString() test: " << toString(0x80000000) + " testing" << std::endl;
    std::cout << "toInt() test: " << toInt("-12345678901") << std::endl;
    int test = 0x7FFFFFFF;
    //test++;
    test = test * -1;
    std::cout << test << std::endl;
    return 0;

    //while (true) {
    //    /*ItemList database = ItemList();

    //    ItemList leak = ItemList(2, new Item*[2] { new Item("fancy sword", "I look fancy"), new Item("gold coin", "I'm a golden circle") }, database);

    //    Room room;
    //    room = Room();

    //    std::cout << leak[1]->getName() << std::endl;

    //    for (int i = 0; i < database.getCount(); i++) {
    //        delete database[i];
    //    }*/

        //Game game = Game(220, 60);
    //}
    /*
    Current layout of rooms

        {sword room}      {cold room}   {wombat room}
        {mannequin room}  {start room}  {empty}
        {empty}           {empty}       {empty}

    */

    //game ticks per second
    int tickrate = 200;

    SetConsoleOutputCP(437);

    SHORT width = 220;
    SHORT height = 60;

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    GetCurrentConsoleFontEx(hout, false, &cfi);

    cfi.dwFontSize.Y = 15;
    cfi.dwFontSize.X = 7;//cfi.dwFontSize.Y / 2;

    SetCurrentConsoleFontEx(hout, false, &cfi);

    SMALL_RECT dim = { 0, 0, width - 1, height - 1 };

    SetConsoleScreenBufferSize(hout, { width, height });
    SetConsoleWindowInfo(hout, true, &dim);

    Game game = Game(width, height);

    while (true) {
        game.run();

        Sleep(1000 / tickrate);
    }
}
