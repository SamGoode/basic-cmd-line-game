#include <iostream>
#include <windows.h>
#include "Screen.h"
#include "Player.h"
#include "Room.h"

void drawRoom(Screen& screen, char chr, int x, int y, int width, int height) {
    screen.rect(chr, x, y - 1, width, 2);
    screen.rect(chr, x - 1, y, 2, height);
    screen.rect(chr, x, y + height - 1, width, 2);
    screen.rect(chr, x + width - 1, y, 2, height);
}

class Game {
    private:
        Screen screen;
        Player player;
        Room rooms[3][3];
    public:
        Game(int width, int height) {
            screen = Screen(width, height);
        }

        void drawRoom(Screen& screen, char chr, int x, int y, int width, int height) {
            screen.rect(chr, x, y - 1, width, 2);
            screen.rect(chr, x - 1, y, 2, height);
            screen.rect(chr, x, y + height - 1, width, 2);
            screen.rect(chr, x + width - 1, y, 2, height);
        }
};

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
    rooms[1][1] = Room("This is the room you started in.");
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

    Screen screen; //= Screen(width, height - 1);
    std::cout << screen.width << ", " << screen.height << std::endl;
    std::cout << screen.screenMatrix[0][0];

    String userInput;

    player.addItem(Item("diamond", "wow shiny"));
    player.addItem(Item("knife", "wow sharp"));
    player.addItem(Item("knife", "wow sharp"));
    player.addItem(Item("knife", "wow sharp"));
    player.addItem(Item("knife", "wow sharp"));

    String response;

    while (true) {
        screen.reset();

        //Player info
        screen.text(String("Player stats:\n\nCoordinates: x:") + toString(player.x) + ", y:" + toString(player.y) + "\n\nInventory:\n" + toString(player.getInventory().getCount()) +  " items", 10, 3);
        for (int i = 0; i < player.getInventory().getCount(); i++) {
            screen.text(player.getInventory()[i].getName(), 10, 10 + i*3);
            screen.text(player.getInventory()[i].getDescription(), 12, 10 + i*3 + 1);
        }

        //Current room info
        screen.text(rooms[player.y][player.x].getDescription(), width - 50, 3);

        //Map
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (rooms[i][j].doesExist()) {
                    drawRoom(screen, 'x', width / 2 - 4 - 13 + 13 * j, height / 2 - 4 - 11 + 11 * i, 8, 8);
                }
            }
        }
        screen.rect('=', width/2 - 1 - 13 + 13 * player.x, height/2 - 1 - 11 + 11 * player.y, 2, 2);

        //user input line
        screen.text("Move 'north', 'east', 'south', 'west'", 5, height - 5);
        screen.text(response, 5, height - 3);

        screen.print();

        std::cout << std::endl << "     ";
        userInput.ReadFromConsole();

        if (userInput.ToLower() == "north") {
            if (!rooms[player.y - 1][player.x].doesExist() || player.y == 0) {
                response = "room doesn't exist.";
                continue;
            }

            response = "You entered the room to the north";
            player.y--;
        }
        else if (userInput.ToLower() == "east") {
            if (!rooms[player.y][player.x + 1].doesExist() || player.x == 2) {
                response = "room doesn't exist.";
                continue;
            }

            response = "You entered the room to the east";
            player.x++;
        }
        else if (userInput.ToLower() == "south") {
            if (!rooms[player.y + 1][player.x].doesExist() || player.y == 2) {
                response = "room doesn't exist.";
                continue;
            }

            response = "You entered the room to the south";
            player.y++;
        }
        else if (userInput.ToLower() == "west") {
            if (!rooms[player.y][player.x - 1].doesExist() || player.x == 0) {
                response = "room doesn't exist.";
                continue;
            }

            rooms[0][1].addItem(Item("diamond", "this wasn't here before"));

            response = "You entered the room to the west";
            player.x--;
        }

        Sleep(1000/tickrate);
    }
}
