#pragma once
#include "ItemList.h"
#include "Spell.h"

class Player {
    private:
        class Game* ownerPtr;
        int health;
        ItemList inventory;
        int currentInvIndex;
        String spells[4];
        int currentSpellIndex;
        TeleportSpell teleportSpell;

    public:
        int x;
        int y;
    
    public:
        Player();

        Player(Game& owner, int x, int y);

        int getHealth();

        int addHealth(int amount);

        String getDescription();

        ItemList& getInventory();

        void setInvIndex(int newIndex);

        void shiftInvIndex(int shift);

        Item*& getItem();

        String useItem();

        int findItemIndex(String itemName);

        void setSpellIndex(int newIndex);

        void shiftSpellIndex(int shift);

        String useSpell();
};