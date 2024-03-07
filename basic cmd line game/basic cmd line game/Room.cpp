#include "Room.h"
#include <iostream>

Room::Room() {
    exists = false;
    description = "room doesn't exist";
    items = ItemList();
}

Room::Room(String description) {
    exists = true;
    this->description = description;
    items = ItemList();
}

Room::Room(String description, const ItemList& items) {
    exists = true;
    this->description = description;
    this->items = items;
}

Room::Room(const Room& room) {
    exists = true;
    description = room.description;
    items = room.items;
}

Room& Room::operator=(const Room& room) {
    exists = room.exists;
    description = room.description;
    items = room.items;

    return *this;
}

bool Room::doesExist() {
    return exists;
}

Room& Room::addItem(Item item) {
    items.addItem(item);

    return *this;
}

String Room::getDescription() {
    String printOut = description;

    if (items.getCount() == 0) {
        printOut += "\n\n";
        return printOut;
    }

    printOut += "\n\nballs:\n";
    for (int i = 0; i < items.getCount(); i++) {
        printOut += items[i].getName();
        printOut += " | ";
        printOut += items[i].getDescription();
        printOut += "\n";
    }
    printOut += "\n";
    return printOut;
}