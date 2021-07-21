#include "stdafx.h"
#include "Test.h"
#include "SourceFile/level/Level.h"
#include "Player/Player.h"

Test::Test()
{
}

Test::~Test()
{

}

void Test::OnDestroy()
{

}
bool Test::Start()
{
	if (m_level == nullptr)
	{
		m_level = new Level();
		m_level->Init("Assets/Level/Test.tkl",[&](const LevelObjectData& objData) {
			if (wcscmp(objData.name, L"Player") == 0)
			{
				m_player = NewGO<Player>(0);
				return true;
			}
			if(wcscmp(objData.name,L""))
			return false;
		});
	}
	return true;
}

void Test::Update()
{

}