#include <iostream>
#include <windows.h>
#include "Game.h"

int main() {

    //while (true) {
    //    ItemList leak = ItemList(1, new Item*[1] { new Item("fancy sword", "I look fancy") });
    //}
    /*
    Current layout of rooms

        {sword room}      {cold room}   {wombat room}
        {mannequin room}  {start room}  {empty}
        {empty}           {empty}       {empty}

    */

    //game ticks per second
    int tickrate = 200;

    SHORT width = 220;
    SHORT height = 60;

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    GetCurrentConsoleFontEx(hout, false, &cfi);

    cfi.dwFontSize.Y = 14;
    cfi.dwFontSize.X = cfi.dwFontSize.Y / 2;

    SetCurrentConsoleFontEx(hout, false, &cfi);

    SMALL_RECT dim = { 0, 0, width - 1, height - 1 };

    SetConsoleScreenBufferSize(hout, { width, 80 });
    SetConsoleWindowInfo(hout, true, &dim);

    Game game = Game(width, height);

    while (true) {
        game.run();

        Sleep(1000 / tickrate);
    }
}
