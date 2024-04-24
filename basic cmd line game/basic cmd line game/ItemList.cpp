#include "ItemList.h"
#include <stdexcept>

ItemList::ItemList() {
    count = 0;
    items = nullptr;
}

ItemList::ItemList(int count, Item** items, ItemList& itemDatabase) {
    this->count = count;
    this->items = new Item*[count];
    for (int i = 0; i < count; i++) {
        this->items[i] = items[i];
        itemDatabase.addItem(items[i]);
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
    delete[] items;
}

ItemList& ItemList::operator=(const ItemList& itemList) {
    delete[] items;
    count = itemList.count;
    items = new Item*[itemList.count];
    for (int i = 0; i < itemList.count; i++) {
        items[i] = itemList.items[i];
    }

    return *this;
}

Item*& ItemList::operator[](int index) {
    if (index < 0 || index >= count) {
        throw std::out_of_range("ItemList array out of bounds");
    }

    return items[index];
}

int ItemList::getCount() {
    return count;
}

int ItemList::findItemIndex(const String& itemName) {
    int upperBound = getCount() - 1;
    int lowerBound = 0;
    int index;

    while (true) {
        index = ((upperBound - lowerBound) / 2) + lowerBound;

        if (itemName == items[index]->getName()) {
            return index;
        }

        if (upperBound <= lowerBound) {
            return -1;
        }

        if (itemName < items[index]->getName()) {
            upperBound = index - 1;
        }
        else {
            lowerBound = index + 1;
        }
    }
}

ItemList& ItemList::addItem(Item* item) {
    Item** oldPtr = items;

    count++;
    items = new Item*[count];
    for (int i = 0; i < count - 1; i++) {
        items[i] = oldPtr[i];
    }
    items[count - 1] = item;

    delete[] oldPtr;
    
    return *this;
}

ItemList& ItemList::addItem(Item* item, ItemList& itemDatabase) {
    addItem(item);
    itemDatabase.addItem(item);

    return *this;
}

ItemList& ItemList::removeItem(int index) {
    Item** oldPtr = items;

    count--;
    items = new Item*[count];
    for (int i = 0, j = 0; i < count; i++, j++) {
        if (i == index) {
            j++;
        }

        items[i] = oldPtr[j];
    }

    delete[] oldPtr;

    return *this;
}

ItemList& ItemList::insertItem(Item* item, int index) {
    Item** oldPtr = items;

    count++;
    items = new Item*[count];
    for (int i = 0, j = 0; i < count; i++, j++) {
        if (i == index) {
            j--;
            items[i] = item;
            continue;
        }

        items[i] = oldPtr[j];
    }

    delete[] oldPtr;

    return *this;
}