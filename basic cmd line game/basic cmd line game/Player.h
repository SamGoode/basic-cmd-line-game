#pragma once
#include "ItemList.h"

class Player {
    private:
        String spells[3];
        ItemList inventory;

    public:
        int x;
        int y;

        Player();

        Player(int x, int y);

        ItemList& getInventory();

        Player& addItem(Item newItem);
};