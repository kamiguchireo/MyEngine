#pragma once

class EnemyRayTest
{
public:
	EnemyRayTest() {}
	~EnemyRayTest() {}

	bool Start();

	//pos		���C�̎n�_
	//dir		���C�̕���
	bool IsHit(Vector3& pos, Vector3& dir);

private:
	const float m_visualDist = 500.0f;
};