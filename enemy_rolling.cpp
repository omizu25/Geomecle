//**************************************************
// 
// enemy_rolling.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_rolling.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyRolling::STD_SIZE = 20.0f;
const float CEnemyRolling::STD_MOVE = 4.0f;
const float CEnemyRolling::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// ����
//--------------------------------------------------
void CEnemyRolling::Create(const D3DXVECTOR3& pos)
{
	{// 1�Ζ�
		CEnemyRolling* pEnemy = nullptr;

		pEnemy = new CEnemyRolling;

		if (pEnemy != nullptr)
		{// null�`�F�b�N
			pEnemy->Init();
			pEnemy->Set(pos);
			pEnemy->SetRotDir(false);
		}
	}

	{// 2�Ζ�
		CEnemyRolling* pEnemy = nullptr;

		pEnemy = new CEnemyRolling;

		if (pEnemy != nullptr)
		{// null�`�F�b�N
			pEnemy->Init();
			pEnemy->Set(pos);
			pEnemy->SetRotDir(true);
		}
	}
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyRolling::CEnemyRolling() :
	m_time(0),
	m_rotDir(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyRolling::~CEnemyRolling()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyRolling::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyRolling::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyRolling::Update()
{
	{
		int time = CEnemy::GetTime();

		if (time <= CEnemy::CREATE_TIME)
		{// �������Ԓ�

			// �F�̎擾
			D3DXCOLOR col = CObject3D::GetCol();

			col.a = SinCurve(time, 0.1f);

			// �F�̐ݒ�
			CObject3D::SetCol(col);

			// �����蔻��̐ݒ�
			CObject3D::SetCollision(false);
		}
		else
		{
			// �����蔻��̐ݒ�
			CObject3D::SetCollision(true);

			D3DXCOLOR col = CObject3D::GetCol();

			col.a = 1.0f;

			// �F�̐ݒ�
			CObject3D::SetCol(col);
		}
	}

	m_time++;

	D3DXVECTOR3 pos = CObject3D::GetPos();

	if (m_rotDir)
	{// �E���
		pos.x += sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;
	}
	else
	{// �����
		pos.x += -sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;
	}
	
	pos.y += cosf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// �͈͓�
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	float rot = (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CEnemy::SetRot(rot);

	// �X�V
	CEnemy::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemyRolling::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemyRolling::Kill()
{
	// �L�����ꂽ
	CEnemy::Kill();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyRolling::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// ��]�����̐ݒ�
//--------------------------------------------------
void CEnemyRolling::SetRotDir(bool rotDir)
{
	m_rotDir = rotDir;
}
