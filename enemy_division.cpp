//**************************************************
// 
// enemy_division.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_division.h"
#include "enemy_rolling.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyDivision::STD_MOVE = 2.5f;
const float CEnemyDivision::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyDivision::CEnemyDivision() :
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyDivision::~CEnemyDivision()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyDivision::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyDivision::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyDivision::Update()
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

			// �X�V
			CEnemy::Update();
			return;
		}

		// �����蔻��̐ݒ�
		CObject3D::SetCollision(true);

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f;

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}

	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}
	
	m_time++;

	D3DXVECTOR3 posDest = pPlayer->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �z�[�~���O
	Homing(&pos, pos, posDest, STD_MOVE + FloatRandom(STD_MOVE, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	D3DXVECTOR3 posDiff = posDest - pos;

	float rot = atan2f(posDiff.x, posDiff.y) + (D3DX_PI * 0.25f);
	rot += (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

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
void CEnemyDivision::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemyDivision::Kill()
{
	// ����
	CEnemyRolling::Create(CObject3D::GetPos());

	// �L�����ꂽ
	CEnemy::Kill();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyDivision::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}
