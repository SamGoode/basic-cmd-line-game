#include "Player.h"
#include "Game.h"

Player::Player() {
    ownerPtr = nullptr;

    health = 100;

    inventory;
    currentInvIndex = 0;

    spells[0] = "teleport";
    spells[1] = "eatshit";
    spells[2] = "fireball";
    spells[3] = "waterspout";
    currentSpellIndex = 0;

    teleportSpell = TeleportSpell("teleport", "teleports the player to specified coordinates");

    x = 0;
    y = 0;
}

Player::Player(Game& owner, int x, int y) {
    ownerPtr = &owner;

    health = 100;

    inventory;
    currentInvIndex = 0;

    spells[0] = "teleport";
    spells[1] = "fireball";
    spells[2] = "waterspout";
    spells[3] = "eatshit";
    currentSpellIndex = 0;

    this->x = x;
    this->y = y;
}

int Player::getHealth() {
    return health;
}

int Player::addHealth(int amount) {
    health += amount;
    return health;
}

String Player::getDescription() {
    String printout = "  Player stats:\n\n";

    //offset printed coordinates so centre room (starting room) is at 0, 0
    printout += "  Health: " + toString(health) + "\n\n  Coordinates: x:" + toString(x-2) + ", y:" + toString(y-2) + "\n\n  Inventory:\n";

    for (int i = 0; i < inventory.getCount(); i++) {
        if (i == currentInvIndex && ownerPtr->getInputState() == 2) {
            printout += 175;
            printout += 175;
        }
        else {
            printout += "  ";
        }
        
        printout += inventory[i]->getName() + " | " + inventory[i]->getDescription();
        
        if (i == currentInvIndex && ownerPtr->getInputState() == 2) {
            printout += 174;
            printout += 174;
        }
        printout += "\n";
    }

    printout += "\n  Spellbook:\n";
    for (int i = 0; i < 3; i++) {
        if (i == currentSpellIndex && ownerPtr->getInputState() == 3) {
            printout += 175;
            printout += 175;
        }
        else {
            printout += "  ";
        }

        printout += spells[i];
        
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

String Player::useSpell() {
    if (spells[currentSpellIndex] == "teleport") {
        return teleportSpell.use(*this, 2, 2);
    }

    return "wtf";
}