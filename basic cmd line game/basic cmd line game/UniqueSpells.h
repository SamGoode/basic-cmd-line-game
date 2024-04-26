#pragma once
#include "SpellBase.h"

class TeleportSpell : public SpellBase {
	public:
		TeleportSpell();

		String cast(class Player& player, int argCount, int* args) override;
};