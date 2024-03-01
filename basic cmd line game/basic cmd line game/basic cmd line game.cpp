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
    
    while (true) {
        {
            Item items[2];
            {
                Item iceCube = Item("ice cube", "cube of ice");

                //delete[] items;
                items[0] = Item("test item", "I am test");
                //items[0] = {iceCube, Item("test item", "I'm for a test")};
            }

            rooms[0][1] = Room("ice room woohoo", 1, items);
            
            //delete[] items;

        }
        rooms[0][1].Description();
    }
    //rooms[0][1] = Room("It's cold in here", 2, new Item[2]{ iceCube, Item("test item", "I'm for a test") });

    rooms[1][1] = Room("You started in this room");

    int currentRoom = 01;
    String userInput;

    while (true) {
        rooms[currentRoom / 10][currentRoom % 10].Description();
        //rooms[0][1].Description();
        //std::cout << rooms[0][1].items[0].getDescription().CStr() << std::endl;
        //iceRoom.Description();

        std::cout << "move 'north', 'east', 'south', 'west'\n";
        
        while (true) {
            userInput.ReadFromConsole();
            if (userInput.ToLower().EqualTo("north")) {
                currentRoom -= 10;
                break;
            }

            std::cout << "invalid input\n";
        }
    }
}
