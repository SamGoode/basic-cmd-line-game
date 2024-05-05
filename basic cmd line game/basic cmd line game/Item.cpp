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

bool Item::isConsumable() {
    return consumable;
}

void Item::setConsumable(bool isConsumable) {
    consumable = isConsumable;
}

String Item::use(Player& player) {
    if (consumable) {
        player.getInventory().removeItem(player.getInvIndex());
    }

    return "I didn't do anything";
}

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

String FoodItem::use(Player& player) {
    if (this->isConsumable()) {
        player.getInventory().removeItem(player.getInvIndex());
    }
    
    player.shiftHealth(healAmount);
    return "healed player for " + toString(healAmount) + " hp";
}

ScrollItem::ScrollItem() {
    this->setName("???");
    this->setDescription("???");
    this->setConsumable(true);

    spell = nullptr;
}

ScrollItem::ScrollItem(String name, String description, SpellBase* spell, SpellList& masterList) {
    this->setName(name);
    this->setDescription(description);
    this->setConsumable(true);

    masterList.addSpell(spell);
    this->spell = spell;
}

String ScrollItem::use(Player& player) {
    if (this->isConsumable()) {
        player.getInventory().removeItem(player.getInvIndex());
    }

    String spellName = spell->getName();
    player.getSpellBook().insertSpell(spell, player.getSpellBook().findSlotIndex(spell->getName()));
    return "player gained " + spellName + " spell";
}