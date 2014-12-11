#pragma once
#include "FlyWin32.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Character.h"
class CharacterManageSystem;

class FightSystem {
	public:
		FightSystem(void);
		~FightSystem(void);

		void initialize(CharacterManageSystem *cms, std::map<CHARACTERid, Character*> *id2character);

		void judgeAttack(CHARACTERid attackerid);

	private:
		CharacterManageSystem *cms;
		std::map<CHARACTERid, Character*> *id2character;
		float attack_radius;
		float attack_angle_cos;
};

