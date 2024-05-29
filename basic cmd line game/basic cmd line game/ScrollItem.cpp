#include "ScrollItem.h"
#include "Player.h"

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

String ScrollItem::Description() {
    return getDescription() + "\nThis item looks readable";
}

String ScrollItem::use(Player& player) {
    if (this->isConsumable()) {
        player.getInventory().removeItem(player.getInvIndex());
        if (player.getInvIndex() == player.getInventory().getCount()) {
            player.shiftInvIndex(-1);
        }
    }

    String spellName = spell->getName();
    player.getSpellBook().insertSpell(spell, player.getSpellBook().findSlotIndex(spell->getName()));
    return "You learned the " + spellName + " spell";
}