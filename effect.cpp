//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "effect.h"
#include "application.h"
#include "camera.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const int CEffect::MAX_EXPLOSION = 100;
const int CEffect::MAX_LIFE = 100;
const float CEffect::STD_SIZE = 20.0f;
const float CEffect::STD_MOVE = 10.0f;

//==================================================
// 静的メンバ変数
//==================================================
int CEffect::m_numAll = 0;

//--------------------------------------------------
// 爆発
//--------------------------------------------------
void CEffect::Explosion(const D3DXVECTOR3& pos)
{
	float red = FloatRandam(1.0f, 0.0f);
	float green = FloatRandam(1.0f, 0.0f);
	float blue = FloatRandam(1.0f, 0.0f);

	D3DXCOLOR col = D3DXCOLOR(red, green, blue, 1.0f);
	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < MAX_EXPLOSION; i++)
	{
		rot = (D3DX_PI * 2.0f) / MAX_EXPLOSION * i;

		// 角度の正規化
		NormalizeAngle(&rot);

		float random = FloatRandam(STD_MOVE, 0.5f);

		move.x = sinf(rot) * random;
		move.y = cosf(rot) * random;

		col = D3DXCOLOR(red + FloatRandam(0.25f, -0.25f), green + FloatRandam(0.25f, -0.25f), blue + FloatRandam(0.25f, -0.25f), 1.0f);

		// 生成
		CEffect::Create(pos, move, col);
	}
}

//--------------------------------------------------
// 生成
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& move, const D3DXCOLOR& col)
{
	if (m_numAll >= CObject::GetMax(CObject::CATEGORY_EFFECT))
	{// 最大数を越した
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;
	
	if (pEffect != nullptr)
	{// nullチェック
		pEffect->Init();
		pEffect->m_pos = pos;
		pEffect->m_move = move;
		pEffect->m_col = col;
	}

	return pEffect;
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CEffect::CEffect() : CObject(CObject::CATEGORY_EFFECT),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_life(0)
{
	m_numAll++;
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CEffect::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	m_life = MAX_LIFE;

	// キープの設定
	CObject::SetKeep(true);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CEffect::Uninit()
{
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CEffect::Update()
{
	m_life--;

	if (m_life <= 0)
	{
		CObject::Release();
		return;
	}

	m_pos += m_move;

	//慣性・移動量を更新 (減衰させる)
	m_move.x += (0.0f - m_move.x) * 0.01f;
	m_move.y += (0.0f - m_move.y) * 0.01f;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// 範囲内で反射
	InRangeReflect(&m_pos, &m_move, D3DXVECTOR3(width, height, 0.0f));	
	
	{
		float ratio = ((float)(MAX_LIFE - m_life) / MAX_LIFE);
		m_col.a = 1.0f - (ratio * ratio);
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CEffect::Draw()
{
	/* インスタンシングで描画 */
}

//--------------------------------------------------
// 位置の取得
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// 色の取得
//--------------------------------------------------
const D3DXCOLOR& CEffect::GetCol() const
{
	return m_col;
}

//--------------------------------------------------
// 移動量の取得
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetMove() const
{
	return m_move;
}
