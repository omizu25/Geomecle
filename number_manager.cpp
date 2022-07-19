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
#include <assert.h>

//==================================================
// 定義
//==================================================
const float CNumberManager::STD_WIDTH = 100.0f;
const float CNumberManager::STD_HEIGHT = 200.0f;

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
void CNumberManager::Init(const D3DXVECTOR3& pos, int value)
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

	// 数の変更
	ChangeNumber(value);
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CNumberManager::Uninit()
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
}

//--------------------------------------------------
// 桁の取得
//--------------------------------------------------
int CNumberManager::GetDigit(int value)
{
	int digit = 0;
	int saveValue = value;

	while (1)
	{// 無限ループ
		if (saveValue >= 10)
		{// 2桁以上
			saveValue /= 10;
			digit++;
		}
		else
		{// 1桁
			digit++;

			if (digit > MAX_DIGIT)
			{// 指定の値より大きい
				digit = MAX_DIGIT;
			}
			break;
		}
	}

	return digit;
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

	for (int i = 0; i < GetDigit(value); i++)
	{// 一桁ずつに分ける
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// 数の変更
		m_number[i]->Change(num[i]);
	}
}
