#include "Item.h"
#include "Player.h"

Item::Item() {
    name = "???";
    description = "???";
    consumable = false;
}

Item::Item(const Item& item) {
    name = item.name;
    description = item.description;
    consumable = item.consumable;
}

Item::Item(String name, String description) {
    this->name = name;
    this->description = description;
    consumable = false;
}

//virtual ~Item() = default;

Item& Item::operator=(const Item& item) {
    name = item.getName();
    description = item.getDescription();

    return *this;
}

Item& Item::setName(String name) {
    this->name = name;

    return *this;
}

const String& Item::getName() const {
    return name;
}

Item& Item::setDescription(String description) {
    this->description = description;
    
    return *this;
}

const String& Item::getDescription() const {
    return description;
}

String Item::Description() {
    return description + "\nThis item looks like your run of the\nmill item";
}

bool Item::isConsumable() {
    return consumable;
}

void Item::setConsumable(bool isConsumable) {
    consumable = isConsumable;
}

String Item::use(Player& player) {
    if (consumable) {
        player.getInventory().removeItem(player.getInvIndex());
        if (player.getInvIndex() == player.getInventory().getCount()) {
            player.shiftInvIndex(-1);
        }
    }

    return "I didn't do anything";
}