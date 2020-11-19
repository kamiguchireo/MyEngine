#include "stdafx.h"
#include "TklFile.h"

void TklFile::Load(const char* filePath)
{
	//ファイルのポインタ
	auto fp = fopen(filePath, "rb");
	if (fp == nullptr)
	{
		//ファイルパスが間違っています。
		std::abort();
	}

	//tklファイルのバージョンを読み込み
	fread(&m_tklVersion, sizeof(m_tklVersion), 1, fp);
	//オブジェクトの数を取得
	fread(&m_numObject, sizeof(m_numObject), 1, fp);
	//オブジェクトの数でvectorのリサイズ
	m_objects.resize(m_numObject);

	//オブジェクトの数だけ回す
	for (int i = 0; i < m_numObject; i++)
	{
		auto& obj = m_objects.at(i);
		size_t nameCount = 0;

		//オブジェクトの名前を取得
		fread(&nameCount, 1, 1, fp);
		//モデルの名前のユニークポインタを作成
		obj.name = std::make_unique<char[]>(nameCount + 1);
		fread(obj.name.get(), nameCount + 1, 1, fp);

		//親のIDを取得
		fread(&obj.parentNo, sizeof(obj.parentNo), 1, fp);

		//バインドポーズを取得
		fread(obj.bindPose, sizeof(obj.bindPose), 1, fp);

		//バインドポーズの逆数を取得
		fread(obj.invBindPose, sizeof(obj.invBindPose), 1, fp);

		//オブジェクトの番号
		obj.no = i;

		//シャドウキャスターのフラグ
		fread(&obj.isShadowCaster, sizeof(obj.isShadowCaster), 1, fp);

		//シャドウレシーバーのフラグ
		fread(&obj.isShadowReciever, sizeof(obj.isShadowReciever), 1, fp);

		//intパラメータの数
		int numIntData;
		fread(&numIntData, sizeof(numIntData), 1, fp);
		//intパラメータの数でリサイズ
		obj.intDatas.resize(numIntData);
		//intパラメータの数分回す
		for (int i = 0; i < numIntData; i++)
		{
			int val = 0;
			//int型で取得
			fread(&val, sizeof(val), 1, fp);
			obj.intDatas.push_back(val);
		}

		//floatパラメータの数
		int numFloatData;
		fread(&numFloatData, sizeof(numFloatData), 1, fp);
		//floatパラメータの数でリサイズ
		obj.floatDatas.resize(numFloatData);
		//floatパラメータの数分回す
		for (int i = 0; i < numFloatData; i++)
		{
			float val = 0;
			//float型で取得
			fread(&val, sizeof(val), 1, fp);
			obj.floatDatas.push_back(val);
		}

		//stringパラメータの数
		int numStringData;
		fread(&numStringData, sizeof(numStringData), 1, fp);
		//stringパラメータの数でリサイズ
		obj.charDatas.resize(numStringData);
		//stringパラメータの数だけ回す
		for (int i = 0; i < numStringData; i++)
		{
			//stringパラメータの長さ
			int numChara;
			fread(&numChara, sizeof(numChara), 1, fp);
			//stringパラメータ
			obj.charDatas[i] = std::make_unique<char[]>(numChara + 1);
			fread(obj.charDatas[i].get(), numChara + 1, 1, fp);
		}

		//vector3パラメータの数
		int numVec3Data;
		fread(&numVec3Data, sizeof(numVec3Data), 1, fp);
		//vector3パラメータ
		for (int i = 0; i < numVec3Data; i++)
		{
			float x, y, z;
			fread(&x, sizeof(x), 1, fp);
			fread(&y, sizeof(y), 1, fp);
			fread(&z, sizeof(z), 1, fp);
			obj.vec3Datas.push_back(Vector3(x, y, z));
		}
	}
	//ファイルを閉じる
	fclose(fp);
}