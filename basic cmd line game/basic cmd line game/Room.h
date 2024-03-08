#pragma once
#include "ItemList.h"

class Room {
    private:
        bool exists;
        String description;
        ItemList items;

    public:
        Room();

        Room(String description);

        Room(String description, const ItemList& items);

        Room(const Room& room);

        Room& operator=(const Room& room);

        bool doesExist();

        Room& addItem(Item* item);

        String getDescription();
};