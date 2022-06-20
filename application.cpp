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
#include "object.h"
#include "object2D.h"
#include "input.h"
#include "player.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
// �t���X�N���[���ɂ��邩�ǂ���
const bool FULL_SCREEN = true;
}

//==================================================
// �ÓI�����o�ϐ�
//==================================================
CRenderer* CApplication::m_pRenderer = nullptr;
CInput* CApplication::m_pInput = nullptr;

//--------------------------------------------------
// �����_���[�̎擾
//--------------------------------------------------
LPDIRECT3DDEVICE9 CApplication::GetDevice()
{
	return m_pRenderer->GetDevice();
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

	CPlayer::Create();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CApplication::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll();

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
