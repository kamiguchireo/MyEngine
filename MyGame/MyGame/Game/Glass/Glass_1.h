#pragma once

struct ObjData {
	Vector3 position;		//座標
	Quaternion rotation;	//回転
	Vector3 scale;		//拡大率
};
class Glass_1:public IGameObject
{
public:
	Glass_1();
	~Glass_1();

	bool Start();
	void Update();
	void Draw();

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
	Model m_Glass;
	ModelInitData m_InitData;
	int m_instanceNum = 1;		//インスタンスの数
	std::vector<ObjData> m_renderObjDatas;		//描画するオブジェクトの配列
};