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
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyRolling::MAX_SIZE = 17.5f;
const float CEnemyRolling::MAX_MOVE = 4.0f;
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
HRESULT CEnemyRolling::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();

	return S_OK;
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
	m_time++;

	D3DXVECTOR3 pos = CObject3D::GetPos();

	if (m_rotDir)
	{// �E���
		pos.x += sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * MAX_MOVE;
	}
	else
	{// �����
		pos.x += -sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * MAX_MOVE;
	}
	
	pos.y += cosf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * MAX_MOVE;

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
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));
}

//--------------------------------------------------
// ��]�����̐ݒ�
//--------------------------------------------------
void CEnemyRolling::SetRotDir(bool rotDir)
{
	m_rotDir = rotDir;
}
