//==================================================
// input_keyboard.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include <string.h>
#include "input_keyboard.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CInputKeyboard::CInputKeyboard()
{
	// �N���A
	memset(m_KeyState, 0, sizeof(m_KeyState));
	memset(m_KeyStateTrigger, 0, sizeof(m_KeyStateTrigger));
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CInputKeyboard::~CInputKeyboard()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CInputKeyboard::Init(const HINSTANCE hInstance, const HWND hWnd)
{
	return CInput::Init(hInstance, hWnd);
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void CInputKeyboard::Uninit(void)
{
	CInput::Uninit();
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void CInputKeyboard::Update(void)
{
	BYTE aKeyState[NUM_KEY_MAX];		// �L�[�{�[�h�̓��͏��

	int nCntKey;
	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(m_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			m_KeyStateTrigger[nCntKey] = (m_KeyState[nCntKey] ^ aKeyState[nCntKey]) & aKeyState[nCntKey];		// �L�[�{�[�h�̃g���K�[����ۑ�
			m_KeyState[nCntKey] = aKeyState[nCntKey];		// �L�[�{�[�h�̃v���X����ۑ�
		}
	}
	else
	{
		m_pDevKeyboard->Acquire();		// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	}
}

//--------------------------------------------------
// �L�[�{�[�h�v���X����
//--------------------------------------------------
bool CInputKeyboard::GetPress(const int nKey)
{
	return (m_KeyState[nKey] & 0x80) ? true : false;
}

//--------------------------------------------------
// �L�[�{�[�h�g���K�[����
//--------------------------------------------------
bool CInputKeyboard::GetTrigger(const int nKey)
{
	return (m_KeyStateTrigger[nKey] & 0x80) ? true : false;
}
