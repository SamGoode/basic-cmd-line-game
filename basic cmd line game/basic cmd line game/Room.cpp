#include "Room.h"
#include <iostream>
#include "String.h"

Room::Room() {
    exists = false;
    description = "room doesn't exist";
    itemCount = 0;
    items = nullptr;
}

Room::Room(const Room& room) {
    exists = true;
    this->description = room.description;

    this->itemCount = room.itemCount;
    this->items = new Item[room.itemCount];
    for (int i = 0; i < room.itemCount; i++) {
        this->items[i] = room.items[i];
    }
}

Room::Room(String description) {
    exists = true;
    this->description = description;
    itemCount = 0;
    items = nullptr;
}

Room::Room(String description, size_t itemCount, Item* items) {
    exists = true;
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
    this->exists = room.exists;
    this->description = room.description;

    this->itemCount = room.itemCount;
    delete[] items;
    this->items = new Item[room.itemCount];
    for (int i = 0; i < room.itemCount; i++) {
        this->items[i] = room.items[i];
    }

    return *this;
}

bool Room::doesExist() {
    return exists;
}

String Room::getDescription() {
    String printOut = description;

    if (itemCount == 0) {
        printOut += "\n\n";
        return printOut;
    }

    printOut += "\n\nItems:\n";
    for (int i = 0; i < itemCount; i++) {
        printOut += items[i].getName();
        printOut += " | ";
        printOut += items[i].getDescription();
        printOut += "\n";
    }
    printOut += "\n";
    return printOut;
}