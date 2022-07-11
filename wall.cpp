//**************************************************
// 
// wall.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "wall.h"
#include "object3D.h"
#include "application.h"
#include <assert.h>

//==================================================
// インクルード
//==================================================
const float CWall::MAX_WIDTH = 10.0f;
const float CWall::MAX_LENGTH = 1200.0f;

//--------------------------------------------------
// 全ての生成
//--------------------------------------------------
void CWall::AllCreate()
{
	{// 上下の壁
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::MAX_LENGTH, CWall::MAX_WIDTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, CWall::MAX_LENGTH * 0.5f, 0.0f);

		// 上の壁
		CWall::Create(pos, size);

		// 下の壁
		CWall::Create(-pos, size);
	}

	{// 左右の壁
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::MAX_WIDTH, CWall::MAX_LENGTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(CWall::MAX_LENGTH * 0.5f, 0.0f, 0.0f);

		// 右の壁
		CWall::Create(pos, size);

		// 左の壁
		CWall::Create(-pos, size);
	}
}

//--------------------------------------------------
// 幅の取得
//--------------------------------------------------
float CWall::GetWidth()
{
	return MAX_WIDTH;
}

//--------------------------------------------------
// 長さの取得
//--------------------------------------------------
float CWall::GetLength()
{
	return MAX_LENGTH;
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CWall* CWall::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CWall* pWall = nullptr;

	pWall = new CWall;

	if (pWall != nullptr)
	{// nullチェック
		pWall->Init();
		pWall->SetPos(pos);
		pWall->SetSize(size);
	}

	return pWall;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CWall::CWall()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CWall::~CWall()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CWall::Init()
{
	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject::TYPE_WALL);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CWall::Uninit()
{
	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CWall::Update()
{
	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CWall::Draw()
{
	// 描画
	CObject3D::Draw();
}
