#include "stdafx.h"
#include "CameraStateTPS.h"

CameraStateTPS::CameraStateTPS()
{
	//カメラコリジョンの初期化
	m_cameraCollisionSolver.Init(Col_Radius);
	//マウスカーソルの表示を消す
	ShowCursor(false);
}

CameraStateTPS::~CameraStateTPS()
{

}

void CameraStateTPS::Update(Vector3& pivotpos,float& rot)
{
	//マウスカーソルの位置を取得
	POINT pt;
	GetCursorPos(&pt);
	int lstx = pt.x;
	int lsty = pt.y;

	//カメラの回転量をマウスカーソルの位置と初期値を比較して求める
	rot += (DefaultPoint[0] - lstx) * sensiX;
	//最終的なカメラのポジション
	Vector3 pos = pivotpos;
	//最終的なカメラのターゲットのポジション
	Vector3 targetPos = pivotpos;
	//最低限の高さを確保
	{
		pos.y += 90.0f;
		targetPos.y += 90.0f;
	}
	//カメラのポジションに足すY方向の値をマウスカーソルの位置と初期値を比較して求める
	AddPosY -= (DefaultPoint[1] - lsty) * sensiY;

	AddPosY = min(max(MinAddPos, AddPosY), MaxAddPos);
	//カメラのポジションに足すベクトル
	Vector3 addPos = Vector3::Zero;
	//rotからカメラの位置を決める
	addPos.x = sinf(rot) * CameraDist;
	addPos.y = AddPosY;
	addPos.z -= cosf(rot) * CameraDist;
	pos += addPos;

	//マウスカーソルの位置をセット
	SetCursorPos(500, 300);

	//コリジョン解決後の位置
	Vector3 solve_pos = Vector3::Zero;
	m_cameraCollisionSolver.Execute(solve_pos, pos, targetPos);
	//カメラにセット
	g_camera3D->SetPosition(solve_pos);
	g_camera3D->SetTarget(targetPos);
}