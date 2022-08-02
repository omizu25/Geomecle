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
#include "input.h"
#include "utility.h"
#include "effect_manager.h"
#include <assert.h>

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CGame::CGame(EMode mode) : CMode(mode)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CGame::~CGame()
{
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

	// 読み込み
	CEnemyManager::GetInstanse()->Load();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CGame::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll(false);

	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();
	*pPlayer = nullptr;

	// 解放
	CEnemyManager::GetInstanse()->Release();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CGame::Update()
{
	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// 決定キーが押された
		D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

		// 爆発
		CEffectManager::GetInstanse()->Explosion(pos);
	}

	// 敵のスポーン
	CEnemyManager::GetInstanse()->Spawn();

	// 弾の発射
	CBullet::Shot();

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
