//**************************************************
// 
// enemy_windmill.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_windmill.h"
#include "application.h"
#include "game.h"
#include "utility.h"
#include "player.h"
#include "wall.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyWindmill::STD_MOVE = 2.0f;
const float CEnemyWindmill::STD_ROTATION = -0.1f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyWindmill::CEnemyWindmill() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyWindmill::~CEnemyWindmill()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyWindmill::Init()
{
	// ������
	CEnemy::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyWindmill::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyWindmill::Update()
{
	D3DXVECTOR3 pos = CObject3D::GetPos();

	pos += m_move;

	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	if (pos.x >= wall)
	{// �E�̕�
		pos.x = wall;
		m_move.x *= -1.0f;
	}
	else if (pos.x <= -wall)
	{// ���̕�
		pos.x = -wall;
		m_move.x *= -1.0f;
	}

	if (pos.y >= wall)
	{// ��̕�
		pos.y = wall;
		m_move.y *= -1.0f;
	}
	else if (pos.y <= -wall)
	{// ���̕�
		pos.y = -wall;
		m_move.y *= -1.0f;
	}

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	float rot = CObject3D::GetRot();

	rot += STD_ROTATION;

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CObject3D::SetRot(rot);

	// �X�V
	CEnemy::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemyWindmill::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyWindmill::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Windmill);

	// �ړ��ʂ̐ݒ�
	SetMove();

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CEnemyWindmill::SetMove()
{
	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	D3DXVECTOR3 posDiff = pos - CObject3D::GetPos();

	float rot = atan2f(posDiff.x, posDiff.y);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;

	// �����̐ݒ�
	CObject3D::SetRot(rot);
}