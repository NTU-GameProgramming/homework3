#pragma once
#include <FlyWin32.h>
#include <map>
#include <iostream>
#include <math.h>
#include <string>

enum MotionState{
	//live status
	IDLE = 0,
	DEAD = 1,
	
	//attack related status
	ATTACK = 2,
	DAMAGED = 3,
	COOL_DOWN = 4,

	//moving  start from 256
	MOVE_FORWARD = 1<<8,
	MOVE_BACKWARD = MOVE_FORWARD<<1,
	MOVE_LEFT = MOVE_BACKWARD<<2,
	MOVE_RIGHT = MOVE_LEFT<<3,
	MOVE_LEFT_FORWARD = MOVE_LEFT + MOVE_FORWARD,
	MOVE_LEFT_BACKWARD = MOVE_LEFT+ MOVE_BACKWARD,
	MOVE_RIGHT_FORWARD = MOVE_RIGHT + MOVE_FORWARD,
	MOVE_RIGHT_BACKWARD = MOVE_RIGHT + MOVE_BACKWARD
};



enum ActionType{
	ACTION_IDLE = 0,
	ACTION_RUN = 1,
	ACTION_WALK = 2,
	ACTION_DIE = 3,
	ACTION_ATTACK = 4,
	ACTION_DAMAGED = 5
};


class GameObject{
public:
	GameObject(){};

	 void getLeftVertDir(float *srcFDir, float *srcUDir, float *dstDir){
		FyCross(dstDir, srcUDir, srcFDir);
		normalizeVector(dstDir, 3);
	 }

	 void getRightVertDir(float *srcFDir, float *srcUDir, float *dstDir){
		FyCross(dstDir, srcFDir, srcUDir);
		normalizeVector(dstDir, 3);
	 }

	 void normalizeVector(float *vec, int size){
		float fSquareSum = 0;
		for(int i = 0; i < size; ++i){
		fSquareSum += vec[i]*vec[i];
		}
		fSquareSum = std::sqrt(fSquareSum);
			 
		for(int i = 0; i < size; ++i){
		vec[i] = vec[i]/fSquareSum;
		}
	 } 

	 void getPositionDist2D(float *vec1, float *vec2, float &dst){
		 float fDiff[2];
		 fDiff[0] = vec1[0] - vec2[0];
		 fDiff[1] = vec1[1] - vec2[1];
		float fSquareDst = fDiff[0]*fDiff[0] + fDiff[1]*fDiff[1];
		dst = std::sqrt(fSquareDst);
	 }

	 void getDstDirection(float *srcFDir, float *srcUDir, float *dstDir, MotionState state){ //得到目標位置的向量
		  float leftDir[3];
		  float rightDir[3];
		 switch(state){
		case MotionState::MOVE_FORWARD:
			dstDir[0] = srcFDir[0]; dstDir[1] = srcFDir[1]; dstDir[2] = srcFDir[2];
			break;
		case MotionState::MOVE_BACKWARD:
			dstDir[0] = -srcFDir[0]; dstDir[1] = -srcFDir[1]; dstDir[2] = -srcFDir[2];
			break;
		case MotionState::MOVE_LEFT:
			getLeftVertDir(srcFDir, srcUDir, dstDir);
			break;
		case MotionState::MOVE_LEFT_FORWARD:
			
			getLeftVertDir(srcFDir, srcUDir,leftDir);
			dstDir[0] = leftDir[0] + srcFDir[0];
			dstDir[1] = leftDir[1] + srcFDir[1];
			dstDir[2] = leftDir[2] + srcFDir[2];
			normalizeVector(dstDir, 3);
			break;
		case MotionState::MOVE_LEFT_BACKWARD:
			getLeftVertDir(srcFDir, srcUDir,leftDir);
			dstDir[0] = leftDir[0] - srcFDir[0];
			dstDir[1] = leftDir[1] - srcFDir[1];
			dstDir[2] = leftDir[2] - srcFDir[2];
			normalizeVector(dstDir, 3);
			break;
		case MotionState::MOVE_RIGHT:
			getRightVertDir(srcFDir, srcUDir, dstDir);
			break;
		case MotionState::MOVE_RIGHT_FORWARD:
			getRightVertDir(srcFDir, srcUDir, rightDir);
			dstDir[0] = rightDir[0] + srcFDir[0];
			dstDir[1] = rightDir[1] + srcFDir[1];
			dstDir[2] = rightDir[2] + srcFDir[2];
			normalizeVector(dstDir, 3);
			break;
		case MotionState::MOVE_RIGHT_BACKWARD:
			getRightVertDir(srcFDir, srcUDir, rightDir);
			dstDir[0] = rightDir[0] - srcFDir[0];
			dstDir[1] = rightDir[1] - srcFDir[1];
			dstDir[2] = rightDir[2] - srcFDir[2];
			normalizeVector(dstDir, 3);
			break;
		default:
			dstDir[0] = 0, dstDir[1], dstDir[2] = 0;
		}
	 }

	 void getVectorAngle(float *vec1, float *vec2, float &angle){
		float fDotProduct = vec1[0]*vec2[0] + vec1[1]*vec2[1] + vec1[2]*vec2[2] ;
		float fNorm = std::sqrt(vec1[0]*vec1[0] + vec1[1]*vec1[1] + vec1[2]*vec1[2])* 
			std::sqrt(vec2[0]*vec2[0] + vec2[1]*vec2[1] + vec2[2]*vec2[2]);
		float cosValue = fDotProduct/fNorm;
		if(cosValue > 1){
			cosValue = 1;
		}else if(cosValue < -1){
			cosValue = -1;
		}
		angle = 180.0*std::acos(cosValue)/3.14159265;

		float fVertVector[3];
		FyCross(fVertVector, vec1, vec2);
		if(fVertVector[2] > 0){
			angle = -angle;
		}
	 }
};

