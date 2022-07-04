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
#include "enemy.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CBullet::MAX_SIZE = 30.0f;
const float CBullet::MAX_MOVE = 10.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CBullet* CBullet::Create(float rot)
{
	CBullet* pBullet = nullptr;

	pBullet = new CBullet;

	if (pBullet != nullptr)
	{// null�`�F�b�N
		pBullet->Init();
		pBullet->SetMove(rot);
	}

	return pBullet;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CBullet::CBullet() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject::TYPE_BULLET);

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

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
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �X�V
	CObject3D::Update();

	{
		float size = (MAX_SIZE * 0.5f) + (CWall::MAX_WIDTH * 0.5f);
		float wall = (CWall::MAX_LENGTH * 0.5f) - size;

		if (InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f)))
		{// �͈͊O
			// ���
			CObject::Release();
			return;
		}
	}

	CObject** pObject = GetMyObject();

	for (int i = 0; i < CObject::MAX_OBJECT; i++)
	{
		if (pObject[i] == nullptr ||
			pObject[i]->GetType() != CObject::TYPE_ENEMY)
		{
			continue;
		}

		D3DXVECTOR3 enemyPos = pObject[i]->GetPos();
		float size = (MAX_SIZE * 0.5f);

		if (((pos.y - size) <= (enemyPos.y + CEnemy::MAX_SIZE)) &&
			((pos.y + size) >= (enemyPos.y - CEnemy::MAX_SIZE)) &&
			((pos.x - size) <= (enemyPos.x + CEnemy::MAX_SIZE)) &&
			((pos.x + size) >= (enemyPos.x - CEnemy::MAX_SIZE)))
		{// �����蔻��
			// �G�̉��
			pObject[i]->Release();

			// ���
			CObject::Release();
			return;
		}
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

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CBullet::SetMove(float rot)
{
	// �����̐ݒ�
	CObject3D::SetRot(rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * MAX_MOVE;
}