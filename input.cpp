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
		if (m_pKeyboard->GetKeyboardPress(DIK_W)
			|| m_pKeyboard->GetKeyboardPress(DIK_UP))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetKeyboardPress(DIK_S)
			|| m_pKeyboard->GetKeyboardPress(DIK_DOWN))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetKeyboardPress(DIK_A)
			|| m_pKeyboard->GetKeyboardPress(DIK_LEFT))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetKeyboardPress(DIK_D)
			|| m_pKeyboard->GetKeyboardPress(DIK_RIGHT))
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
	case CInput::KEY_SHOT:
		if (m_pKeyboard->GetKeyboardPress(DIK_SPACE))
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
		if (m_pKeyboard->GetKeyboardTrigger(DIK_W)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_UP))
		{
			return true;
		}
		break;
	case CInput::KEY_DOWN:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_S)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_DOWN))
		{
			return true;
		}
		break;
	case CInput::KEY_LEFT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_A)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_LEFT))
		{
			return true;
		}
		break;
	case CInput::KEY_RIGHT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_D)
			|| m_pKeyboard->GetKeyboardTrigger(DIK_RIGHT))
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
	case CInput::KEY_SHOT:
		if (m_pKeyboard->GetKeyboardTrigger(DIK_SPACE))
		{
			return true;
		}
		break;
	default:
		break;
	}

	return false;
}
