#pragma once
#include "String.h"

class Item {
    private:
        String name;
        String description;
        bool stacks;
        int amount;
    public:
        Item();

        Item(const Item& item);

        Item(String name, String description);

        Item(String name, String description, bool stacks, int amount);

        //virtual ~Item() = default;
        
        Item& operator=(const Item& item);

        String& getName();

        const String& getName() const;

        String& getDescription();

        const String& getDescription() const;
};