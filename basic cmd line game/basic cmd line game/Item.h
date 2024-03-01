#pragma once
#include "String.h"

class Item {
    private:
        String name;
        String description;

    public:
        Item();

        Item(const Item& item);

        Item(String name, String description);

        //virtual ~Item() = default;
        
        Item& operator=(const Item& item);

        String& getName();

        const String& getName() const;

        String& getDescription();

        const String& getDescription() const;
};