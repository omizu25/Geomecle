//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "player.h"
#include "object2D.h"
#include "application.h"
#include "input.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer() :
	m_pObject(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPlayer::~CPlayer()
{
	assert(m_pObject == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CPlayer::Init()
{
	if (m_pObject == nullptr)
	{// null�`�F�b�N
		m_pObject = new CObject2D;
	}

	if (m_pObject != nullptr)
	{// null�`�F�b�N
		m_pObject->Init();
		m_pos = D3DXVECTOR3(CApplication::SCREEN_WIDTH * 0.5f, CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		m_pObject->SetPos(m_pos);
	}

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPlayer::Uninit()
{
	if (m_pObject != nullptr)
	{// null�`�F�b�N
		m_pObject->Uninit();
		delete m_pObject;
		m_pObject = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPlayer::Update()
{
	// �ړ�
	Move();

	if (m_pObject != nullptr)
	{// null�`�F�b�N
		m_pObject->Update();
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CPlayer::Draw()
{
	if (m_pObject != nullptr)
	{// null�`�F�b�N
		m_pObject->Draw();
	}
}

//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void CPlayer::Move()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_LEFT))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}
	if (pInput->Press(CInput::KEY_RIGHT))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}
	if (pInput->Press(CInput::KEY_UP))
	{// ��L�[�������ꂽ
		vec.y -= 1.0f;
	}
	if (pInput->Press(CInput::KEY_DOWN))
	{// ���L�[�������ꂽ
		vec.y += 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// �ړ����ĂȂ�
		return;
	}

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	// �ړ�
	m_pos.x += vec.x * 7.0f;
	m_pos.y += vec.y * 7.0f;

	// �ʒu�̐ݒ�
	m_pObject->SetPos(m_pos);
}
