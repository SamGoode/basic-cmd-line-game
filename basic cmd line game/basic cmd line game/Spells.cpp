#include "Spells.h"
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

String SpellBase::cast(Player& player, int argCount, int* args) {
	if (argCount > 0) {
		delete[] args;
		return "too many arguments";
	}
	
	return "I didn't do anything";
}

TeleportSpell::TeleportSpell() {
	this->getName() = "???";
	this->getDescription() = "???";
}

TeleportSpell::TeleportSpell(String name, String description) {
	this->getName() = name;
	this->getDescription() = description;
}

String TeleportSpell::cast(Player& player, int argCount, int* args) {
	if (argCount < 2) {
		delete[] args;
		return "not enough arguments";
	}
	else if (argCount > 2) {
		delete[] args;
		return "too many arguments";
	}

	int destX = args[0] + 2;
	int destY = args[1] + 2;
	delete[] args;

	if (destX < 0 || destX > 4 || destY < 0 || destY > 4) {
		return toString(destX - 2) + ", " + toString(destY - 2) + " is outside of the map";
	}

	switch (player.setPos(destX, destY)) {
		case 0:
			return "teleported player to " + toString(destX - 2) + ", " + toString(destY - 2);
			break;
		case 1:
			return toString(destX - 2) + ", " + toString(destY - 2) + " is outside of the map";
			break;
		case 2:
			return "there is no room at " + toString(destX - 2) + ", " + toString(destY - 2);
			break;
	}

	return "this will never happen";
}