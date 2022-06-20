//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "player.h"
#include "object2D.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
namespace
{
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CPlayer::CPlayer() :
	m_pObject(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CPlayer::~CPlayer()
{
	assert(m_pObject == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CPlayer::Init()
{
	if (m_pObject == nullptr)
	{// nullチェック
		m_pObject = new CObject2D;
	}

	if (m_pObject != nullptr)
	{// nullチェック
		m_pObject->Init();
		m_pos = D3DXVECTOR3(CApplication::SCREEN_WIDTH * 0.5f, CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		m_pObject->SetPos(m_pos);
	}

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CPlayer::Uninit()
{
	if (m_pObject != nullptr)
	{// nullチェック
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CPlayer::Update()
{
	CInput* pInput = CInput::GetKey();
	if (pInput->Press(CInput::KEY_UP))
	{
		m_pos.y += -20.0f;
		m_pObject->SetPos(m_pos);
	}
	if (pInput->Press(CInput::KEY_DOWN))
	{
		m_pos.y += 20.0f;
		m_pObject->SetPos(m_pos);
	}

	if (m_pObject != nullptr)
	{// nullチェック
		m_pObject->Update();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CPlayer::Draw()
{
	if (m_pObject != nullptr)
	{// nullチェック
		m_pObject->Draw();
	}
}
