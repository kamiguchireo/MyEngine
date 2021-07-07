#pragma once
#define _CRT_SECURE_NO_WARNINGS

//BulletPhysicsのインクルード
#include "btBulletDynamicsCommon.h"
#include "BulletCollision\CollisionDispatch\btGhostObject.h"

#include "MiniEngine.h"
#include "SourceFile/Noncopyable.h"
#include "SourceFile/graphic/Animation/Animation.h"
#include "SourceFile/graphic/Animation/AnimationClip.h"
#include "SourceFile/graphic/Animation/AnimationPlayController.h"
#include "SourceFile/GameObject/GameObject.h"
#include "SourceFile/GameObject/GameObjectManager.h"

#include "SourceFile/Timer/GameTime.h"

enum EnCollisionAttr {
	enCollisionAttr_StaticObject,
	enCollisionAttr_Character,
	enCollisionAttr_User,
	enCollisionAttr_Player,
	enCollisionAttr_Enemy,
};
static const int MAX_BONE = 512;	//!<ボーンの最大数。
static const int CascadeShadow = 3;		//シャドウマップの枚数
static const int DefferdTexNum = 2;
static const Vector3 gravity = { 0.0f,-9.8f,0.0f };
static const float footStepAdjustValue = 1.0f;
static const Vector2 TexResolution = { 4096.0f,4096.0f };
enum EnPlayerAnimation {
	enPlayerAnimation_Rifle_Idle,
	enPlayerAnimation_Rifle_Walk,
	enPlayerAnimation_Rifle_Run,
	enPlayerAnimation_Rifle_Sprint,
	enPlayerAnimation_Rifle_Down_To_Aim,
	enPlayerAnimation_Rifle_fire,
	enPlayerAnimation_Death_From_Front,
	enPlayerAnimation_Num
};

enum EnEnemyAnimation {
	enEnemyAnimation_Rifle_Idle,
	enEnemyAnimation_Rifle_Walk,
	enEnemyAnimation_Rifle_Run,
	enEnemyAnimation_Rifle_Sprint,
	enEnemyAnimation_Rifle_Down_To_Aim,
	enEnemyAnimation_Death_From_Front,
	enEnemyAnimation_Num
};

enum HitBoxNum {
	Head,
	Spine2,
	Spine,
	Hips,
	LeftUpLeg,
	RightUpLeg,
	LeftLeg,
	RightLeg,
	LeftFoot,
	RightFoot,
	LeftToeBase,
	RightToeBase,
	LeftArm,
	RightArm,
	LeftForeArm,
	RightForeArm,
	LeftHand,
	RightHand,
	Num
};

enum CollisionActivationState
{
	Default,
	Hit
};

using namespace Engine;