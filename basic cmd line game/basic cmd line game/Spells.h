#pragma once
#include "String.h"

class SpellBase {
	private:
		String name;
		String description;

	public:
		SpellBase();

		SpellBase(const SpellBase& spell);

		SpellBase(String name, String description);

		virtual ~SpellBase() = default;

		SpellBase& operator=(const SpellBase& spell);

		String& getName();

		const String& getName() const;

		String& getDescription();

		const String& getDescription() const;

		virtual String cast(class Player& player, int arg, ...);
};

class TeleportSpell : public SpellBase {
	public:
		TeleportSpell();

		TeleportSpell(String name, String description);

		String cast(class Player& player, int arg, ...) override;
};