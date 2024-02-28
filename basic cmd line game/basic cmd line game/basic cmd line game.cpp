#include <iostream>
#include "String.h"

class Item {
private:
    String description;

public:
    Item() {
        description = "???";
    }

    Item(String description) {
        this->description = description;
    }

    void Description() {
        description.WriteToConsole();
    }

    void Use() {

    }
};

class Room {
private:
    String description;
    Item item;

public:
    Room() {
        description = "empty room";
        item = Item();
    }

    Room(String description) {
        this->description = description;
        item = Item();
    }

    Room(String description, Item item) {
        this->description = description;
        this->item = item;
    }

    void Description() {
        std::cout << "You entered the room\n";
        description.WriteToConsole();
        std::cout << "Items:\n";
        item.Description();
    }
};

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

int main()
{
    Room rooms[3][3];

    Item iceCube = Item("cube of ice");
    Room iceRoom = Room("It's cold in here", iceCube);

    rooms[0][1] = Room(iceRoom);
    rooms[1][1] = Room("You start in this room", Item("a bomb"));

    //rooms[0][1].Description();
    
    int currentRoom = 11;
    String userInput;

    while (true) {
        rooms[currentRoom / 10][currentRoom % 10].Description();

        std::cout << "Move 'North', 'East', 'South', 'West'\n";
        
        while (true) {
            userInput.ReadFromConsole();
            if (userInput.ToLower() == "north") {
                currentRoom -= 10;
                break;
            }

            std::cout << "invalid input\n";
        }
    }
}
