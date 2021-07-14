#pragma once


class Grass_03:public IGameObject
{
	struct ObjData {
		Vector3 position;		//座標
		Quaternion rotation;	//回転
		Vector3 scale;		//拡大率
	};
public:
	Grass_03();
	~Grass_03();

	void OnDestroy();
	bool Start();
	void Update();

	//インスタンシング描画するオブジェクトの追加
	void InitInstance(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
	{
		m_instanceNum = 1;
		ObjData data;
		data.position = trans;
		data.rotation = rot;
		data.scale = scale;
		m_renderObjDatas.push_back(data);
	}
	//インスタンシング描画するオブジェクトの追加
	void AddInstance(const Vector3& trans, const Quaternion& rot, const Vector3& scale)
	{
		m_instanceNum++;
		ObjData data;
		data.position = trans;
		data.rotation = rot;
		data.scale = scale;
		m_renderObjDatas.push_back(data);
	}
private:
	prefab::ModelRender* m_Glass = nullptr;
	int m_instanceNum = 1;		//インスタンスの数
	std::vector<ObjData> m_renderObjDatas;		//描画するオブジェクトの配列
};