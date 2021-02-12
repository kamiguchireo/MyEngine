#include "stdafx.h"
#include "Level.h"
#include "comutil.h"
#include "SourceFile/NameKey.h"
#include "MapChip.h"
#include "MapChipRender.h"
#include <comdef.h>

Level::Level()
{
	WNameKey Dummy(L"Dummy");
	DummyHash = Dummy.GetHashCode();
}

Level::~Level()
{

}

MapChipRender* Level::CreateMapChipRenderOrAddRenderObject(const LevelObjectData& objData,int i)
{
	WNameKey nameKey(objData.name);
	if (nameKey.GetHashCode() == DummyHash)
	{
		//ダミーを飛ばす
		return nullptr;
	}
	auto itFind = m_mapChipRenderPtrs.find(nameKey.GetHashCode());
	MapChipRender* pMapChipRender = nullptr;
	if (itFind == m_mapChipRenderPtrs.end())
	{
		//登録されていないオブジェクト
		pMapChipRender = NewGO<MapChipRender>(0);
		m_mapChipRenderPtrs.insert({ nameKey.GetHashCode(),pMapChipRender });
	}
	else
	{
		//描画すべきオブジェクトのインクリメント
		pMapChipRender = itFind->second;
		pMapChipRender->AddRenderObject();
	}
	pMapChipRender->AddRenderObject(objData, m_bones[i].get()->GetWorldMatrix());

	return pMapChipRender;
}
void Level::Init(
	const char* filePath,
	std::function<bool(LevelObjectData& objData)>hookFunc
)
{
	//レベルをロードする
	m_tklFile.Load(filePath);
	BuildBoneMatrices();
	//レベルのデータを取得
	struct SParams {
		bool isShadowCaster;
		bool isShadowReciever;
	};
	std::vector<SParams>Params;
	m_tklFile.QueryObject([&](TklFile::SObject& tklObj) {
		SParams objParam;
		objParam.isShadowCaster = tklObj.isShadowCaster;
		objParam.isShadowReciever = tklObj.isShadowReciever;
		Params.push_back(objParam);
	});

	for (int i = 1; i < m_bones.size(); i++)
	{
		auto bone = m_bones[i].get();
		//親がルートの場合マップチップを作成する
		if (bone->GetParentBoneNo() == 0)
		{
			LevelObjectData objData;
			Vector3 scale;
			bone->CalcWorldTRS(objData.position, objData.rotation, objData.scale);
			//3dsMaxとは軸が違うので、補正を入れる
			auto t = objData.position.y;
			objData.position.y = objData.position.z;
			objData.position.z = -t;

			t = objData.rotation.y;
			objData.rotation.y = objData.rotation.z;
			objData.rotation.z = -t;
		
			//値の入れ替え
			std::swap(objData.scale.y, objData.scale.z);
			
			//オブジェクトの名前取得
			objData.name = bone->GetName();
			std::wstring hoge = objData.name;

			objData.isShadowCaster = Params.at(i).isShadowCaster;
			objData.isShadowReciever = Params.at(i).isShadowReciever;

			auto isHook = false;
			if (hookFunc != nullptr)
			{
				//hook関数が指定されているのでhook関数を呼び出す
				isHook = hookFunc(objData);
			}
			if (isHook == false)
			{
				//マップチップレンダラーを作成する
				CreateMapChipRenderOrAddRenderObject(objData,i);
			}
		}
	}

	//マップチップレンダーを初期化する
	for (auto& mapChipRender : m_mapChipRenderPtrs)
	{
		mapChipRender.second->InitAfterAddAllRenderObjects();
		mapChipRender.second->QueryRenderObjDatas([&](const LevelObjectData& objData)
		{
			//フックされなかったので、マップチップを作成
			auto mapChip = std::make_unique<MapChip>(objData, mapChipRender.second);
			m_mapChipPtrs.push_back(std::move(mapChip));

		});
	}

}

void Level::BuildBoneMatrices()
{
	m_tklFile.QueryObject([&](TklFile::SObject& tklObj)
	{
		//バインドポーズ
		Matrix bindPoseMatrix;
		memcpy(bindPoseMatrix.m[0], &tklObj.bindPose[0], sizeof(tklObj.bindPose[0]));
		memcpy(bindPoseMatrix.m[1], &tklObj.bindPose[1], sizeof(tklObj.bindPose[1]));
		memcpy(bindPoseMatrix.m[2], &tklObj.bindPose[2], sizeof(tklObj.bindPose[2]));
		memcpy(bindPoseMatrix.m[3], &tklObj.bindPose[3], sizeof(tklObj.bindPose[3]));
		bindPoseMatrix.m[0][3] = 0.0f;
		bindPoseMatrix.m[1][3] = 0.0f;
		bindPoseMatrix.m[2][3] = 0.0f;
		bindPoseMatrix.m[3][3] = 1.0f;

		//バインドポーズの逆行列。
		Matrix invBindPoseMatrix;
		memcpy(invBindPoseMatrix.m[0], &tklObj.invBindPose[0], sizeof(tklObj.invBindPose[0]));
		memcpy(invBindPoseMatrix.m[1], &tklObj.invBindPose[1], sizeof(tklObj.invBindPose[1]));
		memcpy(invBindPoseMatrix.m[2], &tklObj.invBindPose[2], sizeof(tklObj.invBindPose[2]));
		memcpy(invBindPoseMatrix.m[3], &tklObj.invBindPose[3], sizeof(tklObj.invBindPose[3]));
		invBindPoseMatrix.m[0][3] = 0.0f;
		invBindPoseMatrix.m[1][3] = 0.0f;
		invBindPoseMatrix.m[2][3] = 0.0f;
		invBindPoseMatrix.m[3][3] = 1.0f;

		wchar_t boneName[256];
		mbstowcs(boneName, tklObj.name.get(), 256);
		BonePtr bone = std::make_unique<Bone>(
			boneName,
			bindPoseMatrix,
			invBindPoseMatrix,
			tklObj.parentNo,
			tklObj.no
			);

		m_bones.push_back(std::move(bone));
	});

	for (auto& bone : m_bones)
	{
		if (bone->GetParentBoneNo() != -1)
		{
			m_bones.at(bone->GetParentBoneNo())->AddChild(bone.get());
			//ローカル行列を計算
			const Matrix& parentMatrix = m_bones.at(bone->GetParentBoneNo())->GetInvBindPoseMatrix();
			Matrix localMatrix;
			localMatrix = bone->GetBindPoseMatrix() * parentMatrix;
			bone->SetLocalMatrix(localMatrix);
		}
		else
		{
			bone->SetLocalMatrix(bone->GetBindPoseMatrix());
		}
	}
	//ボーン行列を確保
	m_boneMatrixs = std::make_unique<Matrix[]>(m_bones.size());
	m_isInited = true;
}