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

        String& getName();

        String& getDescription();

        const String& getDescription() const;

        Item& operator=(const Item& item);
};