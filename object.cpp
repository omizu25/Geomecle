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

int CObject::m_numAll = 0;
CObject* CObject::m_pObject[CObject::MAX_OBJECT] = {};

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの終了
		m_pObject[i]->Uninit();
		delete m_pObject[i];
		m_pObject[i] = nullptr;
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < CObject::MAX_OBJECT; i++)
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
	for (int i = 0; i < CObject::MAX_OBJECT; i++)
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
// デフォルトコンストラクタ
//--------------------------------------------------
CObject::CObject()
{
	for (int i = 0; i < CObject::MAX_OBJECT; i++)
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
