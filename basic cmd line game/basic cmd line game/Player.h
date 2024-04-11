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
    
    public:
        Player();

        Player(int x, int y);

        int getHealth();

        int addHealth(int amount);

        String getDescription(int inputState);

        ItemList& getInventory();

        void setInvIndex(int newIndex);

        void shiftInvIndex(int shift);

        Item*& getItem();

        String useItem();

        int findItemIndex(String itemName);
};