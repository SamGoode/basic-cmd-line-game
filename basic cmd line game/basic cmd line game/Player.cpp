#include "Player.h"

Player::Player() {
    x = 0;
    y = 0;

    health = 100;

    spells[0] = "fireball";
    spells[1] = "waterspout";
    spells[2] = "eatshit";

    inventory;
}

Player::Player(int x, int y) {
    this->x = x;
    this->y = y;

    health = 100;

    spells[0] = "fireball";
    spells[1] = "waterspout";
    spells[2] = "eatshit";

    inventory;
}

int Player::getHealth() {
    return health;
}

int Player::addHealth(int amount) {
    health += amount;
    return health;
}

ItemList& Player::getInventory() {
    return inventory;
}

//Player& Player::addItem(Item* newItem) {
//    inventory.addItem(newItem);
//
//    return *this;
//}

String Player::getDescription() {
    String printout = "Player stats:\n\n";

    printout += String("Health: ") + toString(health) + "\n\nCoordinates: x:" + toString(x) + ", y:" + toString(y) + "\n\nInventory:\n";

    for (int i = 0; i < inventory.getCount(); i++) {
        printout += inventory[i]->getName() + " | " + inventory[i]->getDescription() + "\n";
    }

    return printout;
}