#pragma once
#include "String.h"

class Enemy {
	private:
		String name;

		int maxHealth;
		int health;

		int maxMana;
		int mana;

		int damage;

	public:
		Enemy();

		Enemy(const Enemy& enemy);

		Enemy(String name, int maxHealth, int maxMana, int damage);

		Enemy& operator=(const Enemy& enemy);

		String& getName();

		String getDescription();

		int getHealth();
		int setHealth(int amount);
		int shiftHealth(int amount);
};