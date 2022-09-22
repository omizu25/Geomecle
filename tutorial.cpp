//**************************************************
// 
// tutorial.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "tutorial.h"
#include "application.h"
#include "camera.h"
#include "object.h"
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTutorial::CTutorial() : CMode(CMode::MODE_TUTORIAL),
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CTutorial::Init()
{
	m_time = 0;
	
	CObject2D* pTutorial = CObject2D::Create();
	pTutorial->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTutorial->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));
	pTutorial->SetTexture(CTexture::LABEL_Tutorial);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CTutorial::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CTutorial::Update()
{
	// 更新
	CObject::UpdateAll();

	m_time++;

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		if (m_time >= 20)
		{// フェード時間
			Change(MODE_GAME);
			return;
		}
	}

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CTutorial::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}
