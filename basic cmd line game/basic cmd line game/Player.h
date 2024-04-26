#pragma once
#include "Room.h"
#include "Spells.h"

class Player {
    private:
        class Game* ownerPtr;

        int x;
        int y;

        int maxHealth;
        int health;

        int maxMana;
        int mana;
        
        ItemList inventory;
        int currentInvIndex;

        SpellBase** spellBook;
        int spellCount;
        int currentSpellIndex;
    
    public:
        Player();

        Player(Game& owner, int x, int y);

        Player& operator=(const Player& spell);

        int getX();
        int getY();
        int setPos(int newX, int newY);
        int shiftPos(int shiftX, int shiftY);

        int getHealth();
        int setHealth(int amount);
        int shiftHealth(int amount);

        int getMana();
        int setMana(int amount);
        int shiftMana(int amount);

        String getDescription();

        ItemList& getInventory();
        void setInvIndex(int newIndex);
        void shiftInvIndex(int shift);

        Item*& getItem();
        String useItem();
        Item*& takeItem(Room& room);

        SpellBase**& getSpellBook();
        void setSpellIndex(int newIndex);
        void shiftSpellIndex(int shift);

        SpellBase*& getSpell();
        String castSpell();
        String castSpell(int argCount, int* args);
        int findSpellIndex(const String& spellName);
};