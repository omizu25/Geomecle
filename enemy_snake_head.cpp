//**************************************************
// 
// enemy_snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_snake_head.h"
#include "enemy_snake_body.h"
#include "application.h"
#include "utility.h"
#include "game.h"
#include "player.h"
#include "wall.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEnemySnakeHead::MAX_BODY = 25;
const int CEnemySnakeHead::IDX_PARENT = 0;
const float CEnemySnakeHead::STD_SIZE = 35.0f;
const float CEnemySnakeHead::STD_MOVE = 2.0f;
const float CEnemySnakeHead::AMPLITUDE_WIDTH = 3.0f;
const float CEnemySnakeHead::AMPLITUDE_SPEED = 2.0f;

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
void CEnemySnakeHead::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemySnakeHead::Uninit()
{
	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		// ���
		m_pBody[i]->Release();
		m_pBody[i] = nullptr;
	}

	if (m_pBody != nullptr)
	{// null�`�F�b�N
		delete[] m_pBody;
		m_pBody = nullptr;
	}

	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemySnakeHead::Update()
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

			for (int i = 0; i < MAX_BODY; i++)
			{
				if (m_pBody[i] == nullptr)
				{// null�`�F�b�N
					continue;
				}

				// �F�̎擾
				D3DXCOLOR colBody = m_pBody[i]->GetCol();

				colBody.a = SinCurve(time, 0.1f) * 0.5f;

				// �F�̐ݒ�
				m_pBody[i]->SetCol(colBody);

				// �����蔻��̐ݒ�
				m_pBody[i]->SetCollision(false);
			}

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

		for (int i = 0; i < MAX_BODY; i++)
		{
			if (m_pBody[i] == nullptr)
			{// null�`�F�b�N
				continue;
			}

			// �F�̎擾
			D3DXCOLOR colBody = m_pBody[i]->GetCol();

			colBody.a = 1.0f;

			// �F�̐ݒ�
			m_pBody[i]->SetCol(colBody);

			// �����蔻��̐ݒ�
			m_pBody[i]->SetCollision(true);
		}
	}

	m_time++;

	// �ړ��ʂ̐ݒ�
	SetMove();

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �O��̈ʒu�̕ۑ�
	m_posOld = pos;

	pos.x += m_move.x;
	pos.y += m_move.y;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	//	�͈͓�
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	if (m_pBody[IDX_PARENT] != nullptr)
	{// null�`�F�b�N
		// �ړI�̈ʒu�̐ݒ�
		m_pBody[IDX_PARENT]->SetPosDest(m_posOld);
	}

	for (int i = 0; i < MAX_BODY; i++)
	{
		if (m_pBody[i] == nullptr || i == IDX_PARENT)
		{// null�`�F�b�N
			continue;
		}

		int parent = i - 1;
		D3DXVECTOR3 posOld = m_pBody[parent]->GetPosOld();

		// �ړI�̈ʒu�̐ݒ�
		m_pBody[i]->SetPosDest(posOld);
	}

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
// �O��̈ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CEnemySnakeHead::GetPosOld() const
{
	return m_posOld;
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemySnakeHead::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	m_posOld = pos;

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Bullet);

	// �ړ��ʂ̐ݒ�
	SetMove();

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(0.0f, 0.5f, 1.0f, 1.0f));

	m_pBody = new CEnemySnakeBody*[MAX_BODY];

	for (int i = 0; i < MAX_BODY; i++)
	{
		m_pBody[i] = nullptr;
	}

	for (int i = 0; i < MAX_BODY; i++)
	{
		// ����
		m_pBody[i] = CEnemySnakeBody::Create();
		m_pBody[i]->SetPos(pos);
		m_pBody[i]->SetPosDest(pos);
	}
}

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemySnakeHead::Kill()
{
	// �L�����ꂽ
	CEnemy::Kill();
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CEnemySnakeHead::SetMove()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();
	
	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	float fRotMove, fRotDest, fRotDiff;

	// ���݂̈ړ�����(�p�x)
	fRotMove = atan2f(m_move.x, m_move.y);

	// �ړI�̈ړ�����(�p�x)
	fRotDest = atan2f(pPlayer->GetPos().x - GetPos().x, pPlayer->GetPos().y - GetPos().y);

	fRotDiff = fRotDest - fRotMove;	// �ړI�̈ړ������܂ł̍���

	// �p�x�̐��K��
	NormalizeAngle(&fRotDiff);

	fRotMove += fRotDiff;	// �ړ�����(�p�x)�̕␳

	// �p�x�̐��K��
	NormalizeAngle(&fRotMove);

	float sinCurve = sinf(D3DXToRadian(m_time * AMPLITUDE_SPEED)) * AMPLITUDE_WIDTH;

	m_move.x = (sinf(fRotMove) * (STD_MOVE + FloatRandom(STD_MOVE, 0.0f))) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	m_move.y = (cosf(fRotMove) * (STD_MOVE + FloatRandom(STD_MOVE, 0.0f))) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));

	D3DXVECTOR3 move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	move.x = (sinf(fRotMove) * STD_MOVE) + (sinCurve * sinf(fRotMove + D3DX_PI * 0.5f));
	move.y = (cosf(fRotMove) * STD_MOVE) + (sinCurve * cosf(fRotMove + D3DX_PI * 0.5f));

	float rot = atan2f(move.x, move.y);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CObject3D::SetRot(rot);
}
