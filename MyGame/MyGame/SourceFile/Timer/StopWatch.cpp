#include "stdafx.h"
#include "StopWatch.h"

//åvë™èIóπ
void StopWatch::Stop()
{
	::QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&freq));
	::QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&end));
	elapsed = double(end - begin) / freq;
	elapsedMill = elapsed * 1000.0f;
	elapsedMicro = elapsedMill * 1000.0f;
}