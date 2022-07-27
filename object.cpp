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
#include "application.h"

#include <assert.h>

//==================================================
// 定義
//==================================================
const int CObject::MAX_2D = 64;
const int CObject::MAX_3D = 1024;
//const int CObject::MAX_EFFECT = 30000;

const int CObject::MAX_OBJECT[CATEGORY_MAX]
{
	MAX_3D,
	MAX_EFFECT,
	MAX_2D
};

//==================================================
// 静的メンバ変数
//==================================================
int CObject::m_numAll = 0;
CObject* CObject::m_pObject[CATEGORY_MAX][MAX_EFFECT];

//--------------------------------------------------
// 全ての解放
//--------------------------------------------------
void CObject::ReleaseAll(bool releaseKeep)
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		for (int j = 0; j < MAX_OBJECT[i]; j++)
		{
			if (m_pObject[i][j] == nullptr)
			{// NULLチェック
				continue;
			}

			if (!releaseKeep && m_pObject[i][j]->m_keep)
			{// キープしてあるものは解放しない
				continue;
			}

			// オブジェクトの開放
			m_pObject[i][j]->Release();
		}
	}
}

//--------------------------------------------------
// 全ての更新
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		for (int j = 0; j < MAX_OBJECT[i]; j++)
		{
			if (m_pObject[i][j] == nullptr)
			{// NULLチェック
				continue;
			}

			// オブジェクトの更新
			m_pObject[i][j]->Update();
		}
	}
}

//--------------------------------------------------
// 全ての描画
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		if (i == CATEGORY_2D)
		{// 指定の値と同じ
			// デバイスへのポインタの取得
			LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

			// レンダーステートの設定
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		for (int j = 0; j < MAX_OBJECT[i]; j++)
		{
			if (m_pObject[i][j] == nullptr)
			{// NULLチェック
				continue;
			}

			// オブジェクトの描画
			m_pObject[i][j]->Draw();
		}

		if (i == CATEGORY_2D)
		{// 指定の値と同じ
			// デバイスへのポインタの取得
			LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

			// レンダーステートを元に戻す
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
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
// 最大数の取得
//--------------------------------------------------
int CObject::GetMax(ECategory cat)
{
	return MAX_OBJECT[cat];
}

//--------------------------------------------------
// オブジェクトの取得
//--------------------------------------------------
CObject** CObject::GetMyObject(ECategory cat)
{
	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	return m_pObject[cat];
}

//--------------------------------------------------
// 存在するかどうか
//--------------------------------------------------
bool CObject::Exist(CObject::EType type)
{
	for (int i = 0; i < MAX_3D; i++)
	{
		if (m_pObject[CATEGORY_3D][i] == nullptr)
		{// nullチェック
			continue;
		}

		if (m_pObject[CATEGORY_3D][i]->m_type == type)
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
	m_cat(CATEGORY_NONE),
	m_type(TYPE_NONE),
	m_index(0),
	m_keep(false)
{
	assert(false);
}

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
CObject::CObject(ECategory cat) :
	m_type(TYPE_NONE),
	m_keep(false)
{
	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	for (int i = 0; i < MAX_OBJECT[cat]; i++)
	{
		if (m_pObject[cat][i] == nullptr)
		{// nullチェック
			m_pObject[cat][i] = this;
			m_cat = cat;
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
	if (m_pObject[m_cat][m_index] != nullptr)
	{// NULLチェック
		int index = m_index;
		int cat = m_cat;
		m_pObject[cat][index]->Uninit();
		delete m_pObject[cat][index];
		m_pObject[cat][index] = nullptr;
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

//--------------------------------------------------
// ずっと持っているかの設定
//--------------------------------------------------
void CObject::SetKeep(bool keep)
{
	m_keep = keep;
}
