//**************************************************
// 
// bullet.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "bullet.h"
#include "object2D.h"
#include "application.h"
#include "player.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CBullet* CBullet::Create()
{
	CBullet* pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{// null�`�F�b�N
		pBullet->Init();
	}

	return pBullet;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CBullet::CBullet() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_life(0),
	m_index(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CBullet::~CBullet()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CBullet::Init()
{
	m_life = 60;
	m_move = D3DXVECTOR3(10.0f, 0.0f, 0.0f);

	// ������
	CObject2D::Init();

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// �ʒu�̐ݒ�
	CObject2D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject2D::SetTexture(CTexture::TEXTURE_icon_122540_256);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CBullet::Uninit()
{
	// �I��
	CObject2D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CBullet::Update()
{
	m_life--;

	D3DXVECTOR3 pos = CObject2D::GetPos() + m_move;

	// �ʒu�̐ݒ�
	CObject2D::SetPos(pos);

	// �X�V
	CObject2D::Update();

	if (m_life <= 0)
	{// �̗͂��S���Ȃ���
		// ���
		CObject::Release();
		return;
	}

	if (pos.x >= CApplication::SCREEN_WIDTH)
	{// ��ʂ̍��[���z����
		// ���
		CObject::Release();
		return;
	}
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CBullet::Draw()
{
	// �`��
	CObject2D::Draw();
}
