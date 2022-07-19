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
#include "enemy_manager.h"
#include "wall.h"
#include "number_manager.h"
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
	m_pEnemyManager(nullptr),
	m_pNumber(nullptr)
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
	assert(m_pEnemyManager == nullptr);
	assert(m_pNumber == nullptr);
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

	if (m_pEnemyManager == nullptr)
	{// nullチェック
		m_pEnemyManager = new CEnemyManager;
	}

	if (m_pEnemyManager != nullptr)
	{// nullチェック
		m_pEnemyManager->Load();
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

	// 全ての壁の生成
	CWall::AllCreate();

	// プレイヤーの生成
	m_pPlayer = CPlayer::Create();

	m_pNumber = new CNumberManager;

	if (m_pNumber != nullptr)
	{// nullチェック
		m_pNumber->Init(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT * 0.1f, 0.0f), 1);
	}

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

	if (m_pNumber != nullptr)
	{// nullチェック
		//m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}

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

	if (m_pEnemyManager != nullptr)
	{// nullチェック
		m_pEnemyManager->Release();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
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
	static int score = 1;
	score++;

	if (m_pNumber != nullptr)
	{// nullチェック
		m_pNumber->ChangeNumber(score);
	}

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

//--------------------------------------------------
// エネミーマネージャーの情報の取得
//--------------------------------------------------
CEnemyManager* CApplication::GetEnemyManager()
{
	return m_pEnemyManager;
}
