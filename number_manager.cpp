//**************************************************
// 
// number_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "number_manager.h"
#include "number.h"
#include "utility.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CNumberManager::STD_WIDTH = 40.0f;
const float CNumberManager::STD_HEIGHT = 70.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CNumberManager* CNumberManager::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int value)
{
	CNumberManager* pNumberManager = nullptr;

	pNumberManager = new CNumberManager;

	if (pNumberManager != nullptr)
	{// nullチェック
		// 初期化
		pNumberManager->Init(pos, size);

		// 数の変更
		pNumberManager->ChangeNumber(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0),
	m_zeroDigit(0),
	m_zero(false)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i] = nullptr;
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CNumberManager::~CNumberManager()
{
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CNumberManager::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_zero = false;
	m_zeroDigit = MAX_DIGIT;

	float halfWidth = size.x * 0.5f;

	D3DXVECTOR3 addPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		addPos.x = halfWidth + (size.x * i);

		// 生成
		m_number[i] = CNumber::Create(pos - addPos);
		m_number[i]->SetSize(D3DXVECTOR3(size.x, size.y, 0.0f));
	}
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CNumberManager::Uninit()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i] = nullptr;
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CNumberManager::Release()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] == nullptr)
		{// nullチェック
			continue;
		}

		// 解放
		m_number[i]->Release();
	}

	// 終了
	Uninit();
}

//--------------------------------------------------
// ゼロの設定
//--------------------------------------------------
void CNumberManager::SetZero(bool zero)
{
	m_zero = zero;
}

//--------------------------------------------------
// ゼロの桁数の設定
//--------------------------------------------------
void CNumberManager::SetZeroDigit(int digit)
{
	m_zeroDigit = digit;
}

//--------------------------------------------------
// 数の変更
//--------------------------------------------------
void CNumberManager::ChangeNumber(int value)
{
	m_value = value;

	int num[MAX_DIGIT];

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		num[i] = 0;
	}

	int saveValue = m_value;

	for (int i = 0; i < Digit(m_value); i++)
	{// 一桁ずつに分ける
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 数の変更
		m_number[i]->Change(num[i]);
	}

	// ゼロの描画
	ZeroDraw();
}

//--------------------------------------------------
// 描画の設定
//--------------------------------------------------
void CNumberManager::ZeroDraw()
{
	if (m_zero)
	{// ゼロを描画する
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < m_zeroDigit; i++)
		{
			m_number[i]->SetDraw(true);
		}
	}
	else
	{// ゼロを描画しない
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < Digit(m_value); i++)
		{
			m_number[i]->SetDraw(true);
		}
	}

	// 1桁目は絶対に描画する
	m_number[0]->SetDraw(true);
}
