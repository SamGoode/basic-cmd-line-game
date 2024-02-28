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

    virtual ~Item() = default;

    void Description() {
        description.WriteToConsole();
    }

    void Use() {

    }
};

class Room {
private:
    String description;
    Item* items;
    int itemTotal;

public:
    Room() {
        description = "empty room";
        items = nullptr;
        itemTotal = 0;
    }

    Room(String description) {
        this->description = description;
        items = nullptr;
        itemTotal = 0;
    }

    Room(String description, Item items[]) {
        this->description = description;
        
        itemTotal = sizeof(items) / sizeof(items[0]);
        this->items = new Item[itemTotal];
        for (int i = 0; i < itemTotal; i++) {
            this->items[i] = items[i];
        }
    }

    void Description() {
        std::cout << "You entered the room\n";
        description.WriteToConsole();
        std::cout << "Items:\n";
        for (int i = 0; i < itemTotal; i++) {
            items[i].Description();
        }
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

int main() {
    Room rooms[3][3];

    Item iceCube = Item("cube of ice");
    Item ices[] = { iceCube };
    Room iceRoom = Room("It's cold in here", ices);

    //Room iceRoom = Room("It's cold in here", new Item[1]{iceCube});

    rooms[0][1] = Room(iceRoom);
    //rooms[1][1] = Room("You start in this room", Item("a bomb"));

    int currentRoom = 01;
    String userInput;

    while (true) {
        rooms[currentRoom / 10][currentRoom % 10].Description();

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
