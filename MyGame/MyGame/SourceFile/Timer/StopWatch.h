#pragma once
class StopWatch
{
public:
	StopWatch()
	{
		freq = 0;
		end = 0;
		begin = 0;
		elapsed = 0.0;
		elapsedMill = 0.0;
		elapsedMicro = 0.0;
	}
	~StopWatch()
	{

	}

	//�v���J�n
	void Start()
	{
		::QueryPerformanceCounter(reinterpret_cast <LARGE_INTEGER*>(&begin));
	}

	//�v���I��
	void Stop();

	//�o�ߎ��Ԃ��擾(�P��:�b)
	double GetElapsed() const
	{
		return elapsed;
	}

	//�o�ߎ��Ԃ��擾(�P��:�~���b)
	double GetElapsedMillisecond() const
	{
		return elapsedMill;
	}

	//�o�ߎ��Ԃ��擾(�P��:�}�C�N���b)
	double GetElapsedMicrosecond() const
	{
		return elapsedMicro;
	}

private:
	LONGLONG freq;			//���g��
	LONGLONG end;			//�I��
	LONGLONG begin;			//�J�n
	double elapsed;			//�o�ߎ���(�P�� : �b)
	double elapsedMill;		//�o�ߎ���(�P�� : �~���b)
	double elapsedMicro;	//�o�ߎ���(�P�� : �}�C�N���b)
};

