#include <iostream>
#include <windows.h>
#include "Game.h"

int main() {
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

    SetConsoleOutputCP(437);

    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);

    DWORD consoleMode;
    GetConsoleMode(hout, &consoleMode);
    SetConsoleMode(hout, consoleMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    
    SHORT width = 220;
    SHORT height = 60;

    SetConsoleScreenBufferSize(hout, { width, height });

    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);

    GetCurrentConsoleFontEx(hout, false, &cfi);

    cfi.dwFontSize.Y = 15;
    cfi.dwFontSize.X = 7;//cfi.dwFontSize.Y / 2;

    SetCurrentConsoleFontEx(hout, false, &cfi);

    SMALL_RECT dim = { 0, 0, width - 1, height - 1 };

    if (!SetConsoleWindowInfo(hout, true, &dim)) {
        cfi.dwFontSize.Y = 13;
        cfi.dwFontSize.X = 6;

        SetCurrentConsoleFontEx(hout, false, &cfi);

        SetConsoleWindowInfo(hout, true, &dim);
    }

    Game game = Game(width, height, 50);

    game.run();
}
