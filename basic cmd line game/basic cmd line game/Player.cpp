#include "Player.h"
#include "Game.h"

Player::Player() {
    ownerPtr = nullptr;

    x = 0;
    y = 0;

    maxHealth = 100;
    health = 100;

    maxMana = 50;
    mana = 50;

    inventory;
    currentInvIndex = 0;

    spellBook;
    currentSpellIndex = 0;
}

Player::Player(Game& owner, int x, int y) {
    ownerPtr = &owner;

    this->x = x;
    this->y = y;

    maxHealth = 100;
    health = 100;

    maxMana = 50;
    mana = 50;

    inventory;
    currentInvIndex = 0;

    spellBook;
    currentSpellIndex = 0;
}

Player& Player::operator=(const Player& player) {
    ownerPtr = player.ownerPtr;

    x = player.x;
    y = player.y;

    maxHealth = player.maxHealth;
    health = player.health;

    maxMana = player.maxMana;
    mana = player.mana;

    inventory = player.inventory;
    currentInvIndex = player.currentInvIndex;

    spellBook = player.spellBook;
    currentSpellIndex = player.currentSpellIndex;

    return *this;
}

int Player::getX() {
    return x;
}

int Player::getY() {
    return y;
}

//returns 0 on success, 1 outside of map, 2 room doesn't exist
int Player::setPos(int newX, int newY) {
    if (newX < 0 || newX > 4 || newY < 0 || newY > 4) {
        return 1;
    }

    if (!ownerPtr->getRoom(newX, newY).doesExist()) {
        return 2;
    }
    
    x = newX;
    y = newY;
    return 0;
}

//returns 0 on success, 1 outside of map, 2 room doesn't exist
int Player::shiftPos(int shiftX, int shiftY) {
    return setPos(x + shiftX, y + shiftY);
}

int Player::getHealth() {
    return health;
}

int Player::setHealth(int amount) {
    health = amount;
    return health;
}

int Player::shiftHealth(int amount) {
    return setHealth(health + amount);
}

int Player::getMana() {
    return mana;
}

int Player::setMana(int amount) {
    mana = amount;
    return mana;
}

int Player::shiftMana(int amount) {
    return setMana(mana + amount);
}

String Player::getDescription() {
    //offset printed coordinates so centre room (starting room) is at 0, 0
    String printout = " Coordinates: x:" + toString(x-2) + ", y:" + toString(y-2) + "\n\n Health: " + toString(health) + "/" + toString(maxHealth) + "\n Mana: " + toString(mana) + "/" + toString(maxMana) + "\n\n Inventory: \n";

    for (int i = 0; i < inventory.getCount(); i++) {
        if (i == currentInvIndex && ownerPtr->getInputState() == 2) {
            printout += 175;
            printout += 175;
        }
        else {
            printout += "  ";
        }
        
        printout += inventory[i]->getName();
        
        if (i == currentInvIndex && ownerPtr->getInputState() == 2) {
            printout += 174;
            printout += 174;
        }
        printout += "\n";
    }

    printout += "\n Spellbook:\n";
    for (int i = 0; i < spellBook.getCount(); i++) {
        if (i == currentSpellIndex && ownerPtr->getInputState() == 3) {
            printout += 175;
            printout += 175;
        }
        else {
            printout += "  ";
        }

        printout += spellBook[i]->getName();
        
        if (i == currentSpellIndex && ownerPtr->getInputState() == 3) {
            printout += 174;
            printout += 174;
        }
        printout += "\n";
    }

    return printout;
}

ItemList& Player::getInventory() {
    return inventory;
}

void Player::setInvIndex(int newIndex) {
    if (newIndex < 0) {
        newIndex = 0;
    }
    else if (newIndex > inventory.getCount() - 1) {
        newIndex = inventory.getCount() - 1;
    }
    
    currentInvIndex = newIndex;
}

void Player::shiftInvIndex(int shift) {
    setInvIndex(currentInvIndex + shift);
}

Item*& Player::getItem() {
    return inventory[currentInvIndex];
}

String Player::useItem() {
    return getItem()->use(*this);
}

Item*& Player::takeItem(Room& room) {
    if (!room.doesExist() || room.getItems().getCount() == 0) {
        Item* null = nullptr;
        return null;
    }

    Item* item = room.removeItem();
    room.shiftItemsIndex(-1);

    inventory.insertItem(item, inventory.findSlotIndex(item->getName()));
    return item;
}

SpellList& Player::getSpellBook() {
    return spellBook;
}

void Player::setSpellIndex(int newIndex) {
    if (newIndex < 0) {
        newIndex = 0;
    }
    else if (newIndex > spellBook.getCount() - 1) {
        newIndex = spellBook.getCount() - 1;
    }

    currentSpellIndex = newIndex;
}

void Player::shiftSpellIndex(int shift) {
    setSpellIndex(currentSpellIndex + shift);
}

SpellBase*& Player::getSpell() {
    return spellBook[currentSpellIndex];
}

String Player::castSpell() {
    return getSpell()->cast(*this, 0, nullptr);
}

String Player::castSpell(int argCount, int* args) {
    return getSpell()->cast(*this, argCount, args);
}