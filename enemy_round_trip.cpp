//**************************************************
// 
// enemy_round_trip.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_round_trip.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyRoundTrip::MAX_MOVE = 10.0f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyRoundTrip::CEnemyRoundTrip() : 
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyRoundTrip::~CEnemyRoundTrip()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CEnemyRoundTrip::Init()
{
	// 初期化
	CEnemy::Init();

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyRoundTrip::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyRoundTrip::Update()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	float size = (MAX_SIZE * 0.5f) + (CWall::MAX_WIDTH * 0.5f);
	float wall = (CWall::MAX_LENGTH * 0.5f) - size;

	if (InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f)))
	{// 範囲内
		m_move *= -1.0f;

		float rot = CObject3D::GetRot();

		rot += D3DX_PI;

		// 角度の正規化
		NormalizeAngle(&rot);

		// 向きの設定
		CObject3D::SetRot(rot);
	}

	// 位置の設定
	CObject3D::SetPos(pos);

	// 更新
	CEnemy::Update();
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEnemyRoundTrip::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyRoundTrip::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_PaperAirplane);

	// 移動量の設定
	SetMove();
}

//--------------------------------------------------
// 移動量の設定
//--------------------------------------------------
void CEnemyRoundTrip::SetMove()
{
	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	D3DXVECTOR3 posDiff = pos - CObject3D::GetPos();

	float rot = atan2f(posDiff.x, posDiff.y);

	// 角度の正規化
	NormalizeAngle(&rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * MAX_MOVE;

	// 向きの設定
	CObject3D::SetRot(rot);
}