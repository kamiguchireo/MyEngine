#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include "MiniEngine.h"
#include "SourceFile/Noncopyable.h"
#include "SourceFile/graphic/Animation/Animation.h"
#include "SourceFile/graphic/Animation/AnimationClip.h"
#include "SourceFile/graphic/Animation/AnimationPlayController.h"
#include "SourceFile/GameObject/GameObject.h"
#include "SourceFile/GameObject/GameObjectManager.h"

const int NUM_DIRECTIONAL_LIGHT = 4;	//ディレクションライトの数。
static const int MAX_BONE = 512;	//!<ボーンの最大数。
static const int CascadeShadow = 3;		//シャドウマップの枚数

/// <summary>
/// ディレクションライト。
/// </summary>
struct DirectionalLight {
	Vector3 direction;	//ライトの方向。
	float pad0;			//パディング。
	Vector4 color;		//ライトのカラー。
};
/// <summary>
/// ライト構造体。
/// </summary>
struct Light {
	DirectionalLight directionalLight[NUM_DIRECTIONAL_LIGHT];	//ディレクションライト。
	Vector3 eyePos;					//カメラの位置。
	float specPow;					//スペキュラの絞り。
	Vector3 ambinetLight;			//環境光。
};