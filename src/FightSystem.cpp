#include "FightSystem.h"

FightSystem::FightSystem(void) {
}
FightSystem::~FightSystem(void) {
}

void FightSystem::initialize(Character **character_list, int character_list_size) {
	this->character_list = character_list;
	this->character_list_size = character_list_size;
}

void FightSystem::judgeAttack(Character *attacker) {
	for(int i=0; i<character_list_size; ++i) {
		if(character_list[i] != attacker) { // test attack if target is not itself
			
		}
	}
}
