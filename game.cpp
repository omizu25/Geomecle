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

	float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CNumberManager::STD_WIDTH * 2.0f);
	float height = CNumberManager::STD_HEIGHT * 0.5f;

	// タイムの生成
	m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), 4500);

	// スコアの生成
	m_pScore = CScore::Create(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, height, 0.0f));

	// 倍率の生成
	m_pMul = CMul::Create(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, CNumberManager::STD_HEIGHT + height, 0.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
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
