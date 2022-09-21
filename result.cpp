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
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult() : CMode(CMode::MODE_RESULT),
	m_time(0)
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
	m_time++;

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

	// エフェクト
	Effect();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		if (m_time >= 20)
		{// フェード時間
			Change(MODE_TITLE);
			return;
		}
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

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CResult::Effect()
{
	m_time++;

	if ((m_time % 12) != 0)
	{// 一定間隔待ち
		return;
	}

	float width = CWall::STD_WIDTH * 0.5f;
	float height = CWall::STD_HEIGHT * 0.5f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	// パーティクル
	CEffectManager::GetInstanse()->Particle(pos, col);
}
