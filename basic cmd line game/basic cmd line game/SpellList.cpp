#include "SpellList.h"
#include <stdexcept>

SpellList::SpellList() {
	count = 0;
	spells = nullptr;
}

SpellList::SpellList(int count, SpellBase** spells, SpellList& masterList) {
	this->count = count;
	this->spells = new SpellBase * [count];
	for (int i = 0; i < count; i++) {
		this->spells[i] = spells[i];
		masterList.addSpell(spells[i]);
	}

	delete[] spells;
}

SpellList::SpellList(const SpellList& spellList) {
	count = spellList.count;
	spells = new SpellBase*[spellList.count];
	for (int i = 0; i < spellList.count; i++) {
		spells[i] = spellList.spells[i];
	}
}

SpellList::~SpellList() {
	delete[] spells;
}

SpellList& SpellList::operator=(const SpellList& spellList) {
	delete[] spells;
	count = spellList.count;
	spells = new SpellBase*[spellList.count];
    for (int i = 0; i < spellList.count; i++) {
        spells[i] = spellList.spells[i];
    }

    return *this;
}

SpellBase*& SpellList::operator[](int index) {
	if (index < 0 || index >= count) {
		throw std::out_of_range("index out of bounds of SpellList");
	}

	return spells[index];
}

int SpellList::getCount() {
	return count;
}

int SpellList::findSpellIndex(String spellName) {
    int upperBound = getCount() - 1;
    int lowerBound = 0;
    int index;

    spellName.ToLower();
    //holds lower case copies
    String lcName;

    while (true) {
        // (u - l)/2 + l can be simplified to (u + l)/2
        index = (upperBound + lowerBound) / 2;

        lcName = spells[index]->getName();
        lcName.ToLower();

        if (spellName == lcName) {
            return index;
        }

        if (upperBound <= lowerBound) {
            return -1;
        }

        if (spellName < lcName) {
            upperBound = index - 1;
        }
        else {
            lowerBound = index + 1;
        }
    }
}

int SpellList::findSlotIndex(String spellName) {
    int upperBound = getCount() - 1;
    int lowerBound = 0;
    int index;

    spellName.ToLower();
    //holds lower case copies
    String lcName;

    while (true) {
        // (u - l)/2 + l can be simplified to (u + l)/2
        index = (upperBound + lowerBound) / 2;

        lcName = spells[index]->getName();
        lcName.ToLower();

        if (upperBound <= lowerBound) {
            if (spellName < lcName) {
                return index;
            }

            return index + 1;
        }

        if (spellName < lcName) {
            upperBound = index - 1;
        }
        else {
            lowerBound = index + 1;
        }
    }
}

SpellList& SpellList::addSpell(SpellBase* spell) {
    SpellBase** oldPtr = spells;

    count++;
    spells = new SpellBase*[count];
    for (int i = 0; i < count - 1; i++) {
        spells[i] = oldPtr[i];
    }
    spells[count - 1] = spell;

    delete[] oldPtr;

    return *this;
}

SpellList& SpellList::addSpell(SpellBase* spell, SpellList& masterList) {
    addSpell(spell);
    masterList.addSpell(spell);

    return *this;
}

SpellList& SpellList::removeSpell(int index) {
    SpellBase** oldPtr = spells;

    count--;
    spells = new SpellBase*[count];
    for (int i = 0, j = 0; i < count; i++, j++) {
        if (i == index) {
            j++;
        }

        spells[i] = oldPtr[j];
    }

    delete[] oldPtr;

    return *this;
}

SpellList& SpellList::insertSpell(SpellBase* spell, int index) {
    SpellBase** oldPtr = spells;

    count++;
    spells = new SpellBase*[count];
    for (int i = 0, j = 0; i < count; i++, j++) {
        if (i == index) {
            j--;
            spells[i] = spell;
            continue;
        }

        spells[i] = oldPtr[j];
    }

    delete[] oldPtr;

    return *this;
}