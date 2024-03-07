#include <iostream>
#include <windows.h>
#include "Screen.h"
#include "Player.h"
#include "Room.h"

int main() {
    //game ticks per second
    int tickrate = 200;

    SHORT width = 220;
    SHORT height = 60;

    Player player(1, 1);

    Room rooms[3][3];

    rooms[0][0] = Room("There's a sword stuck in a large boulder.", ItemList(1, new Item[1]{ Item("fancy sword", "I look fancy") }));
    rooms[0][1] = Room("It's cold in here.", ItemList(2, new Item[2]{ Item("ice cube", "I'm a block of ice"), Item("gold coin", "I'm a golden circle") }));
    rooms[0][2] = Room("There's a wombat in here.");
    rooms[1][1] = Room("This is the room you started in.", ItemList());
    rooms[1][0] = Room("It's a large room with training mannequins.", ItemList(1, new Item[1]{ Item("training mannequin", "It's a straw and cotton humanlike figure with slash marks") }));
    
    /*
    Current layout of rooms

        {sword room}  {cold room}   {wombat room}
        {mannequin room}       {start room}  {empty}
        {empty}       {empty}       {empty}
    
    */
    
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    
    CONSOLE_FONT_INFOEX cfi;
    cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    
    GetCurrentConsoleFontEx(hout, false, &cfi);

    cfi.dwFontSize.Y = 14;
    cfi.dwFontSize.X = cfi.dwFontSize.Y / 2;

    SetCurrentConsoleFontEx(hout, false, &cfi);

    SMALL_RECT dim = { 0, 0, width - 1, height - 1 };

    SetConsoleScreenBufferSize(hout, { width, height });
    SetConsoleWindowInfo(hout, true, &dim);

    Screen screen = Screen(width, height - 1);
    
    int x = width/2 - 1;
    int y = height/2 - 1;

    String userInput;

    player.addItem(Item("diamond", "wow shiny"));
    player.addItem(Item("knife", "wow sharp"));
    player.addItem(Item("knife", "wow sharp"));
    player.addItem(Item("knife", "wow sharp"));
    player.addItem(Item("knife", "wow sharp"));

    String response;

    bool posx = true;

    while (true) {
        screen.reset();

        screen.text(String("Player stats:\n\nCoordinates: x:") + toString(player.x) + ", y:" + toString(player.y) + "\n\nInventory:\n" + toString(player.getInventory().getCount()) +  " items", 10, 3);
        for (int i = 0; i < player.getInventory().getCount(); i++) {
            screen.text(player.getInventory()[i].getName(), 10, 10 + i*3);
            screen.text(player.getInventory()[i].getDescription(), 12, 10 + i*3 + 1);
        }

        screen.text(rooms[player.y][player.x].getDescription(), width - 50, 3);

        screen.text("Move 'north', 'east', 'south', 'west'", 5, height - 5);

        screen.text(response, 5, height - 3);

        if (posx) {
            //x += 2;
        }
        else {
            //x -= 2;
        }

        if (x <= 0) {
            posx = true;
        }
        else if (x + 4 >= width - 1) {
            posx = false;
        }

        screen.rect('=', x, y, 2, 2);

        screen.print();

        std::cout << std::endl << "     ";
        userInput.ReadFromConsole();

        if (userInput.ToLower() == "north") {
            if (!rooms[player.y - 1][player.x].doesExist() || player.y == 0) {
                response = "room doesn't exist.";
                continue;
            }

            response = "You entered the room to the north";
            y -= 5;
            player.y--;
        }
        else if (userInput.ToLower() == "east") {
            if (!rooms[player.y][player.x + 1].doesExist() || player.x == 2) {
                response = "room doesn't exist.";
                continue;
            }

            response = "You entered the room to the east";
            x += 20;
            player.x++;
        }
        else if (userInput.ToLower() == "south") {
            if (!rooms[player.y + 1][player.x].doesExist() || player.y == 2) {
                response = "room doesn't exist.";
                continue;
            }

            response = "You entered the room to the south";
            y += 5;
            player.y++;
        }
        else if (userInput.ToLower() == "west") {
            if (!rooms[player.y][player.x - 1].doesExist() || player.x == 0) {
                response = "room doesn't exist.";
                continue;
            }

            rooms[0][1].addItem(Item("diamond", "this wasn't here before"));

            response = "You entered the room to the west";
            x -= 20;
            player.x--;
        }

        Sleep(1000/tickrate);
    }
}
