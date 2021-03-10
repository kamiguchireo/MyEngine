#pragma once
#define _CRT_SECURE_NO_WARNINGS

//BulletPhysics�̃C���N���[�h
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
	enCollisionAttr_Ground,
	enCollisionAttr_Character,
	enCollisionAttr_User,
};
static const int MAX_BONE = 512;	//!<�{�[���̍ő吔�B
static const int CascadeShadow = 3;		//�V���h�E�}�b�v�̖���
static const int DefferdTexNum = 2;
using namespace Engine;