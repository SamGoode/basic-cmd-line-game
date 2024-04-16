#pragma once
#include "Item.h"

class ItemList {
    private:
        int count;
        Item** items;

    public:
        ItemList();

        ItemList(int count, Item** items, ItemList& masterList);

        ItemList(const ItemList& itemList);

        ~ItemList();

        ItemList& operator=(const ItemList& itemList);

        Item*& operator[](int index);

        int getCount();

        ItemList& addItem(Item* item);
        //const ItemList& addItem(Item* item) const;
        ItemList& addItem(Item* item, ItemList& masterList);

        ItemList& insertItem(Item* item, int index);
};