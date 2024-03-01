#include "Room.h"
#include <iostream>
#include "String.h"

Room::Room() {
    description = "empty room";
    itemCount = 0;
    items = nullptr;
}

Room::Room(const Room& room) {
    this->description = room.description;

    this->itemCount = room.itemCount;
    this->items = new Item[room.itemCount];
    for (int i = 0; i < room.itemCount; i++) {
        this->items[i] = room.items[i];
    }
}

Room::Room(String description) {
    this->description = description;
    itemCount = 0;
    items = nullptr;
}

Room::Room(String description, size_t itemCount, Item* items) {
    this->description = description;

    this->itemCount = itemCount;
    this->items = new Item[itemCount];
    for (int i = 0; i < itemCount; i++) {
        this->items[i] = items[i];
    }
}

Room::~Room() {
    delete[] items;
}

Room& Room::operator=(const Room& room) {
    this->description = room.description;

    this->itemCount = room.itemCount;
    delete[] items;
    this->items = new Item[room.itemCount];
    for (int i = 0; i < room.itemCount; i++) {
        this->items[i] = room.items[i];
    }

    return *this;
}

void Room::Description() {
    std::cout << "You entered the room\n";
    description.WriteToConsole();
    std::cout << "\nItems:\n";
    for (int i = 0; i < itemCount; i++) {
        items[i].getName().WriteToConsole();
        items[i].getDescription().WriteToConsole();
        std::cout << std::endl;
    }
}