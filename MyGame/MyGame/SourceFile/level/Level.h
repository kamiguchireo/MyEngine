#pragma once

class MapChip;
class MapChipRender;

struct LevelObjectData {
	Vector3 position;		//座標
	Quaternion rotation;	//回転
	Vector3 scale;		//拡大率
	const wchar_t* name;		//名前
	bool isShadowCaster;		//シャドウキャスター
	bool isShadowReciever;		//シャドウレシーバー
};

class Level:Noncopyable
{
private:
	using MapChipPtr = std::unique_ptr<MapChip>;
	using MapChipRenderPtr = std::unique_ptr<MapChipRender>;

public:
	Level() {}
	~Level();

	//レベルの初期化
	//filePath		tklファイルのファイルパス
	//hoolFunc		オブジェクトを作成するときのフック関数
	//フックしないときはnullptrを指定してください
	//デフォルトで作成されるMapChipクラスのインスタンスが不要な場合はtrueを返してください
	void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);
};

