#pragma once
#include "Item.h"

class ScrollItem : public Item {
private:
    SpellBase* spell;

public:
    ScrollItem();

    ScrollItem(String name, String description, SpellBase* spellPtr, SpellList& masterList);

    virtual String Description() override;

    String use(class Player& player) override;
};