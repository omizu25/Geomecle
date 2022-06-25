//==================================================
// input.cpp
// Author: Buriya Kota
//==================================================

//**************************************************
// include
//**************************************************
#include "input.h"

//**************************************************
// �ÓI�����o�ϐ�
//**************************************************
LPDIRECTINPUT8 CInput::m_pInput = nullptr;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CInput::CInput()
{
	m_pDevKeyboard = nullptr;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CInput::~CInput()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CInput::Init(const HINSTANCE hInstance, const HWND hWnd)
{
	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION,
		IID_IDirectInput8, (void**)&m_pInput, NULL)))
	{
		return E_FAIL;
	}

	// ���̓f�o�C�X�i�L�[�{�[�h�j�̐���
	if (FAILED(m_pInput->CreateDevice(GUID_SysKeyboard, &m_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}

	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(m_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}

	// �������[�h��ݒ�
	if (FAILED(m_pDevKeyboard->SetCooperativeLevel(hWnd,
		(DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	m_pDevKeyboard->Acquire();

	return S_OK;
}

//--------------------------------------------------
//�I������
//--------------------------------------------------
void CInput::Uninit()
{
	// DirectInput�I�u�W�F�N�g�̔j��
	if (m_pInput != nullptr)
	{
		m_pInput->Release();
		m_pInput = nullptr;
	}
}
