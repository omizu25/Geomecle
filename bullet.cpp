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
#include "object3D.h"
#include "application.h"
#include "player.h"
#include <assert.h>

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
	m_life(0)
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
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject::TYPE_BULLET);

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_icon_122540_256);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CBullet::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CBullet::Update()
{
	m_life--;

	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �X�V
	CObject3D::Update();

	CObject** pObject = GetMyObject();

	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (pObject[i]->GetType() != CObject::TYPE_ENEMY)
		{// ��ނ��Ⴄ
			continue;
		}

		D3DXVECTOR3 enemyPos = pObject[i]->GetPos();
		float enemySize = pObject[i]->GetSize() * 0.5f;
		float size = CObject3D::GetSize() * 0.5f;

		if ((pos.y - size <= (enemyPos.y + enemySize)) &&
			(pos.y + size >= (enemyPos.y - enemySize)) &&
			(pos.x - size <= (enemyPos.x + enemySize)) &&
			(pos.x + size >= (enemyPos.x - enemySize)))
		{// �����蔻��
			pObject[i]->Release();

			// ���
			CObject::Release();
			return;
		}
	}

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
	CObject3D::Draw();
}
