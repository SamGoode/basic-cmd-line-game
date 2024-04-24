#include "Room.h"
#include "Game.h"

Room::Room() {
    ownerPtr = nullptr;
    exists = false;
    description = "room doesn't exist";
    items = ItemList();
    currentItemsIndex = -1;
}

Room::Room(Game& owner, String description) {
    ownerPtr = &owner;
    exists = true;
    this->description = description;
    items = ItemList();
    currentItemsIndex = -1;
}

Room::Room(Game& owner, String description, const ItemList& items) {
    ownerPtr = &owner;
    exists = true;
    this->description = description;
    this->items = items;
    currentItemsIndex = 0;
}

Room::Room(const Room& room) {
    ownerPtr = room.ownerPtr;
    exists = room.exists;
    description = room.description;
    items = room.items;
    currentItemsIndex = room.currentItemsIndex;
}

Room& Room::operator=(const Room& room) {
    ownerPtr = room.ownerPtr;
    exists = room.exists;
    description = room.description;
    items = room.items;
    currentItemsIndex = room.currentItemsIndex;

    return *this;
}

bool Room::doesExist() {
    return exists;
}

//Room& Room::addItem(Item* item) {
//    items.addItem(item);
//
//    return *this;
//}

String Room::getDescription() {
    String printOut = description;

    if (items.getCount() == 0) {
        printOut += "\n\n";
        return printOut;
    }

    printOut += "\n\nItems:\n";
    for (int i = 0; i < items.getCount(); i++) {

        if (i == currentItemsIndex && ownerPtr->getInputState() == 4) {
            printOut += 175;
        }

        printOut += items[i]->getName();
        printOut += " | ";
        printOut += items[i]->getDescription();

        if (i == currentItemsIndex && ownerPtr->getInputState() == 4) {
            printOut += 174;
        }

        printOut += "\n";
    }
    printOut += "\n";
    return printOut;
}

ItemList& Room::getItems() {
    return items;
}

Item*& Room::getItem() {
    return items[currentItemsIndex];
}

Item*& Room::removeItem() {
    Item* itemRef = items[currentItemsIndex];
    items.removeItem(currentItemsIndex);

    return itemRef;
}

void Room::setItemsIndex(int newIndex) {
    if (newIndex < 0) {
        newIndex = 0;
    }
    else if (newIndex > items.getCount() - 1) {
        newIndex = items.getCount() - 1;
    }

    currentItemsIndex = newIndex;
}

void Room::shiftItemsIndex(int shift) {
    setItemsIndex(currentItemsIndex + shift);
}