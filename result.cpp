//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "result.h"
#include "application.h"
#include "camera.h"
#include "object.h"
#include "number_manager.h"
#include "input.h"
#include "object2D.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CResult::CResult(EMode mode) : CMode(mode)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
{
	CObject2D* pResult = CObject2D::Create();
	pResult->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pResult->SetSize(D3DXVECTOR3(1000.0f, 300.0f, 0.0f));
	pResult->SetTexture(CTexture::LABEL_Result);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CResult::Update()
{
	// 更新
	CObject::UpdateAll();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		Change(MODE_TITLE);
		return;
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CResult::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}
