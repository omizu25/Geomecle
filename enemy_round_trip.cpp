//**************************************************
// 
// enemy_round_trip.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_round_trip.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyRoundTrip::MAX_MOVE = 10.0f;

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
HRESULT CEnemyRoundTrip::Init()
{
	// ������
	CEnemy::Init();

	return S_OK;
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
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	float size = (MAX_SIZE * 0.5f) + (CWall::MAX_WIDTH * 0.5f);
	float wall = (CWall::MAX_LENGTH * 0.5f) - size;

	if (InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f)))
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
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CEnemyRoundTrip::SetMove()
{
	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	D3DXVECTOR3 posDiff = pos - CObject3D::GetPos();

	float rot = atan2f(posDiff.x, posDiff.y);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * MAX_MOVE;

	// �����̐ݒ�
	CObject3D::SetRot(rot);
}