//**************************************************
// 
// enemy_escape.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_escape.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyEscape::HOMING_SPEED = 4.5f;
const float CEnemyEscape::ESCAPE_SPEED = 10.0f;
const float CEnemyEscape::ROT_CHANGE = 0.1f;
const float CEnemyEscape::STD_INERTIA = 0.07f;
const float CEnemyEscape::FIND_AREA = 100.0f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyEscape::CEnemyEscape() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_rotDir(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyEscape::~CEnemyEscape()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemyEscape::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_rotDir = false;

	// ������
	CEnemy::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyEscape::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyEscape::Update()
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

	D3DXVECTOR3 posDest = pPlayer->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �z�[�~���O
	Homing(&pos, pos, posDest, HOMING_SPEED);

	// �e���瓦����
	Escape();

	pos += m_move;

	// ����
	m_move.x += (0.0f - m_move.x) * STD_INERTIA;
	m_move.y += (0.0f - m_move.y) * STD_INERTIA;

	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	//	�͈͓�
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �����̎擾
	float rot = CObject3D::GetRot();

	if (m_rotDir)
	{// �E���
		rot += ROT_CHANGE;
	}
	else
	{// �����
		rot -= ROT_CHANGE;
	}

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
void CEnemyEscape::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemyEscape::Kill()
{
	// �L�����ꂽ
	CEnemy::Kill();
}

//--------------------------------------------------
// �e���瓦����
//--------------------------------------------------
void CEnemyEscape::Escape()
{
	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float targetSize = 0.0f;
	float targetRot = 0.0f;
	D3DXVECTOR3 pos = CObject3D::GetPos();
	D3DXVECTOR3 posDiff = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float rot = 0.0f;

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_BULLET)
		{// �e�ł͂Ȃ�
			continue;
		}

		targetPos = pObject[i]->GetPos();
		targetSize = pObject[i]->GetSize().x * 0.5f;

		if (CollisionCircle(pos, FIND_AREA, targetPos, targetSize))
		{// �����蔻��
			posDiff = targetPos - pos;

			rot = atan2f(posDiff.x, posDiff.y);

			// �����̎擾
			targetRot = pObject[i]->GetRot();

			if (targetRot >= rot)
			{
				rot += D3DX_PI;
			}
			else
			{
				rot -= D3DX_PI;
			}

			m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * ESCAPE_SPEED;
			return;
		}
	}
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyEscape::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_HomingEscape);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
	
	if (pos.x >= 0.0f)
	{// �E��
		m_rotDir = false;
	}
	else
	{// ����
		m_rotDir = true;
	}
}
