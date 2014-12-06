#pragma once

#include "Character.h"
#include <string>
class CharacterManageSystem
{
public:
	CharacterManageSystem(void);
	
	~CharacterManageSystem(void);

	void update(int skip);

	bool addCharacter(Character &character, bool isLocalPlayer = false);

	void removeCharacter(CHARACTERid characterId);

private:
	void updateCharacterInputs();

private:
	std::map<CHARACTERid, Character*> m_mapCharacterId2Character;
	std::map<CHARACTERid, MotionState> m_mapCharacterId2NewState;
	std::map<std::string, CHARACTERid> m_mapStrName2CharacterId; 

	CHARACTERid m_localPlayerId;
};

