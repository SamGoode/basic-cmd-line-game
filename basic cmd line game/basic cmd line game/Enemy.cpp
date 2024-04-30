#include "Enemy.h"

Enemy::Enemy() {
	name = "???";

	maxHealth = 0;
	health = maxHealth;

	maxMana = 0;
	mana = maxMana;
}

Enemy::Enemy(const Enemy& enemy) {
	name = enemy.name;

	maxHealth = enemy.maxHealth;
	health = enemy.health;

	maxMana = enemy.maxMana;
	mana = enemy.mana;

	damage = enemy.damage;
}

Enemy::Enemy(String name, int maxHealth, int maxMana, int damage) {
	this->name = name;

	this->maxHealth = maxHealth;
	health = maxHealth;

	this->maxMana = maxMana;
	mana = maxMana;

	this->damage = damage;
}

Enemy& Enemy::operator=(const Enemy& enemy) {
	name = enemy.name;

	maxHealth = enemy.maxHealth;
	health = enemy.health;

	maxMana = enemy.maxMana;
	mana = enemy.mana;

	damage = enemy.damage;

	return *this;
}

String& Enemy::getName() {
	return name;
}

String Enemy::getDescription() {
	return "Name: " + name + "\n\nHealth: " + toString(health) + "/" + toString(maxHealth) + "\nMana: " + toString(mana) + "/" + toString(maxMana);
}

int Enemy::getHealth() {
	return health;
}

int Enemy::setHealth(int amount) {
	health = amount;
	return health;
}

int Enemy::shiftHealth(int amount) {
	return setHealth(health + amount);
}