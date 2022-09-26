//**************************************************
// 
// enemy_round_trip.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_round_trip.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyRoundTrip::STD_MOVE = 7.5f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyRoundTrip::CEnemyRoundTrip() : 
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyRoundTrip::~CEnemyRoundTrip()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyRoundTrip::Init()
{
	// ������
	CEnemy::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyRoundTrip::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyRoundTrip::Update()
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

	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	if (InRange(&pos, D3DXVECTOR3(width, height, 0.0f)))
	{// �͈͓�
		m_move *= -1.0f;

		float rot = CObject3D::GetRot();

		rot += D3DX_PI;

		// �p�x�̐��K��
		NormalizeAngle(&rot);

		// �����̐ݒ�
		CObject3D::SetRot(rot);
	}

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �X�V
	CEnemy::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemyRoundTrip::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemyRoundTrip::Kill()
{
	// �L�����ꂽ
	CEnemy::Kill();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyRoundTrip::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_PaperAirplane);

	// �ړ��ʂ̐ݒ�
	SetMove();

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CEnemyRoundTrip::SetMove()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetPos();

	D3DXVECTOR3 posDiff = pos - CObject3D::GetPos();

	float rot = atan2f(posDiff.x, posDiff.y);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;

	// �����̐ݒ�
	CObject3D::SetRot(rot);
}
