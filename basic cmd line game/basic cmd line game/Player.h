#pragma once
#include "ItemList.h"

class Player {
    private:
        int health;
        String spells[3];
        ItemList inventory;

    public:
        int x;
        int y;

        Player();

        Player(int x, int y);

        int getHealth();

        int addHealth(int amount);

        ItemList& getInventory();

        Player& addItem(Item* newItem);
};