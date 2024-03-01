#pragma once
#include "ItemList.h"

class Room {
    private:
        bool exists;
        String description;
        ItemList items;

    public:
        Room();

        Room(const Room& room);

        Room(String description);

        Room(String description, ItemList items);

        Room& operator=(const Room& room);

        bool doesExist();

        Room& addItem(Item item);

        String getDescription();
};