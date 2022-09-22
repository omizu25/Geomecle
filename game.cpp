//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "game.h"
#include "application.h"
#include "camera.h"
#include "player.h"
#include "enemy_manager.h"
#include "bullet.h"
#include "number_manager.h"
#include "time.h"
#include "score.h"
#include "mul.h"
#include "effect_manager.h"
#include "input.h"
#include "ranking.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_pTime(nullptr),
	m_pScore(nullptr),
	m_pMul(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
	assert(m_pTime == nullptr);
	assert(m_pScore == nullptr);
	assert(m_pMul == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CGame::Init()
{
	// プレイヤーの生成
	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();

	if (*pPlayer == nullptr)
	{// nullチェック
		*pPlayer = CPlayer::Create();
	}

	// 初期化
	CEnemyManager::GetInstanse()->Init();

	{// タイム
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CTime::STD_WIDTH * 1.0f);
		float height = CTime::STD_HEIGHT * 0.5f + 15.0f;

		// タイムの生成
		m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), 45);
	}

	{// スコア
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = CScore::STD_HEIGHT * 0.5f + 10.0f;

		// スコアの生成
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}
	
	{// 倍率
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = (CMul::STD_HEIGHT * 0.5f) + CScore::STD_HEIGHT + 10.0f;

		// 倍率の生成
		m_pMul = CMul::Create(D3DXVECTOR3(width, height, 0.0f));
	}
	
	{// ベストスコア
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		int score = CRanking::Get(0);

		float width = (size.x * Digit(score)) + (((Digit(score) - 1) / 3) * (size.x * 0.5f));
		float height = size.y * 0.5f + 10.0f;

		// スコアの生成
		CScore* pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// スコアの設定
		pScore->Set(score);
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	// ランキングの設定
	CRanking::Set(m_pScore->Get());
	
	// 全ての解放
	CObject::ReleaseAll(false);

	m_pTime = nullptr;
	m_pScore = nullptr;
	m_pMul = nullptr;

	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();
	*pPlayer = nullptr;

	// 終了
	CEnemyManager::GetInstanse()->Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	// 更新
	CEnemyManager::GetInstanse()->Update();

	// 弾の発射
	CBullet::Shot();

#ifdef _DEBUG

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		CPlayer* pPlayer = CApplication::GetInstanse()->GetPlayer();

		if (pPlayer != nullptr)
		{// nullチェック
			// 爆発
			CEffectManager::GetInstanse()->Explosion(pPlayer->GetPos());
		}
	}

	if (CInput::GetKey()->TriggerSpecific(DIK_F2))
	{// キーが押された
		// モードの変更
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);
	}

#endif // _DEBUG

	// タイムの減算
	m_pTime->Update();

	// 更新
	CObject::UpdateAll();

	// カメラの更新
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CGame::Draw()
{
	// カメラの設定
	CApplication::GetInstanse()->GetCamera()->Set();

	// 描画
	CObject::DrawAll();
}

//--------------------------------------------------
// スコアの取得
//--------------------------------------------------
CScore* CGame::GetScore()
{
	return m_pScore;
}

//--------------------------------------------------
// 倍率の取得
//--------------------------------------------------
CMul* CGame::GetMul()
{
	return m_pMul;
}
