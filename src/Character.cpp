#include "Character.h"

Character::Character(void)
	:m_sceneId(NULL),
	 m_terrianId(NULL),
	 m_actorId(NULL),
	 m_dummyCameraId(NULL),
	 m_terrianRoomId(NULL),
	 m_curActionId(NULL),
	 m_isOnCameraFocus(false),
	 blood(100)
{
	m_meshFileName = "Lyubu2";
	this->setCharacterBlood(100, 100);
}

Character::~Character(void)
{
}


void Character::initialize(const SCENEid &sceneId, 
						   const OBJECTid &dummyCameraId, 
						   const ROOMid &terrianRoomId,
						   float *fDir, 
						   float *uDir, 
						   float *pos){ 
	// Since character size seems to be invisible from users, we had to set it ourselves.
	character_height = 120.0f;

	m_sceneId = sceneId;
	m_dummyCameraId = dummyCameraId;
	m_terrianRoomId = terrianRoomId;

	//load character
	FnScene scene(sceneId); 
	char *cstr = new char[m_meshFileName.length()+1];
	strcpy_s(cstr, m_meshFileName.length()+1, m_meshFileName.c_str());
	m_actorId =  scene.LoadCharacter(cstr);
	m_actor.ID(m_actorId);

	//put on terrian
	FnRoom room(terrianRoomId);
	room.AddObject(m_actorId);
	
	if(fDir == NULL){
		m_fDir3[0] = 1; m_fDir3[1] = 0; m_fDir3[2] = 0;
	}else{
		m_fDir3[0] = fDir[0]; m_fDir3[1] = fDir[1]; m_fDir3[2] = fDir[2];
	}

	if(uDir == NULL){
		 m_uDir3[0] = 0, m_uDir3[1] = 0; m_uDir3[2] = 1;
	}else{
		m_uDir3[0] = uDir[0], m_uDir3[1] = uDir[1]; m_uDir3[2] = uDir[2];
	}
	
	if(pos == NULL){
		m_fPos3[0] = 3569.0; m_fPos3[1] = -3208.0; m_fPos3[2] = 0;
	}else{
		m_fPos3[0] = pos[0]; m_fPos3[1] = pos[1]; m_fPos3[2] = pos[2];
	}
	
	m_actor.SetDirection(m_fDir3, m_uDir3);
	m_actor.SetTerrainRoom(terrianRoomId, 400.f);

	m_actor.PutOnTerrain(m_fPos3, 200);
	m_actor.SetPosition(m_fPos3);
	
	//set up action
	if(!m_meshFileName.compare("Lyubu2")){
		ACTIONid idleId = m_actor.GetBodyAction(NULL, "Idle");
		ACTIONid runId = m_actor.GetBodyAction(NULL, "Run");
		ACTIONid walkId = m_actor.GetBodyAction(NULL, "Walk");
		ACTIONid dieId = m_actor.GetBodyAction(NULL, "Die");
		ACTIONid damagedId = m_actor.GetBodyAction(NULL, "HeavyDamaged");
		ACTIONid attackId = m_actor.GetBodyAction(NULL, "NormalAttack1");

		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_IDLE, idleId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_RUN, runId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_WALK, walkId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_DIE, dieId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_ATTACK, attackId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_DAMAGED, damagedId));
	
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::IDLE, idleId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::DEAD, dieId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::COOL_DOWN, NULL));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::ATTACK, attackId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::DAMAGED, damagedId));

		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_BACKWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_FORWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_LEFT, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_LEFT_BACKWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_LEFT_FORWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_RIGHT, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_RIGHT_BACKWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_RIGHT_FORWARD, runId));
	
	}else if(!m_meshFileName.compare("Donzo2")){
		ACTIONid idleId = m_actor.GetBodyAction(NULL, "Idle");
		ACTIONid runId = m_actor.GetBodyAction(NULL, "Run");
		ACTIONid walkId = m_actor.GetBodyAction(NULL, "Walk");
		ACTIONid dieId = m_actor.GetBodyAction(NULL, "Die");
		ACTIONid attackId = m_actor.GetBodyAction(NULL, "Attack1");
		ACTIONid damagedId = m_actor.GetBodyAction(NULL, "DamageL");

		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_IDLE, idleId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_RUN, runId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_WALK, walkId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_DIE, dieId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_ATTACK, attackId));
		m_mapIndex2Action.insert(std::pair<ActionType, ACTIONid>(ACTION_DAMAGED, damagedId));
	
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::IDLE, idleId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::DEAD, dieId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::COOL_DOWN, NULL));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::ATTACK, attackId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::DAMAGED, damagedId));

		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_BACKWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_FORWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_LEFT, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_LEFT_BACKWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_LEFT_FORWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_RIGHT, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_RIGHT_BACKWARD, runId));
		m_mapState2Action.insert(std::pair<MotionState, ACTIONid>(MotionState::MOVE_RIGHT_FORWARD, runId));
	}else{
		return;
	}
	m_curActionId = m_mapIndex2Action[ACTION_IDLE];
	m_actor.SetCurrentAction(NULL, 0, m_curActionId);
	m_actor.Play(START, 0.0f, FALSE, TRUE);

	m_curState = MotionState::IDLE;

	m_rotateVel = 10;
	m_moveVel = 10;
}

