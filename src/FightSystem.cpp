#include "FightSystem.h"
#include "CharacterManageSystem.h"
#include <math.h>
FightSystem::FightSystem(void) {
}
FightSystem::~FightSystem(void) {
}

void FightSystem::initialize(CharacterManageSystem *cms, std::map<CHARACTERid, Character*> *id2character) {
	this->cms = cms;
	this->id2character = id2character;
	this->attack_radius = 200.0f;
	this->attack_angle_cos = cos(30.0f);
}

void FightSystem::judgeAttack(CHARACTERid attackerid) {
	std::map<CHARACTERid, Character*>::iterator iter;
	float attacker_fdir[3], attacker_pos[3], enemy_pos[3], displacement[4];
	float angle_cos;
	FnCharacter attacker, enemy;
	attacker.ID(attackerid);
	attacker.GetDirection(attacker_fdir, NULL);
	attacker.GetPosition(attacker_pos);
	for(iter = id2character->begin() ; iter != id2character->end() ; ++iter) {
		if(iter->first != attackerid) { // test attack if target is not itself
			float damage = 0;
			enemy.ID(iter->first);
			enemy.GetPosition(enemy_pos);
			displacement[0] = enemy_pos[0] - attacker_pos[0];
			displacement[1] = enemy_pos[1] - attacker_pos[1];
			displacement[2] = enemy_pos[2] - attacker_pos[2];
			displacement[3] = pow(pow(displacement[0], 2.0f) + pow(displacement[1], 2.0f) + pow(displacement[2], 2.0f), 0.5f);

			if (displacement[3] <= this->attack_radius) {
				angle_cos = (displacement[0] * attacker_fdir[0] +  displacement[1] * attacker_fdir[1] +  displacement[2] * attacker_fdir[2]) / displacement[3];
				if(angle_cos >= this->attack_angle_cos) {
					damage = 10.0f * angle_cos;
					cms->gotAttacked(iter->first, damage);
				}
			}
		}
	}
}
