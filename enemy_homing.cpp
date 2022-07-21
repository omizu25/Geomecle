//**************************************************
// 
// enemy_homing.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "enemy_homing.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyHoming::STD_MOVE = 3.0f;
const float CEnemyHoming::SIZE_CHANGE = 10.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyHoming::CEnemyHoming() :
	m_time(0),
	m_saveSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyHoming::~CEnemyHoming()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEnemyHoming::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyHoming::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyHoming::Update()
{
	m_time++;

	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// ホーミング
	Homing(&pos, pos, posDest, STD_MOVE);

	// 位置の設定
	CObject3D::SetPos(pos);

	D3DXVECTOR3 size = m_saveSize;

	size.x += sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * SIZE_CHANGE;
	size.y -= sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * SIZE_CHANGE;

	// サイズの設定
	CObject3D::SetSize(size);

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemyHoming::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyHoming::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_Homing);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(0.0f, 0.75f, 1.0f, 1.0f));

	m_saveSize = CObject3D::GetSize();
}
