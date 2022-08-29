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
const float CNumberManager::STD_WIDTH = 50.0f;
const float CNumberManager::STD_HEIGHT = 100.0f;

//--------------------------------------------------
// 生成
//--------------------------------------------------
CNumberManager* CNumberManager::Create(const D3DXVECTOR3& pos, int value, bool zero)
{
	CNumberManager* pNumberManager = nullptr;

	pNumberManager = new CNumberManager;

	if (pNumberManager != nullptr)
	{// nullチェック
		// 初期化
		pNumberManager->Init(pos);

		pNumberManager->m_zero = zero;

		// 数の変更
		pNumberManager->ChangeNumber(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0)
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
void CNumberManager::Init(const D3DXVECTOR3& pos)
{
	float halfWidth = STD_WIDTH * 0.5f;

	D3DXVECTOR3 addPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		addPos.x = halfWidth + (STD_WIDTH * i);

		// 生成
		m_number[i] = CNumber::Create(pos - addPos);
		m_number[i]->SetSize(D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f));
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
		return;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i]->SetDraw(false);
	}

	for (int i = 0; i < Digit(m_value); i++)
	{
		m_number[i]->SetDraw(true);
	}
}
