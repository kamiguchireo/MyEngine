#pragma once
#include "TklFile.h"

class MapChip;
class MapChipRender;

struct LevelObjectData {
	Vector3 position;		//座標
	Quaternion rotation;	//回転
	Vector3 scale;		//拡大率
	const wchar_t* name = nullptr;		//名前
	bool isShadowCaster = true;		//シャドウキャスター
	bool isShadowReciever = true;		//シャドウレシーバー
};

class Level:Noncopyable
{
private:
	using MapChipPtr = std::unique_ptr<MapChip>;
	using MapChipRenderPtr = std::unique_ptr<MapChipRender>;

public:
	Level();
	~Level();

	//レベルの初期化
	//filePath		tklファイルのファイルパス
	//hoolFunc		オブジェクトを作成するときのフック関数
	//フックしないときはnullptrを指定してください
	//デフォルトで作成されるMapChipクラスのインスタンスが不要な場合はtrueを返してください
	void Init(const char* filePath, std::function<bool(LevelObjectData& objData)> hookFunc);

private:
	//マップチップレンダーを作成するか、描画するオブジェクトをインクリメントする
	//未登録のオブジェクトが渡されたら、レンダーを作成する
	//登録済みの場合は、マップチップレンダーが描画すべきオブジェクトをインクリメントする
	MapChipRender* CreateMapChipRenderOrAddRenderObject(const LevelObjectData& objData,int i);
	//ボーン行列の構築
	void BuildBoneMatrices();
private:
	std::map<unsigned int, MapChipRender*>m_mapChipRenderPtrs;		//マップチップレンダーの配列
	std::vector<MapChipPtr> m_mapChipPtrs;			//マップチップの配列
	TklFile m_tklFile;
	using BonePtr = std::unique_ptr<Bone>;
	std::vector<BonePtr> m_bones;
	std::unique_ptr<Matrix[]>	m_boneMatrixs;		//ボーン行列
	bool m_isInited = false;						//初期化フラグ

};