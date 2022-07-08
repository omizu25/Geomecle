//**************************************************
// 
// enemy_homing.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_homing.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEnemyHoming::MAX_U = 4;
const int CEnemyHoming::ANIMATION_TIME = 10;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyHoming::CEnemyHoming() :
	m_time(0),
	m_idxPattern(0)
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
HRESULT CEnemyHoming::Init()
{
	// 初期化
	CEnemy::Init();

	return S_OK;
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
	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	D3DXVECTOR3 posDiff = posDest - pos;

	float rot = atan2f(posDiff.x, posDiff.y);

	// 角度の正規化
	NormalizeAngle(&rot);

	// 向きの設定
	CObject3D::SetRot(rot);

	// ホーミング
	Homing(&pos, pos, posDest, 3.0f);

	// 位置の設定
	CObject3D::SetPos(pos);

	m_time++;

	if ((m_time % CEnemyHoming::ANIMATION_TIME) == 0)
	{// 一定時間経過
		m_idxPattern++;

		// テクスチャ座標の設定
		CEnemyHoming::SetTex();
	}

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
}

//--------------------------------------------------
// テクスチャ座標の設定
//--------------------------------------------------
void CEnemyHoming::SetTex()
{
	int a = m_idxPattern % CEnemyHoming::MAX_U;
	float b = 1.0f / CEnemyHoming::MAX_U;
	float c = a * b;

	D3DXVECTOR2 u = D3DXVECTOR2(c, c + b);
	D3DXVECTOR2 v = D3DXVECTOR2(0.0f, 1.0f);

	// テクスチャ座標の設定
	CObject3D::SetVtxTex(u, v);
}