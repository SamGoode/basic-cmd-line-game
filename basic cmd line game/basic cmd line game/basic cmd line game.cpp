#include <iostream>
#include "String.h"

class Item {
private:
    String description;

public:
    Item() {
        description = "???";
    }

    Item(const Item& item) {
        this->description = item.getDescription();
    }

    Item(String description) {
        this->description = description;
    }

    //virtual ~Item() = default;

    String& getDescription() {
        return description;
    }

    const String& getDescription() const {
        return description;
    }

    void Use() {

    }
};

//class ItemList {
//private:
//    size_t itemCount;
//    Item* items;
//
//public:
//    ItemList() {
//        itemCount = 0;
//        items = nullptr;
//    }
//
//    ItemList(const ItemList& itemList) {
//        this->itemCount = itemList.length();
//        for (int i = 0; i < itemList.length(); i++) {
//            this->items[i] = itemList.getItem(i);
//            //itemList.getItem(i) = Item();
//        }
//    }
//
//    ItemList(size_t itemCount, Item* items) {
//        this->itemCount = itemCount;
//        std::cout << itemCount;
//        for (int i = 0; i < itemCount; i++) {
//            //this->items[i] = Item(items[i]);
//        }
//        std::cout << "test";
//    }
//
//    ~ItemList() {
//        delete[] items;
//    }
//
//    Item& getItem(size_t index) const {
//        return items[index];
//    }
//
//    size_t length() const {
//        return itemCount;
//    }
//};

class Room {
private:
    String description;
    size_t itemCount;
    Item* items;
    //ItemList items;
    
public:
    Room() {
        description = "empty room";
        itemCount = 0;
        items = nullptr;
    }

    Room(String description) {
        this->description = description;
        itemCount = 0;
        items = nullptr;
    }

    Room(String description, size_t itemCount, Item* items) {
        this->description = description;
        this->itemCount = itemCount;
        for (int i = 0; i < itemCount; i++) {
            std::cout << "assigning item " << i << std::endl;
            *(this->items + i) = *(items + i);
        }
    }

    void Description() {
        std::cout << "You entered the room\n";
        description.WriteToConsole();
        std::cout << "Items:\n";
        for (int i = 0; i < itemCount; i++) {
            std::cout << "item: " << i << std::endl;
            //items[i].getDescription().WriteToConsole();
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
    
    Room iceRoom = Room("It's cold in here", 2, new Item[2]{ iceCube, Item("test item") });

    int currentRoom = 01;
    String userInput;

    while (true) {
        //rooms[currentRoom / 10][currentRoom % 10].Description();
        iceRoom.Description();

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
