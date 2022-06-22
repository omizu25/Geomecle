//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// インクルード
//==================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"
#include <assert.h>

//==================================================
// 定義
//==================================================
const bool CApplication::FULL_SCREEN = true;

//==================================================
// 静的メンバ変数
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// インスタンスの取得
//--------------------------------------------------
CApplication* CApplication::GetInstanse()
{
	if (m_pApplication == nullptr)
	{// nullチェック
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// デフォルトコンストラクタ
//--------------------------------------------------
CApplication::CApplication()
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pRenderer == nullptr);
	assert(m_pPlayer == nullptr);
}

//--------------------------------------------------
// 初期化
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{// nullチェック
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		if (FAILED(m_pRenderer->Init(hWnd, FULL_SCREEN)))
		{// 初期化
			return S_FALSE;
		}
	}

	// 生成
	m_pInput = CInput::Create();

	if (m_pInput != nullptr)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// 初期化
			return S_FALSE;
		}
	}

	if (m_pTexture == nullptr)
	{// nullチェック
		m_pTexture = new CTexture;
	}

	if (m_pTexture == nullptr)
	{
		return S_FALSE;
	}

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CApplication::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll();

	if (m_pPlayer != nullptr)
	{// nullチェック
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pInput != nullptr)
	{// nullチェック
		// 終了
		m_pInput->Uninit();
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 終了
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// 更新
//--------------------------------------------------
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{// nullチェック
		// 更新
		m_pInput->Update();
	}

	if (m_pRenderer != nullptr)
	{// nullチェック
		// 更新処理
		m_pRenderer->Update();
	}
}

//--------------------------------------------------
// 描画
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// nullチェック
		// 描画処理
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// レンダラーの取得
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// テクスチャの情報の取得
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// プレイヤーの情報の取得
//--------------------------------------------------
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}