#include "Item.h"

Item::Item() {
    name = "???";
    description = "???";
}

Item::Item(const Item& item) {
    this->name = item.name;
    this->description = item.description;
}

Item::Item(String name, String description) {
    this->name = name;
    this->description = description;
}

//virtual ~Item() = default;

String& Item::getName() {
    return name;
}

String& Item::getDescription() {
    return description;
}

const String& Item::getDescription() const {
    return description;
}

Item& Item::operator=(const Item& item) {
    this->name = item.name;
    this->description = item.description;

    return *this;
}    