#include "FoodItem.h"
#include "Player.h"

FoodItem::FoodItem() {
    this->setName("???");
    this->setDescription("???");
    this->setConsumable(true);

    healAmount = 0;
}

FoodItem::FoodItem(String name, String description, int healAmount) {
    this->setName(name);
    this->setDescription(description);
    this->setConsumable(true);

    this->healAmount = healAmount;
}

String FoodItem::Description() {
    return getDescription() + "\nThis item looks edible";
}

String FoodItem::use(Player& player) {
    if (this->isConsumable()) {
        player.getInventory().removeItem(player.getInvIndex());
        if (player.getInvIndex() == player.getInventory().getCount()) {
            player.shiftInvIndex(-1);
        }
    }

    player.shiftHealth(healAmount);
    return "You ate the " + this->getName() + " and healed " + toString(healAmount) + " hp";
}