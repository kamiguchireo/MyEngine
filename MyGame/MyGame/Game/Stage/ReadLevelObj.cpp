#include "stdafx.h"
#include "ReadLevelObj.h"
#include "Game/Game.h"

Enemy* ReadLevelObj::GetEnemyPtr(const wchar_t* ObjName,const Vector3& pos,const Quaternion& rot)
{
	if (wcsncmp(ObjName, L"Enemy_", 6) == 0)
	{
		for (int i = 0; i < 100; i++)
		{
			wchar_t m_enemychar[256] = L"Enemy_";
			if (Firstplace == 10)
			{
				//10の位に上げる
				Tenthplace++;
				Firstplace = 0;
			}
			wchar_t first[2];
			wchar_t ten[2];
			_itow_s(Firstplace, first, 10);
			_itow_s(Tenthplace, ten, 10);
			//10の位をファイルパスに結合
			wcscat_s(m_enemychar, ten);
			//1の位をファイルパスに結合
			wcscat_s(m_enemychar, first);
			//カウントを1上げる
			Firstplace++;

			if (wcsncmp(ObjName, m_enemychar, 8) == 0)
			{
				Enemy* m_enemy = nullptr;
				//ファイルパスが合致したとき
				if (m_IsEnemyInited[m_numEnemy] == false)
				{
					m_IsEnemyInited[m_numEnemy] = true;
					m_enemy = NewGO<Enemy>(0);
					m_numEnemy++;
				}

				//エネミーのポジションをセット
				m_enemy->SetPosition(pos);
				//エネミーの回転をセット
				m_enemy->SetRotation(rot);

				//10の位を0に戻す
				Tenthplace = 0;
				//1の位を0に戻す
				Firstplace = 0;
				//エネミーの数をインクリメント
				Game::GetInstance()->AddEnemyCount();

				return m_enemy;
			}
		}
		Tenthplace = 0;
		Firstplace = 0;
	}
	return nullptr;
}