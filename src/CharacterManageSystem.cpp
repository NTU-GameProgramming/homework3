#include "CharacterManageSystem.h"


CharacterManageSystem::CharacterManageSystem(void)
	:m_localPlayerId(NULL)
{
}


CharacterManageSystem::~CharacterManageSystem(void)
{
}

bool CharacterManageSystem::addCharacter(Character &character, bool isLocalPlayer){
	CHARACTERid  characterId = character.getCharacterId();
	Character *pCharacter = &character;
	if(characterId == NULL){
		return true;
	}
	m_mapCharacterId2Character.insert(std::pair<CHARACTERid, Character*>(characterId, pCharacter));
	m_mapCharacterId2NewState.insert(std::pair<CHARACTERid, MotionState>(characterId, MotionState::IDLE));	
	m_mapStrName2CharacterId.insert(std::pair<std::string, CHARACTERid>(character.getCharacterName(), characterId));
	if(isLocalPlayer){	
		m_localPlayerId = characterId;
	}
	return false;
}

void CharacterManageSystem::updateCharacterInputs(){
	//for local player
   	int newState = 0;
	if(FyCheckHotKeyStatus(FY_UP)){
		newState = newState|MOVE_FORWARD;
		std::cout<<"up key\n";
	}												  
	if(FyCheckHotKeyStatus(FY_DOWN)){
		newState = newState|MOVE_BACKWARD;
		std::cout<<"down key\n";
	}
	if(FyCheckHotKeyStatus(FY_LEFT)){
		newState = newState|MOVE_LEFT;
		std::cout<<"left key\n";
	}
	if(FyCheckHotKeyStatus(FY_RIGHT)){
		newState = newState|MOVE_RIGHT;
		std::cout<<"right key\n";
	}
	if(FyCheckHotKeyStatus(FY_F)){
		newState = ATTACK;			//player can not move while attacking
		std::cout<<"attak key\n";
	}

	m_mapCharacterId2NewState[m_localPlayerId] = (MotionState)newState;

	//update other charcter's input state
	m_mapCharacterId2NewState[m_mapStrName2CharacterId["Donzo2"]] = MotionState::IDLE;
}

void CharacterManageSystem::update(int skip){
	updateCharacterInputs();

	//update date character's animation and motion
	{
		std::map<CHARACTERid, Character*>::iterator chrIter = m_mapCharacterId2Character.begin();
		for(; chrIter != m_mapCharacterId2Character.end(); ++chrIter){
			(chrIter->second)->update(skip, m_mapCharacterId2NewState[(chrIter->first)]);
		}
	}

	//check attack
	{
//		(m_mapCharacterId2Character[m_mapStrName2CharacterId["Donzo2"] ])->modifyChrBlood(-1);	   //used to test die
		std::map<CHARACTERid, MotionState>::iterator chrIter = m_mapCharacterId2NewState.begin();
		for(;chrIter != m_mapCharacterId2NewState.end(); ++chrIter){
			if(chrIter->second == MotionState::ATTACK){
				//trigger fight system
				
			}
		}
	}
}
