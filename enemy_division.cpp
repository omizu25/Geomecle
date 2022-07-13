//**************************************************
// 
// enemy_division.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_division.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CEnemyDivision::MAX_MOVE = 4.0f;
const float CEnemyDivision::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEnemyDivision::CEnemyDivision() :
	m_time(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEnemyDivision::~CEnemyDivision()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CEnemyDivision::Init()
{
	m_time = 0;

	// 初期化
	CEnemy::Init();

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEnemyDivision::Uninit()
{
	// 終了
	CEnemy::Uninit();
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEnemyDivision::Update()
{
	m_time++;

	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// ホーミング
	Homing(&pos, pos, posDest, MAX_MOVE);

	// 位置の設定
	CObject3D::SetPos(pos);

	D3DXVECTOR3 posDiff = posDest - pos;

	float rot = atan2f(posDiff.x, posDiff.y) + (D3DX_PI * 0.25f);
	rot += (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

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
void CEnemyDivision::Draw()
{
	// 描画
	CEnemy::Draw();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CEnemyDivision::Set(const D3DXVECTOR3& pos)
{
	// 位置の設定
	CObject3D::SetPos(pos);

	// テクスチャの設定
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// 色の設定
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	// サイズの設定
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));
}
