#include "Spells.h"
#include "Player.h"

SpellBase::SpellBase() {
	name = "???";
	description = "???";
}

SpellBase::SpellBase(const SpellBase& spell) {
	name = spell.name;
	description = spell.description;
}

SpellBase::SpellBase(String name, String description) {
	this->name = name;
	this->description = description;
}

SpellBase& SpellBase::operator=(const SpellBase& spell) {
	name = spell.name;
	description = spell.description;

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

String SpellBase::cast(Player& player, int arg, ...) {
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

String TeleportSpell::cast(Player& player, int arg, ...) {
	player.x = *((int*)&arg);
	player.y = *((int*)&arg + 2);

	return "teleported player to " + toString(player.x - 2) + ", " + toString(player.y - 2);
}