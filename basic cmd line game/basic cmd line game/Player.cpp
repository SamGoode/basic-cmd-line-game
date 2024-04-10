#include "Player.h"

Player::Player() {
    x = 0;
    y = 0;

    health = 100;

    spells[0] = "fireball";
    spells[1] = "waterspout";
    spells[2] = "eatshit";

    inventory;
    currentInvIndex = 0;
}

Player::Player(int x, int y) {
    this->x = x;
    this->y = y;

    health = 100;

    spells[0] = "fireball";
    spells[1] = "waterspout";
    spells[2] = "eatshit";

    inventory;
    currentInvIndex = 1;
}

int Player::getHealth() {
    return health;
}

int Player::addHealth(int amount) {
    health += amount;
    return health;
}

String Player::getDescription() {
    String printout = "Player stats:\n\n";

    //offset printed coordinates so centre room (starting room) is at 0, 0
    printout += "Health: " + toString(health) + "\n\nCoordinates: x:" + toString(x-2) + ", y:" + toString(y-2) + "\n\nInventory:\n";

    for (int i = 0; i < inventory.getCount(); i++) {
        if (i == currentInvIndex) {
            printout += ">>";
        }
        printout += inventory[i]->getName() + " | " + inventory[i]->getDescription() + "\n";
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