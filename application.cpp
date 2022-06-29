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
#include "texture.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
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
	m_pInput(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr),
	m_pCamera(nullptr),
	m_pPlayer(nullptr),
	m_pEnemy(nullptr)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pRenderer == nullptr);
	assert(m_pInput == nullptr);
	assert(m_pSound == nullptr);
	assert(m_pTexture == nullptr);
	assert(m_pCamera == nullptr);
	assert(m_pPlayer == nullptr);
	assert(m_pEnemy == nullptr);
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

	if (m_pInput == nullptr)
	{// nullチェック
		m_pInput = CInput::Create();
	}

	if (m_pInput != nullptr)
	{// nullチェック
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// 初期化
			return E_FAIL;
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
	{// nullチェック
		return S_FALSE;
	}

	if (m_pCamera == nullptr)
	{// nullチェック
		m_pCamera = new CCamera;
	}

	if (m_pCamera != nullptr)
	{// nullチェック
		if (FAILED(m_pCamera->Init()))
		{// 初期化
			return S_FALSE;
		}
	}

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	m_pEnemy = CEnemy::Create();

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
	m_pEnemy = nullptr;

	if (m_pCamera != nullptr)
	{// nullチェック
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

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

	if (m_pInput != nullptr)
	{// nullチェック
		// 終了
		m_pInput->Uninit();
		m_pInput = nullptr;
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
// カメラの情報の取得
//--------------------------------------------------
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}

//--------------------------------------------------
// プレイヤーの情報の取得
//--------------------------------------------------
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}