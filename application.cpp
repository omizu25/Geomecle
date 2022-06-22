//**************************************************
// 
// application.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "renderer.h"
#include "input.h"
#include "player.h"
#include "texture.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const bool CApplication::FULL_SCREEN = true;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CApplication* CApplication::m_pApplication = nullptr;

//--------------------------------------------------
// �C���X�^���X�̎擾
//--------------------------------------------------
CApplication* CApplication::GetInstanse()
{
	if (m_pApplication == nullptr)
	{// null�`�F�b�N
		m_pApplication = new CApplication;
	}

	return m_pApplication;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CApplication::CApplication()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CApplication::~CApplication()
{
	assert(m_pRenderer == nullptr);
	assert(m_pPlayer == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CApplication::Init(HINSTANCE hInstance, HWND hWnd)
{
	if (m_pRenderer == nullptr)
	{// null�`�F�b�N
		m_pRenderer = new CRenderer;
	}

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pRenderer->Init(hWnd, FULL_SCREEN)))
		{// ������
			return S_FALSE;
		}
	}

	// ����
	m_pInput = CInput::Create();

	if (m_pInput != nullptr)
	{
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// ������
			return S_FALSE;
		}
	}

	if (m_pTexture == nullptr)
	{// null�`�F�b�N
		m_pTexture = new CTexture;
	}

	if (m_pTexture == nullptr)
	{
		return S_FALSE;
	}

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CApplication::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll();

	if (m_pPlayer != nullptr)
	{// null�`�F�b�N
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}

	if (m_pInput != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pInput->Uninit();
	}

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pRenderer->Uninit();
		delete m_pRenderer;
		m_pRenderer = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CApplication::Update()
{
	if (m_pInput != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pInput->Update();
	}

	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �X�V����
		m_pRenderer->Update();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CApplication::Draw()
{
	if (m_pRenderer != nullptr)
	{// null�`�F�b�N
		// �`�揈��
		m_pRenderer->Draw();
	}
}

//--------------------------------------------------
// �����_���[�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
}

//--------------------------------------------------
// �e�N�X�`���̏��̎擾
//--------------------------------------------------
CTexture* CApplication::GetTexture()
{
	return m_pTexture;
}

//--------------------------------------------------
// �v���C���[�̏��̎擾
//--------------------------------------------------
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}