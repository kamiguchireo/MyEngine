#pragma once
class GameOver:public IGameObject
{
public:
	GameOver();
	~GameOver();

	void Init(Vector3 pos, Vector3 forward);
	void OnDestroy();
	bool Start();
	void Update();

	//シングルトン
	static GameOver* GetInstance()
	{
		if (m_Instance != nullptr)
		{
			return m_Instance;
		}
		return nullptr;
	}
private:
	static GameOver* m_Instance;		//インスタンス
	prefab::SpriteRender* m_DiedSprite = nullptr;		//死亡時に表示するスプライト
	float m_DeadSpriteAlpha = 0.0f;
	const float m_DeadAlphaFadeSpeed = 0.2f;
	Vector3 m_DeadAfterCameraPos = Vector3::Zero;
	Vector3 m_DeadAfterCameraTarget = Vector3::Zero;
	Vector3 m_LerpForwardCameraPos = Vector3::Zero;
	const float m_DeadCameraDist = 300.0f;		//死亡後にカメラを引く距離
	float m_DeadAfterLeapSpeed = 0.2f;		//線形補完する速度
	float m_DeadLeapTime = 0.0f;		//補完時間
	Vector3 m_forward = Vector3::Zero;		//前
	Vector3 m_pos = Vector3::Zero;		//ポジション
	bool m_IsInited = false;		//初期化フラグ
};