int Character::update(int skip, MotionState newState){
	//detect keyevent
	int success = 0;

//	std::cout.flush();
	if(m_curState == MotionState::COOL_DOWN){
			m_coolDownCnt--;
			if(m_coolDownCnt < 0){
				newState = MotionState::IDLE;
			}else{
				newState = MotionState::COOL_DOWN;
			}
	}else if(m_curState == MotionState::DEAD){
		newState = MotionState::DEAD;
	}else{
		switch(newState){		//ensure state is one of defined state
		case (int)MotionState::IDLE:
		case (int)MotionState::MOVE_FORWARD:
		case (int)MotionState::MOVE_BACKWARD:
		case (int)MotionState::MOVE_LEFT_FORWARD:
		case (int)MotionState::MOVE_LEFT_BACKWARD:
		case (int)MotionState::MOVE_RIGHT_FORWARD:
		case (int)MotionState::MOVE_RIGHT_BACKWARD:
		case (int)MotionState::MOVE_LEFT:
		case (int)MotionState::MOVE_RIGHT:
		case (int)MotionState::ATTACK:
		case (int)MotionState::DAMAGED:
			break;
		default:
			newState = m_curState;
		}
	}

   //animation
	if(newState == (int)MotionState::COOL_DOWN){		//if is in cd, 
		m_actor.Play(LOOP, (float)skip, FALSE, TRUE);
	}else{
		if(m_mapState2Action[(MotionState)newState] != m_curActionId){		//action changed
			 m_curActionId = m_mapState2Action[(MotionState)newState];
			 m_actor.SetCurrentAction(NULL, 0, m_curActionId, 5.0f);
			 m_actor.Play(START, 0.0f, FALSE, TRUE);	  
		}else{													//action not change;
			if(m_curActionId == m_mapIndex2Action[ActionType::ACTION_DIE]){
				m_actor.Play(ONCE, (float)skip, FALSE, TRUE);
			}else{
				m_actor.Play(LOOP, (float)skip, FALSE, TRUE);
			}
		}
	}

	//check motion state
	FnObject dummy(m_dummyCameraId);
	float fDummyFDir[3];
	float fDummyUDir[3];
	float fDummyPos[3];
	float fDstDir[3];
	dummy.GetDirection(fDummyFDir, fDummyUDir);

	switch((MotionState)newState){
	case MotionState::IDLE:
	case MotionState::DEAD:
		break;
	case MotionState::ATTACK:
		 //do attack
		m_coolDownCnt = 15;		//enter into cd 
		newState = MotionState::COOL_DOWN;
		break;
	case MotionState::DAMAGED:
		m_coolDownCnt = 15;
		newState = MotionState::COOL_DOWN;
		break;
	case MotionState::MOVE_FORWARD:
	case MotionState::MOVE_BACKWARD:
	case MotionState::MOVE_LEFT_FORWARD:
	case MotionState::MOVE_LEFT_BACKWARD:
	case MotionState::MOVE_RIGHT_FORWARD:
	case MotionState::MOVE_RIGHT_BACKWARD:
		if(m_isOnCameraFocus){
			getDstDirection(fDummyFDir, fDummyUDir, fDstDir, (MotionState)newState);
			float fAngleDiff;
			getVectorAngle(m_fDir3, fDstDir, fAngleDiff);
			if(std::fabs(fAngleDiff) <= m_rotateVel){
				m_actor.TurnRight(fAngleDiff);
				//int success = m_actor.MoveForward(m_moveVel, TRUE, FALSE,  2, TRUE );
				success = m_actor.MoveForward(m_moveVel, TRUE, false, FALSE, TRUE);
			}else{
				float fSign = fAngleDiff/std::fabs(fAngleDiff);
				success = m_actor.TurnRight(fSign*m_rotateVel);
			}
		}
		break;
	case MotionState::MOVE_LEFT:
		if(m_isOnCameraFocus){
			float fAngleDiff;
			dummy.GetPosition(fDummyPos);
			getDstDirection(fDummyFDir, fDummyUDir, fDstDir, (MotionState)newState);
			getVectorAngle(m_fDir3, fDstDir, fAngleDiff);
			if(std::fabs(fAngleDiff) <= m_rotateVel){
				m_actor.TurnRight(fAngleDiff);
				float fDistance;
				getPositionDist2D(fDummyPos, m_fPos3, fDistance);
				double fHalfAngle = -asin(0.5*m_moveVel/fDistance)*180.0/3.14159265;
				m_actor.TurnRight(fHalfAngle);
				success = m_actor.MoveForward(m_moveVel, TRUE, false, FALSE, TRUE);

			//	dummy.TurnRight(2*fHalfAngle);
			}else{
				float fSign = fAngleDiff/std::fabs(fAngleDiff);
				success = m_actor.TurnRight(fSign*m_rotateVel);
			}
		}
		
		break;
	case MotionState::MOVE_RIGHT:
		if(m_isOnCameraFocus){
			float fAngleDiff;
			dummy.GetPosition(fDummyPos);
			getDstDirection(fDummyFDir, fDummyUDir, fDstDir, (MotionState)newState);
			getVectorAngle(m_fDir3, fDstDir, fAngleDiff);
			if(std::fabs(fAngleDiff) <= m_rotateVel){
				m_actor.TurnRight(fAngleDiff);
				float fDistance;
				getPositionDist2D(fDummyPos, m_fPos3, fDistance);
				double fHalfAngle = asin(0.5*m_moveVel/fDistance)*180/3.14159265;
				m_actor.TurnRight(fHalfAngle);
				success = m_actor.MoveForward(m_moveVel, TRUE, false, FALSE, TRUE);

			//	dummy.TurnRight(2*fHalfAngle);		
			}else{
				float fSign = fAngleDiff/std::fabs(fAngleDiff);
				success = m_actor.TurnRight(fSign*m_rotateVel);
			}
		}
		break;
	}

	//update state 
	m_curState = newState;
	m_actor.GetPosition(m_fPos3);
	m_actor.GetDirection(m_fDir3, m_uDir3);
	collision = success;
	return success;
}
