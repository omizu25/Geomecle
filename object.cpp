//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "object.h"
#include "object2D.h"

#include <assert.h>

//==================================================
// 静的メンバ変数
//==================================================
int CObject::m_numAll = 0;
CObject* CObject::m_pObject[MAX_OBJECT] = {};

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの開放
		m_pObject[i]->Release();
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの更新
		m_pObject[i]->Update();
	}
}

//--------------------------------------------------
// 全ての描画
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの描画
		m_pObject[i]->Draw();
	}
}

//--------------------------------------------------
// 総数の取得
//--------------------------------------------------
int CObject::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// オブジェクトの取得
//--------------------------------------------------
CObject** CObject::GetMyObject()
{
	return m_pObject;
}

//--------------------------------------------------
// 存在するかどうか
//--------------------------------------------------
bool CObject::Exist(CObject::EType type)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// nullチェック
			continue;
		}

		if (m_pObject[i]->m_type == type)
		{// 同じ種類
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObject::CObject() : 
	m_type(CObject::TYPE_NONE)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{
			m_pObject[i] = this;
			m_index = i;
			m_numAll++;
			break;
		}
	}
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CObject::~CObject()
{
	m_numAll--;
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CObject::Release()
{
	if (m_pObject[m_index] != nullptr)
	{// NULLチェック
		int index = m_index;
		m_pObject[index]->Uninit();
		delete m_pObject[index];
		m_pObject[index] = nullptr;
	}
}

//--------------------------------------------------
// 種類の設定
//--------------------------------------------------
void CObject::SetType(CObject::EType type)
{
	m_type = type;
}

//--------------------------------------------------
// 種類の取得
//--------------------------------------------------
const CObject::EType CObject::GetType() const
{
	return m_type;
}
