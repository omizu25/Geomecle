//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include "enemy_homing.h"
#include "enemy_round_trip.h"
#include "enemy_windmill.h"
#include "enemy_snake_head.h"
#include "enemy_division.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemy::MAX_SIZE = 30.0f;

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
HRESULT CEnemy::Init()
{
	// 初期化
	CObject3D::Init();

	// 種類の設定
	CObject3D::SetType(CObject::TYPE_ENEMY);

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemy::Uninit()
{
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
