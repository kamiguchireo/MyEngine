#pragma once
#include <map>
#include "SourceFile/NameKey.h"
#include "SourceFile/Noncopyable.h"

class WaveFile;
typedef std::shared_ptr<WaveFile> WaveFilePtr;
typedef std::map<unsigned int, WaveFilePtr> WaveFilePtrMap;

//波形データバング
//一度ロードされた波形データをバンクに登録することで
//登録された波形データは再度読み込みを行う必要がなくなる
class WaveFileBank : Engine::Noncopyable
{
public:
	WaveFileBank();
	~WaveFileBank();

	//波形データを登録
	//groupID		グループID
	//waveFile		波形データ
	void RegistWaveFile(int groupID, WaveFilePtr waveFile);

	//引数で指定したファイルパスの波形データがバンクに登録されているか検索する
	//groupID		グループID
	//filePath		ファイルパス
	WaveFilePtr FindWaveFile(int groupID, const wchar_t* filePath);

	//引数で指定したファイルパスの波形データがバンクに登録されているか検索する
	//ネームキーを使用する
	WaveFilePtr FindWaveFile(int groupID, const WNameKey& nameKey);

	//波形データをバンクから登録解除
	//groupID		グループID
	//waveFile		波形データ
	void UnregistWaveFile(int groupID, WaveFilePtr waveFile);

	//グループ単位で解放
	void Release(int groupID);

	//全て解放
	void ReleaseAll()
	{
		for (int i = 0; i < MAX_GROUP; i++)
		{
			Release(i);
		}
	}

private:
	static const int MAX_GROUP = 256;
	WaveFilePtrMap	m_waveFileMap[MAX_GROUP];		//!<waveファイルのリスト。
};