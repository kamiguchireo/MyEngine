#pragma once

class EnemyRayTest
{
public:
	EnemyRayTest() {}
	~EnemyRayTest() {}

	bool Start();

	//pos		レイの始点
	//dir		レイの方向
	bool IsHit(Vector3& pos, Vector3& dir);

private:
	const float m_visualDist = 500.0f;
};