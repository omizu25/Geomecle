//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "input_keyboard.h"
#include "sound.h"
#include "player.h"
#include "object2D.h"
#include "bullet.h"
#include "texture.h"
#include <assert.h>

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CPlayer::m_numShot = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// null�`�F�b�N
		pPlayer->Init();
	}

	return pPlayer;
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
void CPlayer::ChangeNumShot()
{
	CInputKeyboard* pInput = CApplication::GetInstanse()->GetKeyboard();

	if (pInput->GetTrigger(DIK_UP))
	{// ��L�[�������ꂽ
		m_numShot++;
	}
	if (pInput->GetTrigger(DIK_DOWN))
	{// ���L�[�������ꂽ
		m_numShot--;

		if (m_numShot <= 0)
		{// �w��̒l�ȉ�
			m_numShot = 0;
		}
	}
}

//--------------------------------------------------
// �����̕ύX
//--------------------------------------------------
int CPlayer::GetNumShot()
{
	return m_numShot;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CPlayer::Init()
{
	// ������
	CObject2D::Init();

	D3DXVECTOR3 pos = D3DXVECTOR3(CApplication::SCREEN_WIDTH * 0.5f, CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);

	// �ʒu�̐ݒ�
	CObject2D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::LABEL_icon_122380_256);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPlayer::Uninit()
{
	// �I��
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPlayer::Update()
{
	CInputKeyboard* pInput = CApplication::GetInstanse()->GetKeyboard();

	if (pInput->GetTrigger(DIK_SPACE))
	{// �X�y�[�X�L�[�������ꂽ
		for (int i = 0; i < m_numShot; i++)
		{
			CBullet::Create();
		}

		if (m_numShot > 0)
		{// �w��̒l����
			CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_ENTER);
		}
	}

	// �ړ�
	Move();

	// �X�V
	CObject2D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CPlayer::Draw()
{
	// �`��
	CObject2D::Draw();
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CPlayer::GetPos() const
{
	return CObject2D::GetPos();
}

//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void CPlayer::Move()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInputKeyboard* pInput = CApplication::GetInstanse()->GetKeyboard();

	if (pInput->GetPress(DIK_A))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}
	
	if (pInput->GetPress(DIK_D))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}
	
	if (pInput->GetPress(DIK_W))
	{// ��L�[�������ꂽ
		vec.y -= 1.0f;
	}
	
	if (pInput->GetPress(DIK_S))
	{// ���L�[�������ꂽ
		vec.y += 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// �ړ����ĂȂ�
		return;
	}

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	D3DXVECTOR3 pos = CObject2D::GetPos();

	// �ړ�
	pos.x += vec.x * 7.0f;
	pos.y += vec.y * 7.0f;

	// �ʒu�̐ݒ�
	CObject2D::SetPos(pos);
}