class Blood{
public:
	Blood()
		:	m_bloodCnt(1),
			m_maxBlood(1){};

	Blood(int maxBlood, int curBlood)
		:	m_maxBlood(maxBlood),
			m_bloodCnt(curBlood){};

	void modifyBlood(int bloodDiff){
		 m_bloodCnt = m_bloodCnt + bloodDiff;
		 if(m_bloodCnt > m_maxBlood){
			m_bloodCnt = m_maxBlood;
		 }

		 if(m_bloodCnt < 0){
			 m_bloodCnt = 0;
		 }
	}

	void setBlood(int blood){
		m_bloodCnt = blood;
	}

	void setMaxBlood(int blood){
		m_maxBlood = blood;
	}

	void resetCounter(){
		m_bloodCnt = m_maxBlood;
	}

	int getBlood(){
		return m_bloodCnt;
	}

	int getMaxBlood(){
		return m_maxBlood;
	}

	Blood& operator=(const Blood &other){
		if(this != &other){
			this->m_maxBlood = other.m_maxBlood;
			this->m_bloodCnt = other.m_bloodCnt;
		}
		return *this;
	}

private:
	int m_maxBlood;
	int m_bloodCnt;
};

class Character
	:public GameObject
{
public:
	Character(void);

	~Character(void);

	void initialize(const SCENEid &sceneId, 
					const OBJECTid &dummyCameraId, 
					const ROOMid &terrianRoomId,
					float *fDir = NULL, 
					float *uDir = NULL, 
					float *pos = NULL);  //dummyCameraId 輸入camera的ID
	
	int update(int skip, MotionState newState); //在gameAI時，更新人物動作 return 是否碰撞

	//setter and getter
	void setBaseCameraId(OBJECTid baseCameraId) {
		this->m_dummyCameraId = baseCameraId;
		this->m_isOnCameraFocus = true;
	}

	void setMeshFileName(std::string meshFileName){
		m_meshFileName = meshFileName;
	}

	void setCharacterName(std::string name){
		m_characterName = name;
	}

	std::string getCharacterName(){
		return m_characterName;
	}

	CHARACTERid getCharacterId(){
		return m_actorId;
	}

	MotionState getCurrentState() {
		return m_curState;
	}

	float getCharacterHeight() {
		return character_height;
	}

	FnCharacter* getController() {
		return &m_actor;
	}

	Character& operator=(const Character &other){
	   if(this != &other){
		   this->m_sceneId = other.m_sceneId;
		   this->m_terrianId = other.m_terrianId;
		   this->m_actorId = other.m_actorId;
		   this->m_dummyCameraId = other.m_dummyCameraId;
		   this->m_terrianRoomId = other.m_terrianRoomId;

		   this->m_meshFileName = other.m_meshFileName;
		   this->m_characterName = other.m_characterName;
		   for(int i = 0; i < 3; ++i){
			   this->m_fDir3[i] = other.m_fDir3[i];
			   this->m_uDir3[i] = other.m_uDir3[i];
			   this->m_fPos3[i] = other.m_fPos3[i];
			   
		   }
		   this->m_moveVel = other.m_moveVel;
		   this->m_rotateVel = other.m_rotateVel;
		   this->m_curState = other.m_curState;
		   this->m_curActionId = other.m_curActionId;
		   this->m_coolDownCnt = other.m_coolDownCnt;
		   this->m_isOnCameraFocus = other.m_isOnCameraFocus;
		   this->m_curActionId = other.m_curActionId;
		   this->m_mapState2Action = other.m_mapState2Action;
		   this->m_mapIndex2Action = other.m_mapIndex2Action;
		   this->character_height = other.character_height;
		   this->m_actor.ID(this->m_actorId);
		   this->m_chrBlood = other.m_chrBlood;
		   this->blood = other.blood;
	   }
	   return *this;
	}

	void setCharacterBlood(int maxBlood, int curBlood){
		m_chrBlood.setMaxBlood(maxBlood);
		m_chrBlood.setBlood(curBlood);
	}

	int modifyChrBlood(int bloodDiff){
		m_chrBlood.modifyBlood(bloodDiff);
		if(m_chrBlood.getBlood() == 0){
			m_curState = MotionState::DEAD;
		}
//		blood += bloodDiff;
//		if(blood <= 0){
//			m_curState = MotionState::DEAD;
//		}
		return m_chrBlood.getBlood();
	}
	int readChrBlood()
	{
		return m_chrBlood.getBlood();
	}
	void notOnCameraFocus()
	{
		m_isOnCameraFocus = false;
	}

private:
	float getNewRotateAngle();

public:
	int collision; //人物是否碰撞中
	
private:
	//friend object id
	SCENEid m_sceneId;
	OBJECTid m_terrianId;
	CHARACTERid m_actorId;
	OBJECTid m_dummyCameraId;
	ROOMid m_terrianRoomId;

	//player controller
	FnCharacter m_actor;

	//mesh info
	std::string m_meshFileName;

	//state info
	std::string m_characterName;
	Blood m_chrBlood;
	int blood;
	float m_fPos3[3], m_fDir3[3], m_uDir3[3];
	float m_moveVel, m_rotateVel;
	MotionState m_curState;
	ACTIONid m_curActionId;
	int m_coolDownCnt;
	bool m_isOnCameraFocus;

	//action mapping
	std::map<MotionState, ACTIONid> m_mapState2Action;
	std::map<ActionType, ACTIONid> m_mapIndex2Action;

	//character info
	float character_height;
};

