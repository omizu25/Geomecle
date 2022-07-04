//=============================================================================
//
// 入力処理 [input.cpp]
// Author1 : KOZUNA HIROHITO
// input.hを参照を推奨
//
//=============================================================================

//-----------------------------------------------------------------------------
//インクルードファイル
//-----------------------------------------------------------------------------
#include "input.h"

CInput *CInput::m_Input = nullptr;

//*************************************************************************************
//コンストラクタ
//*************************************************************************************
CInput::CInput()
{
	m_pKeyboard = nullptr;
}

//*************************************************************************************
//デストラクタ
//*************************************************************************************
CInput::~CInput()
{
}

//*************************************************************************************
//初期化
//*************************************************************************************
HRESULT CInput::Init(HINSTANCE hInstance, HWND hWnd)
{
	m_pKeyboard = new CInputKeyboard;

	//キーボードの初期化処理
	if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
	{
		return E_FAIL;
	}


	return S_OK;
}

//*************************************************************************************
//終了処理
//*************************************************************************************
void CInput::Uninit()
{
	if (m_pKeyboard != nullptr)
	{
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
	}

	if (m_Input != nullptr)
	{
		delete m_Input;
		m_Input = nullptr;
	}
}

//*************************************************************************************
//更新処理
//*************************************************************************************
void CInput::Update()
{
	m_pKeyboard->Update();
}

//*************************************************************************************
//インプットの生成
//*************************************************************************************
CInput *CInput::Create()
{
	m_Input = new CInput;
	return m_Input;
}

//*************************************************************************************
//プレス処理
//*************************************************************************************
bool CInput::Press(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case CInput::KEY_UP:
		if (m_pKeyboard->GetKeyboardPress(DIK_W))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetKeyboardPress(DIK_S))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetKeyboardPress(DIK_A))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetKeyboardPress(DIK_D))
		{
			return true;
		}
		break;
	case CInput::KEY_DECISION:
		if (m_pKeyboard->GetKeyboardPress(DIK_RETURN))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//トリガー処理
//*************************************************************************************
bool CInput::Trigger(STAN_DART_INPUT_KEY key)
{
	switch (key)
	{
	case CInput::KEY_UP:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_W))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_S))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_A))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_D))
		{
			return true;
		}
		break;
	case CInput::KEY_DECISION:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_RETURN))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}

//*************************************************************************************
//発射処理
//*************************************************************************************
bool CInput::Shot(D3DXVECTOR3* pRot)
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	bool shot = false;

	if (m_pKeyboard->GetKeyboardPress(DIK_UP))
	{// 上キーが押された
		vec.y += 1.0f;
		shot = true;
	}

	if (m_pKeyboard->GetKeyboardPress(DIK_DOWN))
	{// 下キーが押された
		vec.y -= 1.0f;
		shot = true;
	}

	if (m_pKeyboard->GetKeyboardPress(DIK_LEFT))
	{// 左キーが押された
		vec.x -= 1.0f;
		shot = true;
	}

	if (m_pKeyboard->GetKeyboardPress(DIK_RIGHT))
	{// 右キーが押された
		vec.x += 1.0f;
		shot = true;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// 移動してない
		return false;
	}

	if (!shot)
	{// 発射しない
		return false;
	}

	*pRot = vec;

	return true;
}