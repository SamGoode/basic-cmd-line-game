#include "Item.h"
#include "Player.h"

Item::Item() {
    name = "???";
    description = "???";
}

Item::Item(const Item& item) {
    name = item.getName();
    description = item.getDescription();
}

Item::Item(String name, String description) {
    this->name = name;
    this->description = description;
}

//virtual ~Item() = default;

Item& Item::operator=(const Item& item) {
    name = item.getName();
    description = item.getDescription();

    return *this;
}

String& Item::getName() {
    return name;
}

const String& Item::getName() const {
    return name;
}

String& Item::getDescription() {
    return description;
}

const String& Item::getDescription() const {
    return description;
}

String Item::use(Player& player) {
    return "I didn't do anything";
}

FoodItem::FoodItem() {
    this->getName() = "???";
    this->getDescription() = "???";
    healAmount = 0;
}

FoodItem::FoodItem(String name, String description, int healAmount) {
    this->getName() = name;
    this->getDescription() = description;
    this->healAmount = healAmount;
}

String FoodItem::use(Player& player) {
    player.shiftHealth(healAmount);
    return "healed player for " + toString(healAmount) + " hp";
}
