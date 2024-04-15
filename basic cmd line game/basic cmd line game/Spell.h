#pragma once
#include "String.h"

class Spell {
	private:
		String name;
		String description;

	public:
		Spell();

		Spell(const Spell& spell);

		Spell(String name, String description);

		virtual ~Spell() = default;

		Spell& operator=(const Spell& spell);

		String& getName();

		const String& getName() const;

		String& getDescription();

		const String& getDescription() const;

		virtual String use(class Player& player);

		virtual String use(class Player& player, int arg, ...);
};

class TeleportSpell : public Spell {
	public:
		TeleportSpell();

		TeleportSpell(String name, String description);

		String use(class Player& player, int arg, ...) override;
};