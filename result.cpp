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
#include "ranking.h"
#include "score.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CResult::CResult() : CMode(CMode::MODE_RESULT),
	m_pRanking(nullptr),
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CResult::~CResult()
{
	assert(m_pRanking == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CResult::Init()
{
	m_time++;

	{// ランキングの背景
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.5f - 15.0f;

		// ランキングの背景の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(600.0f, 650.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f));
		pObj->SetFade(0.0f);
	}

	{// スコアの背景
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.25f- 10.0f;

		// スコアの背景の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(620.0f, 300.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NONE);
		pObj->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.25f));
		pObj->SetFade(0.0f);
	}

	{// ランキング
		float width = (float)CApplication::SCREEN_WIDTH - 35.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// ランキングの生成
		m_pRanking = CRanking::Create(D3DXVECTOR3(width, height, 0.0f), 40.0f);
	}

	{// ランキングの文字列
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f;

		// 文字列の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(450.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Rankig);
		pObj->SetFade(0.0f);
	}

	{// 今回のスコア
		D3DXVECTOR3 size = D3DXVECTOR3(CRanking::STD_WIDTH * 1.3f, CRanking::STD_HEIGHT * 1.3f, 0.0f);
		int score = CRanking::Get(-1);
		int digit = Digit(score);
		float center = (digit * (size.x * 0.5f)) + (((digit - 1) / 3) * (size.x * 0.25f));
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f + center;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// スコアの生成
		CScore* pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// スコアの設定
		pScore->Set(score);
	}

	{// 今回のスコアの文字列
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f - 12.5f;

		// 文字列の生成
		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(450.0f, 100.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NewScore);
		pObj->SetFade(0.0f);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CResult::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll(false);

	m_pRanking = nullptr;
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

	// ランキングの更新
	m_pRanking->Update();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		if (m_time >= CMode::FADE_TIME)
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

	if ((m_time % 10) != 0)
	{// 一定間隔待ち
		return;
	}

	float width = CWall::STD_WIDTH * 0.4f;
	float height = CWall::STD_HEIGHT * 0.4f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	// パーティクル
	CEffectManager::GetInstanse()->Particle(pos, col);
}
