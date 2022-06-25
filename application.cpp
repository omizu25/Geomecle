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
#include "input_keyboard.h"
#include "sound.h"
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
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pKeyboard(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr),
	m_pPlayer(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pRenderer == nullptr);
	assert(m_pKeyboard == nullptr);
	assert(m_pSound == nullptr);
	assert(m_pTexture == nullptr);
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

	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard;
	}

	if (m_pKeyboard != nullptr)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{// 初期化
			return S_FALSE;
		}
	}

	if (m_pSound == nullptr)
	{// nullチェック
		m_pSound = new CSound;
	}

	if (m_pSound != nullptr)
	{// nullチェック
		if (FAILED(m_pSound->Init(hWnd)))
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

//	m_pSound->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//--------------------------------------------------
// 終了
//--------------------------------------------------
void CApplication::Uninit()
{
	// 全ての解放
	CObject::ReleaseAll();

	m_pPlayer = nullptr;

//	m_pSound->Stop();
	
	if (m_pTexture != nullptr)
	{// nullチェック
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pSound != nullptr)
	{// nullチェック
		// 終了
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{// nullチェック
		// 終了
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
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
	if (m_pKeyboard != nullptr)
	{// nullチェック
		// 更新
		m_pKeyboard->Update();
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
// サウンドの情報の取得
//--------------------------------------------------
CInputKeyboard* CApplication::GetKeyboard()
{
	return m_pKeyboard;
}

//--------------------------------------------------
// サウンドの情報の取得
//--------------------------------------------------
CSound* CApplication::GetSound()
{
	return m_pSound;
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