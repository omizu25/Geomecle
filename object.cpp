//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "object.h"
#include "object2D.h"

#include <assert.h>

CObject* CObject::m_pObject[MAX_POLYGON] = {};
int CObject::m_numAll = 0;

//--------------------------------------------------
// 全ての生成
//--------------------------------------------------
void CObject::CreateAll()
{
	for (int i = 0; i < CObject::MAX_POLYGON; i++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(i * (CRenderer::SCREEN_WIDTH * 0.25f), CRenderer::SCREEN_HEIGHT * 0.5f, 0.0f);

		// 生成
		CObject2D* pObject = CObject2D::Create();

		// 位置の設定
		pObject->SetPos(pos);
	}

	// 終了
	m_pObject[2]->Uninit();
}

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの終了
		m_pObject[i]->Uninit();
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
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
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULLチェック
			continue;
		}

		// オブジェクトの更新
		m_pObject[i]->Draw();
	}
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CObject::CObject()
{
	for (int i = 0; i < CObject::MAX_POLYGON; i++)
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
}

//--------------------------------------------------
// 解放
//--------------------------------------------------
void CObject::Release()
{
	if (m_pObject[m_index] != nullptr)
	{// NULLチェック
		int index = m_index;
		delete m_pObject[index];
		m_pObject[index] = nullptr;
		m_numAll = 0;
	}
}
