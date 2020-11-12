#pragma once
#include "StopWatch.h"
#include <list>

class GameTime
{
public:
	GameTime(){}
	~GameTime(){}

	//1フレームの経過時間を取得
	const float GetFrameDeltaTime()const
	{
		return m_frameDeltaTime;
	}

	void PushFrameDeltaTime(float deltaTime)
	{
		m_frameDeltaTimeQue.push_back(deltaTime);
		if (m_frameDeltaTimeQue.size() > 5)
		{
			float totalTime = 0.0f;
			for (auto time : m_frameDeltaTimeQue)
			{
				totalTime += time;
			}
			//平均値をとる
			m_frameDeltaTime = totalTime / m_frameDeltaTimeQue.size();
			//先頭要素を削除
			m_frameDeltaTimeQue.pop_front();
		}
	}

	//FPSを取得
	float GetFPS()
	{
		return 1.0f / m_frameDeltaTime;
	}
private:
	std::list<float> m_frameDeltaTimeQue;
	float m_frameDeltaTime = 1.0f / 60.0f;		//1フレームの経過時間
};

extern GameTime g_gameTime;