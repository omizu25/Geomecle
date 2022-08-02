//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "title.h"
#include "application.h"
#include "camera.h"
#include "object.h"
#include "number_manager.h"
#include "input.h"
#include "object2D.h"
#include "effect.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTitle::CTitle()
{
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CTitle::CTitle(EMode mode) : CMode(mode)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTitle::Init()
{
	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(1000.0f, 300.0f, 0.0f));
	pTitle->SetTexture(CTexture::LABEL_Title);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTitle::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTitle::Update()
{
	// 更新
	CObject::UpdateAll();

	static int time = 0;

	time++;

	if ((time % 10) == 0)
	{// 一定間隔
		float width = CWall::STD_WIDTH * 0.5f;
		float height = CWall::STD_HEIGHT * 0.5f;

		D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandam(width, -width), FloatRandam(height, -height), 0.0f);

		// 爆発
		CEffect::Explosion(pos);
	}

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		Change(MODE_GAME);
		return;
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTitle::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}
