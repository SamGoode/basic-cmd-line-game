#include "UniqueSpells.h"
#include "Player.h"

TeleportSpell::TeleportSpell() {
	this->getName() = "Teleport";
	this->getDescription() = "Teleports the player to specified\ncoordinates.\nUsage: cast {x} {y}";
	this->setCost(5);
}

String TeleportSpell::cast(Player& player, int argCount, int* args) {
	if (this->getCost() > player.getMana()) {
		delete[] args;
		return "not enough mana";
	}
	
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
			player.shiftMana(-getCost());
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