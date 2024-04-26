#pragma once
#include "String.h"

class SpellBase {
	private:
		String name;
		String description;
		int cost;
		int damage;

	public:
		SpellBase();

		SpellBase(const SpellBase& spell);

		SpellBase(String name, String description);

		SpellBase(String name, String description, int cost, int damage);

		virtual ~SpellBase() = default;

		SpellBase& operator=(const SpellBase& spell);

		String& getName();
		const String& getName() const;

		String& getDescription();
		const String& getDescription() const;

		int getCost();
		SpellBase& setCost(int amount);

		int getDamage();
		SpellBase& setDamage(int amount);

		virtual String cast(class Player& player, int argCount, int* args);
};

class TeleportSpell : public SpellBase {
	public:
		TeleportSpell();

		TeleportSpell(String name, String description);

		String cast(class Player& player, int argCount, int* args) override;
};