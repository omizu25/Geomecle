//**************************************************
// 
// effect_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect_manager.h"
#include "utility.h"
#include "effect.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEffectManager::MAX_PARTICLE = 300;
const int CEffectManager::MAX_EXPLOSION = 100;
const int CEffectManager::MAX_BULLET = 50;
const float CEffectManager::PARTICLE_MOVE = 20.0f;
const float CEffectManager::EXPLOSION_MOVE = 10.0f;
const float CEffectManager::BULLET_MOVE = 5.0f;

//==================================================
// 静的メンバ変数
//==================================================
CEffectManager* CEffectManager::m_pEffectManager = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CEffectManager* CEffectManager::GetInstanse()
{
	if (m_pEffectManager == nullptr)
	{// nullチェック
		m_pEffectManager = new CEffectManager;
	}

	return m_pEffectManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffectManager::CEffectManager()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffectManager::~CEffectManager()
{
}

//--------------------------------------------------
// 爆発
//--------------------------------------------------
void CEffectManager::Particle(const D3DXVECTOR3& pos, const D3DXCOLOR& col)
{
	D3DXCOLOR randomCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < MAX_PARTICLE; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_PARTICLE * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		float random = FloatRandam(PARTICLE_MOVE, 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		randomCol.r = col.r + FloatRandam(0.25f, -0.25f);
		randomCol.g = col.g + FloatRandam(0.25f, -0.25f);
		randomCol.b = col.b + FloatRandam(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos, move, randomCol);
	}
}

//--------------------------------------------------
// 爆発
//--------------------------------------------------
void CEffectManager::Explosion(const D3DXVECTOR3& pos)
{
	float red = FloatRandam(1.0f, 0.0f);
	float green = FloatRandam(1.0f, 0.0f);
	float blue = FloatRandam(1.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_EXPLOSION * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		float random = FloatRandam(EXPLOSION_MOVE, 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = red + FloatRandam(0.25f, -0.25f); 
		col.g = green + FloatRandam(0.25f, -0.25f);
		col.b = blue + FloatRandam(0.25f, -0.25f);

		// 生成
		CEffect::Create(pos, move, col);
	}
}

//--------------------------------------------------
// 弾
//--------------------------------------------------
void CEffectManager::Bullet(const D3DXVECTOR3& pos)
{
	D3DXCOLOR col = D3DXCOLOR(1.0f, 0.2f, 0.1f, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < MAX_BULLET; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_BULLET * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		float random = FloatRandam(BULLET_MOVE, 0.1f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col.r = 0.5f + FloatRandam(0.1f, -0.1f);

		// 生成
		CEffect::Create(pos, move, col);
	}
}
