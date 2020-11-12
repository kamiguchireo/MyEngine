#pragma once
#include "StopWatch.h"
#include <list>

class GameTime
{
public:
	GameTime(){}
	~GameTime(){}

	//1�t���[���̌o�ߎ��Ԃ��擾
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
			//���ϒl���Ƃ�
			m_frameDeltaTime = totalTime / m_frameDeltaTimeQue.size();
			//�擪�v�f���폜
			m_frameDeltaTimeQue.pop_front();
		}
	}

	//FPS���擾
	float GetFPS()
	{
		return 1.0f / m_frameDeltaTime;
	}
private:
	std::list<float> m_frameDeltaTimeQue;
	float m_frameDeltaTime = 1.0f / 60.0f;		//1�t���[���̌o�ߎ���
};

extern GameTime g_gameTime;