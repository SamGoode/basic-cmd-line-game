#pragma once
#include "Item.h"

class ItemList {
    private:
        size_t count;
        Item** items;

    public:
        ItemList();

        ItemList(size_t count, Item** items);

        ItemList(const ItemList& itemList);

        ~ItemList();

        ItemList& operator=(const ItemList& itemList);

        Item*& operator[](size_t index);

        size_t getCount();

        ItemList& addItem(Item* item);
};