#pragma once
#include "FlyWin32.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Character.h"

class FightSystem {
	public:
		FightSystem(void);
		~FightSystem(void);

		void initialize(Character **character_list, int character_list_size);

		void judgeAttack(Character *character);

	private:

		Character **character_list;
		int character_list_size;
};

