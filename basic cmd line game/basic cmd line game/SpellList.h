#pragma once
#include "SpellBase.h"
#include "UniqueSpells.h"

class SpellList {
	private:
		int count;
		SpellBase** spells;

	public:
		SpellList();

		SpellList(int count, SpellBase** spells, SpellList& masterList);

		SpellList(const SpellList& spellList);

		~SpellList();

		SpellList& operator=(const SpellList& spellList);

		SpellBase*& operator[](int index);

		int getCount();

		int findSpellIndex(String spellName);
		int findSlotIndex(String spellName);

		SpellList& addSpell(SpellBase* spell);
		SpellList& addSpell(SpellBase* spell, SpellList& masterList);

		SpellList& removeSpell(int index);

		SpellList& insertSpell(SpellBase* spell, int index);
};