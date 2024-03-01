#pragma once
#include "item.h"

class Room {
private:
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

    void Description();
};