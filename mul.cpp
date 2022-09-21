//**************************************************
// 
// mul.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "mul.h"
#include "number_manager.h"
#include "object2D.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CMul::STD_WIDTH = 22.5f;
const float CMul::STD_HEIGHT = 30.0f;
const float CMul::MUL_SIZE = 20.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CMul* CMul::Create(const D3DXVECTOR3& pos)
{
	CMul* pMul = nullptr;

	pMul = new CMul;

	if (pMul != nullptr)
	{// nullチェック
		// 初期化
		pMul->Init(pos);
	}

	return pMul;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CMul::CMul() :
	m_pNumber(nullptr),
	m_pMul(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_mul(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMul::~CMul()
{
	assert(m_pNumber == nullptr);
	assert(m_pMul == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CMul::Init(const D3DXVECTOR3& pos)
{
	m_mul = 0;
	m_pos = pos;

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	// 数の生成
	m_pNumber = CNumberManager::Create(m_pos, size, 0);

	// 掛けるの生成
	m_pMul = CObject2D::Create();

	// サイズの設定
	m_pMul->SetSize(D3DXVECTOR3(MUL_SIZE, MUL_SIZE, 0.0f));

	float PosX = m_pos.x - (Digit(m_mul) * STD_WIDTH) - (MUL_SIZE * 0.5f);

	// 位置の設定
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));

	// テクスチャの設定
	m_pMul->SetTexture(CTexture::LABEL_Mul);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CMul::Uninit()
{
	// 解放
	m_pNumber->Release();

	m_pNumber = nullptr;
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CMul::Add()
{
	m_mul++;

	// 数の変更
	m_pNumber->ChangeNumber(m_mul);

	float PosX = m_pos.x - (Digit(m_mul) * STD_WIDTH) - (MUL_SIZE * 0.5f);

	// 位置の設定
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CMul::Get()
{
	return m_mul;
}
