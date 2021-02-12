#include "stdafx.h"
#include "MapChipRender.h"
#include "mbstring.h"

MapChipRender::MapChipRender()
{

}

MapChipRender::~MapChipRender()
{
	if (m_modelRender != nullptr)
	{
		DeleteGO(m_modelRender);
		m_modelRender = nullptr;
	}
}
bool MapChipRender::Start()
{
	return true;
}

void MapChipRender::Update()
{
	m_modelRender->ModelInstanceRefresh();

	if (m_renderObjDatas.size() > 1) {
		for (auto& objData : m_renderObjDatas) {
			m_modelRender->UpdateInstancingData(objData.position, objData.rotation, objData.scale);
		}
		m_modelRender->UpdateInstancingSTB();
	}
	else
	{
		m_modelRender->Update();
	}
}

void MapChipRender::InitAfterAddAllRenderObjects()
{
	//スキンモデルレンダーを初期化する
	m_modelRender = NewGO<prefab::ModelRender>(0, nullptr);
	//ファイルパスを作成
	wchar_t filePath[256];
	swprintf_s(filePath, L"Assets/modelData/%s.tkm", m_renderObjDatas[0].name);

	size_t origsize = wcslen(filePath) + 1;
	size_t convertedChars = 0;
	char strConcat[] = "";
	size_t strConcatsize = (strlen(strConcat) + 1) * 2;
	const size_t newsize = origsize * 2;
	char* nstring = new char[newsize + strConcatsize];
	wcstombs_s(&convertedChars, nstring, newsize, filePath, _TRUNCATE);
	_mbscat_s((unsigned char*)nstring, newsize + strConcatsize, (unsigned char*)strConcat);

	//モデルレンダーの初期化
	m_modelRender->SetTkmFilePath(nstring);
	m_modelRender->InitTkmFile(nstring);
	m_modelRender->SetPosition(m_renderObjDatas[0].position);
	m_modelRender->SetRotation(m_renderObjDatas[0].rotation);
	m_modelRender->SetScale(m_renderObjDatas[0].scale);
	m_modelRender->SetInstanceNum(m_numRenderObject);
	m_modelRender->SetLevelMatrix(m_levelMatrixs);
	if (m_renderObjDatas.size() > 1)
	{
		m_modelRender->SetVSEntryPoint("VSMainInstancing");
	}
	else
	{
		m_modelRender->SetVSEntryPoint("VSMain");
	}
	//影
	m_modelRender->SetShadowCasterFlag(true);
	m_modelRender->SetShadowRecieverFlag(true);

	m_modelRender->Start();
}