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

		// 数の設定
		pNumberManager->Set(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0),
	m_zeroDigit(0),
	m_interval(0),
	m_width(0.0f),
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
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		assert(m_number[i] == nullptr);
	}
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
void CNumberManager::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_value = 0;
	m_interval = 0;
	m_width = 0.0f;
	m_zero = false;
	m_zeroDigit = MAX_DIGIT;

	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - (halfWidth + (size.x * i));

		// 生成
		m_number[i] = CNumber::Create(D3DXVECTOR3(posX, pos.y, 0.0f), size);
	}
	
	// 変更
	Change();

	// ゼロの描画
	ZeroDraw();
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CNumberManager::Uninit()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] != nullptr)
		{
			// 終了
			m_number[i]->Uninit();
			m_number[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CNumberManager::Release()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] != nullptr)
		{
			// 解放
			m_number[i]->Release();
			m_number[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// 加算
//--------------------------------------------------
void CNumberManager::Add(int value)
{
	m_value += value;

	// 変更
	Change();
}

//--------------------------------------------------
// 設定
//--------------------------------------------------
void CNumberManager::Set(int value)
{
	m_value = value;

	// 変更
	Change();
}

//--------------------------------------------------
// 取得
//--------------------------------------------------
int CNumberManager::Get()
{
	return m_value;
}

//--------------------------------------------------
// 位置の設定
//--------------------------------------------------
void CNumberManager::SetPos(const D3DXVECTOR3& pos)
{
	float halfWidth = m_number[0]->GetSize().x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - (halfWidth + (m_number[i]->GetSize().x * i));

		// 位置の設定
		m_number[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
}

//--------------------------------------------------
// 色の設定
//--------------------------------------------------
void CNumberManager::SetCol(const D3DXCOLOR& col)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 色の設定
		m_number[i]->SetCol(col);
	}
}

//--------------------------------------------------
// ゼロの設定
//--------------------------------------------------
void CNumberManager::SetZero(bool zero)
{
	m_zero = zero;

	// ゼロの描画
	ZeroDraw();
}

//--------------------------------------------------
// ゼロの桁数の設定
//--------------------------------------------------
void CNumberManager::SetZeroDigit(int digit)
{
	m_zeroDigit = digit;

	// ゼロの描画
	ZeroDraw();
}

//--------------------------------------------------
// 間隔の設定
//--------------------------------------------------
void CNumberManager::SetInterval(int interval, float width)
{
	m_interval = interval;
	m_width = width;

	if (m_interval == 0)
	{// 間隔はいらない
		m_interval = 1;
		m_width = 0.0f;
	}

	D3DXVECTOR3 size = m_number[0]->GetSize();
	float halfWidth = size.x * 0.5f;

	D3DXVECTOR3 pos = m_number[0]->GetPos();
	pos.x += halfWidth;

	float posX = 0.0f;

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		posX = pos.x - ((halfWidth + (size.x * i)) + ((i / m_interval) * m_width));

		// 生成
		m_number[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));
	}
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

//--------------------------------------------------
// 変更
//--------------------------------------------------
void CNumberManager::Change()
{
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
