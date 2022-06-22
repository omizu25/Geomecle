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

	D3DXVECTOR3 pos = D3DXVECTOR3(CApplication::SCREEN_WIDTH * 0.5f, CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);

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
