#include "Spell.h"
#include "Player.h"

Spell::Spell() {
	name = "???";
	description = "???";
}

Spell::Spell(const Spell& spell) {
	name = spell.name;
	description = spell.description;
}

Spell::Spell(String name, String description) {
	this->name = name;
	this->description = description;
}

Spell& Spell::operator=(const Spell& spell) {
	name = spell.name;
	description = spell.description;

	return *this;
}

String& Spell::getName() {
	return name;
}

const String& Spell::getName() const {
	return name;
}

String& Spell::getDescription() {
	return description;
}

const String& Spell::getDescription() const {
	return description;
}

String Spell::use(Player& player) {
	return "I didn't do anything";
}

String Spell::use(Player& player, int arg, ...) {
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

String TeleportSpell::use(Player& player, int arg, ...) {
	player.x = *((int*)&arg);
	player.y = *((int*)&arg + 2);

	return "teleported player to " + toString(player.x - 2) + ", " + toString(player.y - 2);
}