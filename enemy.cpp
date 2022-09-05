//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy.h"
#include "enemy_homing.h"
#include "enemy_round_trip.h"
#include "enemy_windmill.h"
#include "enemy_snake_head.h"
#include "enemy_division.h"
#include "enemy_rolling.h"
#include "effect_manager.h"
#include "exp.h"
#include "application.h"
#include "mode.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemy::STD_SIZE = 30.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEnemy* CEnemy::Create(CEnemy::EType type, const D3DXVECTOR3& pos)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case CEnemy::TYPE_HOMING:
		pEnemy = new CEnemyHoming;
		break;

	case CEnemy::TYPE_ROUNDTRIP:
		pEnemy = new CEnemyRoundTrip;
		break;

	case CEnemy::TYPE_WINDMILL:
		pEnemy = new CEnemyWindmill;
		break;

	case CEnemy::TYPE_SNAKE:
		pEnemy = new CEnemySnakeHead;
		break;

	case CEnemy::TYPE_DIVISION:
		pEnemy = new CEnemyDivision;
		break;

	case CEnemy::TYPE_ROLLING:
		pEnemy = new CEnemyRolling;
		break;

	case CEnemy::TYPE_MAX:
	case CEnemy::TYPE_NONE:
	default:
		assert(false);
		break;
	}

	if (pEnemy != nullptr)
	{// nullチェック
		pEnemy->Init();
		pEnemy->Set(pos);
	}

	return pEnemy;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemy::CEnemy()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemy::Init()
{
	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject3D::TYPE_ENEMY);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemy::Uninit()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// 爆発
	CEffectManager::GetInstanse()->Explosion(pos);

	if (CApplication::GetInstanse()->GetMode()->Get() == CMode::MODE_GAME)
	{// ゲーム中
		// 経験値の生成
		CExp::CreateAll(pos);
	}

	// 終了
	CObject3D::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemy::Update()
{
	// 更新
	CObject3D::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemy::Draw()
{
	// 描画
	CObject3D::Draw();
}
