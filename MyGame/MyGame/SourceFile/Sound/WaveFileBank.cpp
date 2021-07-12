#include "stdafx.h"
#include "WaveFileBank.h"
#include "WaveFile.h"

WaveFileBank::WaveFileBank()
{

}

WaveFileBank::~WaveFileBank()
{
	ReleaseAll();
}

void WaveFileBank::Release(int groupID)
{
	for (auto waveFile : m_waveFileMap[groupID]) {
		waveFile.second->Release();
	}
	m_waveFileMap[groupID].clear();
}

void WaveFileBank::UnregistWaveFile(int groupID, WaveFilePtr waveFile)
{
	//groupID is invalid
	if (groupID > MAX_GROUP)
	{
		std::abort();
	}
	m_waveFileMap->erase(waveFile->GetFilePathHash());
}

void WaveFileBank::RegistWaveFile(int groupID, WaveFilePtr waveFile)
{
	//groupID is invalid
	if (groupID > MAX_GROUP)
	{
		std::abort();
	}
	m_waveFileMap[groupID].insert({ waveFile->GetFilePathHash(), waveFile });
}

WaveFilePtr WaveFileBank::FindWaveFile(int groupID, const wchar_t* filePath)
{
	//groupID is invalid
	if (groupID > MAX_GROUP)
	{
		std::abort();
	}
	auto value = m_waveFileMap[groupID].find(Util::MakeHash(filePath));
	if (value != m_waveFileMap[groupID].end()) {
		return value->second;
	}
	return WaveFilePtr();
}

WaveFilePtr WaveFileBank::FindWaveFile(int groupID, const WNameKey& nameKey)
{
	//groupID is invalid
	if (groupID > MAX_GROUP)
	{
		std::abort();
	}
	auto value = m_waveFileMap[groupID].find(nameKey.GetHashCode());
	if (value != m_waveFileMap[groupID].end()) {
		return value->second;
	}
	return WaveFilePtr();

}
