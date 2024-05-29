#pragma once
#include "String.h"
#include "SpellList.h"

class Item {
    private:
        String name;
        String description;
        bool consumable;
        //bool stackable;
        //int amount;

    public:
        Item();

        Item(const Item& item);

        Item(String name, String description);

        //Item(String name, String description, bool stacks, int amount);

        virtual ~Item() = default;

        Item& operator=(const Item& item);

        Item& setName(String name);

        const String& getName() const;

        Item& setDescription(String description);

        const String& getDescription() const;

        virtual String Description();

        bool isConsumable();

        void setConsumable(bool isConsumable);

        virtual String use(class Player& player);
};

