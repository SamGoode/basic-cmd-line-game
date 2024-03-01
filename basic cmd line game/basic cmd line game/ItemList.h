#pragma once
#include "Item.h"

class ItemList {
    private:
        size_t count;
        Item* items;

    public:
        ItemList();

        ItemList(const ItemList& itemList);

        ItemList(size_t count, Item* items);

        ~ItemList();

        ItemList& operator=(const ItemList& itemList);

        Item& operator[](size_t index);

        size_t getCount();

        ItemList& addItem(Item item);
};