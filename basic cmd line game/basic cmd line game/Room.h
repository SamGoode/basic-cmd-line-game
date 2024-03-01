#pragma once
#include "item.h"

class Room {
    private:
        bool exists;
        String description;
        size_t itemCount;
        Item* items;

    public:
        Room();

        Room(const Room& room);

        Room(String description);

        Room(String description, size_t itemCount, Item* items);

        ~Room();

        Room& operator=(const Room& room);

        bool doesExist();

        String getDescription();
};