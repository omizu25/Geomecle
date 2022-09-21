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
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CTitle::CTitle() : CMode(CMode::MODE_TITLE),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_time(0),
	m_partCnt(0)
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
	m_time = 0;
	m_partCnt = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.3f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(600.0f, 150.0f, 0.0f));
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

	// エフェクト
	Effect();

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
void CTitle::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// エフェクト
//--------------------------------------------------
void CTitle::Effect()
{
	m_time++;

	if ((m_time % 20) != 0)
	{// 一定間隔待ち
		return;
	}

	if (m_partCnt % 10 == 0)
	{// 一定間隔
		m_col.r = FloatRandom(1.0f, 0.0f);
		m_col.g = FloatRandom(1.0f, 0.0f);
		m_col.b = FloatRandom(1.0f, 0.0f);
	}

	m_partCnt++;

	float width = CWall::STD_WIDTH * 0.25f;
	float height = CWall::STD_HEIGHT * 0.25f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	// パーティクル
	CEffectManager::GetInstanse()->Particle(pos, m_col);
}
