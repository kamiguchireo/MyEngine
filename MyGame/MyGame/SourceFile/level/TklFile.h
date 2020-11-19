#pragma once

//Tklファイルのローダー

class TklFile
{
public:
	struct SObject {
		std::unique_ptr<char[]>name;		//モデルの名前
		int parentNo;		//親の番号
		float bindPose[4][3];		//バインドポーズ
		float invBindPose[4][3];		//バインドポーズの逆数
		int no;		//オブジェクトの番号
		bool isShadowCaster;		//シャドウキャスターフラグ
		bool isShadowReciever;		//シャドウレシーバーフラグ
		std::vector<int> intDatas;		//intパラメータ
		std::vector<float> floatDatas;		//floatパラメータ
		std::vector<std::unique_ptr<char[]>> charDatas;		//文字列
		std::vector<Vector3> vec3Datas;		//vector3のパラメータ
	};

	TklFile(){}
	~TklFile(){}
	//読み込み処理
	//filePath		ファイルパス
	void Load(const char* filePath);

	//オブジェクトに対してクエリを行う
	void QueryObject(std::function<void(SObject& obj)> query)
	{
		for (auto& obj : m_objects)
		{
			query(obj);
		}
	}

private:
	int m_tklVersion = 100;		//tklファイルのバージョン
	int m_numObject = 0;		//オブジェクトの数
	std::vector<SObject> m_objects;		//オブジェクトのリスト
};

