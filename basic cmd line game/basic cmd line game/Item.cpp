#include "Item.h"

Item::Item() {
    name = "???";
    description = "???";
}

Item::Item(const Item& item) {
    this->name = item.getName();
    this->description = item.getDescription();
}

Item::Item(String name, String description) {
    this->name = name;
    this->description = description;
}

//virtual ~Item() = default;

Item& Item::operator=(const Item& item) {
    this->name = item.getName();
    this->description = item.getDescription();

    return *this;
}

String& Item::getName() {
    return name;
}

const String& Item::getName() const {
    return name;
}

String& Item::getDescription() {
    return description;
}

const String& Item::getDescription() const {
    return description;
}
