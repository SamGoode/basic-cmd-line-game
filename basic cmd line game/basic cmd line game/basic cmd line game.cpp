#include <iostream>
#include "Room.h"

class Player {
private:
    String spells[3];

public:
    Player() {
        spells[0] = "fireball";
        spells[1] = "waterspout";
        spells[2] = "eatshit";
    }
};

int main() {
    Room rooms[3][3];

    rooms[0][0] = Room("There's a sword stuck in a large boulder.", 1, new Item[1]{ Item("fancy sword", "I look fancy") });
    rooms[0][1] = Room("It's cold in here.", 2, new Item[2]{ Item("ice cube", "I'm a block of ice"), Item("gold coin", "I'm a golden circle") });
    rooms[0][2] = Room("There's a wombat in here.");
    rooms[1][1] = Room("This is the room you started in.", 0, nullptr);

    /*
    Current layout of rooms

        {empty}  {cold room}  {empty}
        {empty}  {start room} {empty}
        {empty}  {empty}      {empty}
    
    */

    struct pos {
        int x;
        int y;
    };

    pos currentRoom = { 1, 1 };

    String userInput;

    while (true) {
        std::cout << "You entered the room\n\n";
        
        rooms[currentRoom.y][currentRoom.x].getDescription().WriteToConsole();
        
        std::cout << "\nMove 'north', 'east', 'south', 'west'\n";
        
        while (true) {
            userInput.ReadFromConsole();
            
            if (userInput.ToLower() == "north") {
                if (!rooms[currentRoom.y - 1][currentRoom.x].doesExist() || currentRoom.y == 0) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }
                
                currentRoom.y -= 1;
                break;
            }
            else if (userInput.ToLower() == "east") {
                if (!rooms[currentRoom.y][currentRoom.x + 1].doesExist() || currentRoom.x == 2) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }
                
                currentRoom.x += 1;
                break;
            }
            else if (userInput.ToLower() == "south") {
                if (!rooms[currentRoom.y + 1][currentRoom.x].doesExist() || currentRoom.y == 2) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }

                currentRoom.y += 1;
                break;
            }
            else if (userInput.ToLower() == "west") {
                if (!rooms[currentRoom.y][currentRoom.x - 1].doesExist() || currentRoom.x == 0) {
                    std::cout << "room doesn't exist.\n";
                    continue;
                }
                
                currentRoom.x -= 1;
                break;
            }

            std::cout << "invalid input\n";
        }
        
        std::cout << "\n";
    }
}
