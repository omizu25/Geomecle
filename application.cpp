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
#include "input_keyboard.h"
#include "sound.h"
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
CApplication::CApplication() :
	m_pRenderer(nullptr),
	m_pKeyboard(nullptr),
	m_pSound(nullptr),
	m_pTexture(nullptr),
	m_pPlayer(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
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

	if (m_pKeyboard == nullptr)
	{
		m_pKeyboard = new CInputKeyboard;
	}

	if (m_pKeyboard != nullptr)
	{
		if (FAILED(m_pKeyboard->Init(hInstance, hWnd)))
		{// ������
			return S_FALSE;
		}
	}

	if (m_pSound == nullptr)
	{// null�`�F�b�N
		m_pSound = new CSound;
	}

	if (m_pSound != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pSound->Init(hWnd)))
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

//	m_pSound->Play(CSound::LABEL_BGM_TITLE);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CApplication::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll();

	m_pPlayer = nullptr;

//	m_pSound->Stop();
	
	if (m_pTexture != nullptr)
	{// null�`�F�b�N
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pSound != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pKeyboard != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pKeyboard->Uninit();
		delete m_pKeyboard;
		m_pKeyboard = nullptr;
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
	if (m_pKeyboard != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pKeyboard->Update();
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
// �T�E���h�̏��̎擾
//--------------------------------------------------
CInputKeyboard* CApplication::GetKeyboard()
{
	return m_pKeyboard;
}

//--------------------------------------------------
// �T�E���h�̏��̎擾
//--------------------------------------------------
CSound* CApplication::GetSound()
{
	return m_pSound;
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