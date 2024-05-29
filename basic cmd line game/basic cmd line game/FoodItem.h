#pragma once
#include "Item.h"

class FoodItem : public Item {
private:
    int healAmount;

public:
    FoodItem();

    FoodItem(String name, String description, int healAmount);

    virtual String Description() override;

    String use(class Player& player) override;
};