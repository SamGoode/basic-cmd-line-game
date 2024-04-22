#pragma once
#include "ItemList.h"

class Room {
    private:
        class Game* ownerPtr;

        bool exists;
        String description;
        ItemList items;
        int currentItemsIndex;

    public:
        Room();

        Room(Game& owner, String description);

        Room(Game& owner, String description, const ItemList& items);

        Room(const Room& room);

        Room& operator=(const Room& room);

        bool doesExist();

        //Room& addItem(Item* item);

        String getDescription();

        ItemList& getItems();

        Item*& getItem();
        Room& removeItem();

        void setItemsIndex(int newIndex);
        void shiftItemsIndex(int shift);
};