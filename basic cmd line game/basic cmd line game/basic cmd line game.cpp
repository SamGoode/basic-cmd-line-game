#include <iostream>
#include <windows.h>
#include "Screen.h"
#include "Player.h"
#include "Room.h"

int main() {
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

    SHORT width = 220;
    SHORT height = 60;
    SMALL_RECT dim = { 0, 0, width - 1, height - 1 };

    SetConsoleScreenBufferSize(hout, { width, height });
    SetConsoleWindowInfo(hout, true, &dim);

    Screen screen = Screen(width, height - 1);

    int x = 100;
    int y = 20;

    bool posx = true;

    String userInput;

    while (true) {
        screen.reset();

        screen.text("Player stats: ", 5, 5);

        String coords = String("coordinates: ") + toString(player.x) + ", " + toString(player.y);

        screen.text(coords, 10, 6);

        screen.rect('a', x, y, 5, 5);

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

        screen.print();

        std::cout << std::endl;
        userInput.ReadFromConsole();

        if (userInput.ToLower() == "north") {
            if (!rooms[player.y - 1][player.x].doesExist() || player.y == 0) {
                //std::cout << "room doesn't exist.\n";
                continue;
            }

            y -= 2;
            player.y--;
            //break;
        }
        else if (userInput.ToLower() == "east") {
            if (!rooms[player.y][player.x + 1].doesExist() || player.x == 2) {
                //std::cout << "room doesn't exist.\n";
                continue;
            }

            x += 4;
            player.x++;
            //break;
        }
        else if (userInput.ToLower() == "south") {
            if (!rooms[player.y + 1][player.x].doesExist() || player.y == 2) {
                //std::cout << "room doesn't exist.\n";
                continue;
            }

            y += 2;
            player.y++;
            //break;
        }
        else if (userInput.ToLower() == "west") {
            if (!rooms[player.y][player.x - 1].doesExist() || player.x == 0) {
                //std::cout << "room doesn't exist.\n";
                continue;
            }

            //rooms[0][1].addItem(Item("diamond", "this wasn't here before"));

            x -= 4;
            player.x--;
            //break;
        }

        //Sleep(1);
    }

    while (true) {
        std::cout << "You entered the room\n\n";
        
        rooms[player.y][player.x].getDescription().WriteToConsole();
        
        std::cout << "\nMove 'north', 'east', 'south', 'west'\n";
        
        while (true) {
            userInput.ReadFromConsole();
            
            if (userInput.ToLower() == "north") {
                if (!rooms[player.y - 1][player.x].doesExist() || player.y == 0) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }
                
                player.y--;
                break;
            }
            else if (userInput.ToLower() == "east") {
                if (!rooms[player.y][player.x + 1].doesExist() || player.x == 2) {    
                    std::cout << "room doesn't exist.\n";
                    continue;
                }
                
                player.x++;
                break;
            }
            else if (userInput.ToLower() == "south") {
                if (!rooms[player.y + 1][player.x].doesExist() || player.y == 2) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }

                player.y++;
                break;
            }
            else if (userInput.ToLower() == "west") {
                if (!rooms[player.y][player.x - 1].doesExist() || player.x == 0) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }

                rooms[0][1].addItem(Item("diamond", "this wasn't here before"));
                
                player.x--;
                break;
            }

            std::cout << "invalid input\n";
        }
        
        std::cout << "\n";
    }
}
