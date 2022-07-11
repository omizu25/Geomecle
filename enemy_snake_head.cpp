//**************************************************
// 
// enemy_snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_snake_head.h"
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
const float CEnemySnakeHead::MAX_SIZE = 20.0f;
const float CEnemySnakeHead::MAX_MOVE = 5.0f;
const float CEnemySnakeHead::MAX_AMPLITUDE = 3.0f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemySnakeHead::CEnemySnakeHead() :
	m_time(0),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemySnakeHead::~CEnemySnakeHead()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CEnemySnakeHead::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemySnakeHead::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemySnakeHead::Update()
{
	m_time++;

	// �ړ��ʂ̐ݒ�
	SetMove();

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �O��̈ʒu�̕ۑ�
	m_posOld = pos;

	pos.x += m_move.x;
	pos.y += m_move.y;

	float size = (MAX_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	//	�͈͓�
	InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	float rot = atan2f(m_move.x, m_move.y);

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
void CEnemySnakeHead::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemySnakeHead::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_icon_122380_256);

	// �ړ��ʂ̐ݒ�
	SetMove();

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CEnemySnakeHead::SetMove()
{
	float fRotMove, fRotDest, fRotDiff;

	// ���݂̈ړ�����(�p�x)
	fRotMove = atan2f(m_move.x, m_move.y);

	CPlayer* pPlayer = CApplication::GetInstanse()->GetPlayer();

	// �ړI�̈ړ�����(�p�x)
	fRotDest = atan2f(pPlayer->GetPos().x - GetPos().x, pPlayer->GetPos().y - GetPos().y);

	fRotDiff = fRotDest - fRotMove;	// �ړI�̈ړ������܂ł̍���

	// �p�x�̐��K��
	NormalizeAngle(&fRotDiff);

	fRotMove += fRotDiff;	// �ړ�����(�p�x)�̕␳

	// �p�x�̐��K��
	NormalizeAngle(&fRotMove);

	float sinCurve = sinf(D3DXToRadian(m_time * MAX_AMPLITUDE)) * MAX_MOVE;

	m_move.x = sinf(fRotMove) + sinCurve * sinf(fRotMove + D3DX_PI * 0.5f);
	m_move.y = cosf(fRotMove) + sinCurve * cosf(fRotMove + D3DX_PI * 0.5f);
}
