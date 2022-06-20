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
	// 移動
	Move();

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

//--------------------------------------------------
// 移動
//--------------------------------------------------
void CPlayer::Move()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
	}
	if (pInput->Press(CInput::KEY_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
	}
	if (pInput->Press(CInput::KEY_UP))
	{// 上キーが押された
		vec.y -= 1.0f;
	}
	if (pInput->Press(CInput::KEY_DOWN))
	{// 下キーが押された
		vec.y += 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// 移動してない
		return;
	}

	// ベクトルの正規化
	D3DXVec3Normalize(&vec, &vec);

	// 移動
	m_pos.x += vec.x * 7.0f;
	m_pos.y += vec.y * 7.0f;

	// 位置の設定
	m_pObject->SetPos(m_pos);
}
