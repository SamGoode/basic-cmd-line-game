#include <iostream>
#include "String.h"

class Item {
private:
    String name;
    String description;

public:
    Item() {
        name = "???";
        description = "???";
    }

    Item(const Item& item) {
        this->name = item.name;
        this->description = item.description;
    }

    Item(String name, String description) {
        this->name = name;
        this->description = description;
    }

    //virtual ~Item() = default;

    String& getName() {
        return name;
    }

    String& getDescription() {
        return description;
    }

    const String& getDescription() const {
        return description;
    }

    Item& operator=(const Item& item) {
        this->name = item.name;
        this->description = item.description;

        return *this;
    }

    void Use() {

    }
};

class Room {
public:
    String description;
    size_t itemCount;
    Item* items;
    
public:
    Room() {
        description = "empty room";
        itemCount = 0;
        items = nullptr;
    }

    Room(const Room& room) {
        this->description = room.description;
        
        this->itemCount = room.itemCount;
        this->items = new Item[room.itemCount];
        for (int i = 0; i < room.itemCount; i++) {
            this->items[i] = room.items[i];
        }
    }

    Room(String description) {
        this->description = description;
        itemCount = 0;
        items = nullptr;
    }

    Room(String description, size_t itemCount, Item* items) {
        this->description = description;

        this->itemCount = itemCount;
        this->items = new Item[itemCount];
        for (int i = 0; i < itemCount; i++) {
            this->items[i] = items[i];
        }

        //delete[] items;
    }

    ~Room() {
        delete[] this->items;
    }

    Room& operator=(const Room& room) {
        this->description = room.description;

        this->itemCount = room.itemCount;
        delete[] items;
        this->items = new Item[room.itemCount];
        for (int i = 0; i < room.itemCount; i++) {
            this->items[i] = room.items[i];
        }

        return *this;
    }

    void Description() {
        std::cout << "You entered the room\n";
        description.WriteToConsole();
        std::cout << "\nItems:\n";
        for (int i = 0; i < itemCount; i++) {
            items[i].getName().WriteToConsole();
            items[i].getDescription().WriteToConsole();
            std::cout << std::endl;
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
    
    //{ Room("It's cold in here", 2, new Item[2]{ iceCube, Item("test item", "I'm for a test")}) };
    //{
    Item iceCube = Item("ice cube", "cube of ice");
    //    Item* items = new Item[2]{ iceCube, Item("test item", "I'm for a test") };

    //    Room iceRoom = Room("It's cold in here", 2, items);//new Item[2]{ iceCube, Item("test item", "I'm for a test") });

    //    delete[] items;

    //    rooms[0][1] = iceRoom;
    //}
    rooms[0][1] = Room("It's cold in here", 2, new Item[2]{ iceCube, Item("test item", "I'm for a test") });
    
    int currentRoom = 01;
    String userInput;

    while (true) {
        //items[0].getName().WriteToConsole();
        //rooms[currentRoom / 10][currentRoom % 10].Description();
        rooms[0][1].Description();
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
