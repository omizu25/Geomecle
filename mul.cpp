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
#include <assert.h>

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
	m_mul(0)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CMul::~CMul()
{
	assert(m_pNumber == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CMul::Init(const D3DXVECTOR3& pos)
{
	m_mul = 0;

	// 数の生成
	m_pNumber = CNumberManager::Create(pos, 0);
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
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CMul::Get()
{
	return m_mul;
}
