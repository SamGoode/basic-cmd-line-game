#include "ItemList.h"

ItemList::ItemList() {
    count = 0;
    items = nullptr;
}

ItemList::ItemList(size_t count, Item** items) {
    this->count = count;
    this->items = new Item*[count];
    for (int i = 0; i < count; i++) {
        this->items[i] = items[i];
    }

    delete[] items;
}

ItemList::ItemList(const ItemList& itemList) {
    count = itemList.count;
    items = new Item*[itemList.count];
    for (int i = 0; i < itemList.count; i++) {
        items[i] = itemList.items[i];
    }
}

ItemList::~ItemList() {
    for (int i = 0; i < count; i++) {
        delete items[i];
    }
    delete[] items;
}

ItemList& ItemList::operator=(const ItemList& itemList) {
    count = itemList.count;
    items = new Item*[itemList.count];
    for (int i = 0; i < itemList.count; i++) {
        items[i] = itemList.items[i];
    }

    return *this;
}

Item*& ItemList::operator[](size_t index) {
    return items[index];
}

size_t ItemList::getCount() {
    return count;
}

ItemList& ItemList::addItem(Item* item) {
    Item** oldPtr = items;

    count++;
    items = new Item*[count];
    for (int i = 0; i < count - 1; i++) {
        items[i] = new Item;
        *items[i] = *oldPtr[i];
    }
    //items[count - 1] = new Item;
    items[count - 1] = item;

    //delete item;

    
    return *this;
}