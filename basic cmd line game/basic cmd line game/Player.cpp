#include "Player.h"
#include "Game.h"

Player::Player() {
    ownerPtr = nullptr;

    health = 100;

    inventory;
    currentInvIndex = 0;

    spellCount = 0;
    spellBook = nullptr;
    currentSpellIndex = 0;

    x = 0;
    y = 0;
}

Player::Player(Game& owner, int x, int y) {
    ownerPtr = &owner;

    health = 100;

    inventory;
    currentInvIndex = 0;

    spellCount = 3;
    spellBook = new SpellBase*[spellCount];
    spellBook[0] = new SpellBase("hiya", "I don't actually do anything");
    spellBook[1] = new TeleportSpell("teleport", "teleports the player to specified\ncoordinates");
    spellBook[2] = new SpellBase("dummy spell", "doesn't do anything");
    currentSpellIndex = 0;

    this->x = x;
    this->y = y;
}

Player& Player::operator=(const Player& player) {
    ownerPtr = player.ownerPtr;

    health = player.health;

    inventory = player.inventory;
    currentInvIndex = player.currentInvIndex;

    for (int i = 0; i < spellCount; i++) {
        delete spellBook[i];
    }
    delete[] spellBook;

    spellCount = player.spellCount;
    spellBook = player.spellBook;
    currentSpellIndex = 0;

    x = player.x;
    y = player.y;

    return *this;
}

int Player::getHealth() {
    return health;
}

int Player::addHealth(int amount) {
    health += amount;
    return health;
}

String Player::getDescription() {
    String printout = " Player stats:\n\n";

    //offset printed coordinates so centre room (starting room) is at 0, 0
    printout += " Health: " + toString(health) + "\n\n Coordinates: x:" + toString(x-2) + ", y:" + toString(y-2) + "\n\n Inventory:\n";

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
    for (int i = 0; i < spellCount; i++) {
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

int Player::findItemIndex(String itemName) {
    int upperBound = inventory.getCount() - 1;
    int lowerBound = 0;
    int index;

    while (true) {
        index = ((upperBound - lowerBound) / 2) + lowerBound;

        if (itemName == inventory[index]->getName()) {
            return index;
        }

        if (upperBound <= lowerBound) {
            return -1;
        }

        if (itemName < inventory[index]->getName()) {
            upperBound = index - 1;
        }
        else {
            lowerBound = index + 1;
        }
    }
}

SpellBase**& Player::getSpellBook() {
    return spellBook;
}

void Player::setSpellIndex(int newIndex) {
    if (newIndex < 0) {
        newIndex = 0;
    }
    else if (newIndex > 3 - 1) {
        newIndex = 3 - 1;
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
    return getSpell()->cast(*this, 0, 2);
}

int Player::findSpellIndex(String spellName) {
    int upperBound = spellCount - 1;
    int lowerBound = 0;
    int index;

    while (true) {
        index = ((upperBound - lowerBound) / 2) + lowerBound;

        if (spellName == spellBook[index]->getName()) {
            return index;
        }

        if (upperBound <= lowerBound) {
            return -1;
        }

        if (spellName < spellBook[index]->getName()) {
            upperBound = index - 1;
        }
        else {
            lowerBound = index + 1;
        }
    }
}