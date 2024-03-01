#include "Player.h"

Player::Player() {
    x = 0;
    y = 0;

    spells[0] = "fireball";
    spells[1] = "waterspout";
    spells[2] = "eatshit";

    inventory;
}

Player::Player(int x, int y) {
    this->x = x;
    this->y = y;

    spells[0] = "fireball";
    spells[1] = "waterspout";
    spells[2] = "eatshit";

    inventory;
}

Player& Player::addItem(Item newItem) {
    inventory.addItem(newItem);

    return *this;
}