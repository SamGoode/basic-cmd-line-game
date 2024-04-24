#pragma once
#include "Room.h"
#include "Spells.h"

class Player {
    private:
        class Game* ownerPtr;
        int health;
        
        ItemList inventory;
        int currentInvIndex;

        SpellBase** spellBook;
        int spellCount;
        int currentSpellIndex;

    public:
        int x;
        int y;
    
    public:
        Player();

        Player(Game& owner, int x, int y);

        Player& operator=(const Player& spell);

        int getHealth();
        int addHealth(int amount);

        String getDescription();

        ItemList& getInventory();
        void setInvIndex(int newIndex);
        void shiftInvIndex(int shift);

        Item*& getItem();
        String useItem();
        int findItemIndex(const String& itemName);
        Item*& takeItem(Room& room);

        SpellBase**& getSpellBook();
        void setSpellIndex(int newIndex);
        void shiftSpellIndex(int shift);

        SpellBase*& getSpell();
        String castSpell();
        int findSpellIndex(const String& spellName);
};