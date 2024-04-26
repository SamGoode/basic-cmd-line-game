#include "SpellBase.h"
#include "Player.h"

SpellBase::SpellBase() {
	name = "???";
	description = "???";
	cost = 0;
	damage = 0;
}

SpellBase::SpellBase(const SpellBase& spell) {
	name = spell.name;
	description = spell.description;
	cost = spell.cost;
	damage = spell.damage;
}

SpellBase::SpellBase(String name, String description) {
	this->name = name;
	this->description = description;
	cost = 0;
	damage = 0;
}

SpellBase::SpellBase(String name, String description, int cost, int damage) {
	this->name = name;
	this->description = description;
	this->cost = cost;
	this->damage = damage;
}

SpellBase& SpellBase::operator=(const SpellBase& spell) {
	name = spell.name;
	description = spell.description;
	cost = spell.cost;
	damage = spell.damage;

	return *this;
}

String& SpellBase::getName() {
	return name;
}

const String& SpellBase::getName() const {
	return name;
}

String& SpellBase::getDescription() {
	return description;
}

const String& SpellBase::getDescription() const {
	return description;
}

int SpellBase::getCost() {
	return cost;
}

SpellBase& SpellBase::setCost(int amount) {
	cost = amount;
	return *this;
}

int SpellBase::getDamage() {
	return damage;
}

SpellBase& SpellBase::setDamage(int amount) {
	damage = amount;
	return *this;
}

String SpellBase::cast(Player& player, int argCount, int* args) {
	if (cost > player.getMana()) {
		delete[] args;
		return "not enough mana";
	}
	
	if (argCount > 0) {
		delete[] args;
		return "too many arguments";
	}

	return "I didn't do anything";
}