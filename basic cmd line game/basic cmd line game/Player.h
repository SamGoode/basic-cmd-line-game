#pragma once
#include "ItemList.h"

class Player {
    private:
        int health;
        String spells[3];
        ItemList inventory;
        int currentInvIndex;

    public:
        int x;
        int y;

        Player();

        Player(int x, int y);

        int getHealth();

        int addHealth(int amount);

        String getDescription();

        ItemList& getInventory();

        //Player& addItem(Item* newItem);

        Item*& getItem();

        String useItem();
};