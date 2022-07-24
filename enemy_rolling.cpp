//**************************************************
// 
// enemy_rolling.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_rolling.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyRolling::STD_SIZE = 17.5f;
const float CEnemyRolling::STD_MOVE = 4.0f;
const float CEnemyRolling::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
void CEnemyRolling::Create(const D3DXVECTOR3& pos)
{
	{// 1対目
		CEnemyRolling* pEnemy = nullptr;

		pEnemy = new CEnemyRolling;

		if (pEnemy != nullptr)
		{// nullチェック
			pEnemy->Init();
			pEnemy->Set(pos);
			pEnemy->SetRotDir(false);
		}
	}

	{// 2対目
		CEnemyRolling* pEnemy = nullptr;

		pEnemy = new CEnemyRolling;

		if (pEnemy != nullptr)
		{// nullチェック
			pEnemy->Init();
			pEnemy->Set(pos);
			pEnemy->SetRotDir(true);
		}
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyRolling::CEnemyRolling() :
	m_time(0),
	m_rotDir(false)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyRolling::~CEnemyRolling()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyRolling::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyRolling::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyRolling::Update()
{
	m_time++;

	D3DXVECTOR3 pos = CObject3D::GetPos();

	if (m_rotDir)
	{// 右回り
		pos.x += sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;
	}
	else
	{// 左回り
		pos.x += -sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;
	}
	
	pos.y += cosf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	// 範囲内
	InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f));

	// 位置の設定
	CObject3D::SetPos(pos);

	float rot = (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CEnemy::SetRot(rot);

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemyRolling::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyRolling::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// 回転方向の設定
//--------------------------------------------------
void CEnemyRolling::SetRotDir(bool rotDir)
{
	m_rotDir = rotDir;
}
