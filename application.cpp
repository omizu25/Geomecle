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
#include "texture.h"
#include "camera.h"
#include "player.h"
#include "enemy_manager.h"
#include "wall.h"
#include "number_manager.h"
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
// �f�X�g���N�^
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

	if (m_pInput == nullptr)
	{// null�`�F�b�N
		m_pInput = CInput::Create();
	}

	if (m_pInput != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pInput->Init(hInstance, hWnd)))
		{// ������
			return E_FAIL;
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
	{// null�`�F�b�N
		return S_FALSE;
	}

	if (m_pEnemyManager == nullptr)
	{// null�`�F�b�N
		m_pEnemyManager = new CEnemyManager;
	}

	if (m_pEnemyManager != nullptr)
	{// null�`�F�b�N
		m_pEnemyManager->Load();
	}

	if (m_pCamera == nullptr)
	{// null�`�F�b�N
		m_pCamera = new CCamera;
	}

	if (m_pCamera != nullptr)
	{// null�`�F�b�N
		if (FAILED(m_pCamera->Init()))
		{// ������
			return S_FALSE;
		}
	}

	// �S�Ă̕ǂ̐���
	CWall::AllCreate();

	// �v���C���[�̐���
	m_pPlayer = CPlayer::Create();

	m_pNumber = new CNumberManager;

	if (m_pNumber != nullptr)
	{// null�`�F�b�N
		m_pNumber->Init(D3DXVECTOR3((float)SCREEN_WIDTH, (float)SCREEN_HEIGHT * 0.1f, 0.0f), 1);
	}

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

	if (m_pNumber != nullptr)
	{// null�`�F�b�N
		//m_pNumber->Uninit();
		delete m_pNumber;
		m_pNumber = nullptr;
	}

	if (m_pCamera != nullptr)
	{// null�`�F�b�N
		m_pCamera->Uninit();
		delete m_pCamera;
		m_pCamera = nullptr;
	}

	if (m_pTexture != nullptr)
	{// null�`�F�b�N
		m_pTexture->ReleaseAll();
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	if (m_pEnemyManager != nullptr)
	{// null�`�F�b�N
		m_pEnemyManager->Release();
		delete m_pEnemyManager;
		m_pEnemyManager = nullptr;
	}

	if (m_pSound != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pSound->Uninit();
		delete m_pSound;
		m_pSound = nullptr;
	}

	if (m_pInput != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pInput->Uninit();
		m_pInput = nullptr;
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
	static int score = 1;
	score++;

	if (m_pNumber != nullptr)
	{// null�`�F�b�N
		m_pNumber->ChangeNumber(score);
	}

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
// �J�����̏��̎擾
//--------------------------------------------------
CCamera* CApplication::GetCamera()
{
	return m_pCamera;
}

//--------------------------------------------------
// �v���C���[�̏��̎擾
//--------------------------------------------------
CPlayer* CApplication::GetPlayer()
{
	return m_pPlayer;
}

//--------------------------------------------------
// �G�l�~�[�}�l�[�W���[�̏��̎擾
//--------------------------------------------------
CEnemyManager* CApplication::GetEnemyManager()
{
	return m_pEnemyManager;
}
