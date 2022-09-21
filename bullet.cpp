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
#include "application.h"
#include "utility.h"
#include "input.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "effect_manager.h"
#include "exp.h"
#include "score.h"
#include "mode.h"
#include "game.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CBullet::SHOT_INTERVAL = 8;
const float CBullet::STD_SIZE = 25.0f;
const float CBullet::STD_MOVE = 15.0f;
const float CBullet::STD_INERTIA = 0.3f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CBullet::m_time = 0;
float CBullet::m_dest = 0.0f;
float CBullet::m_now = 0.0f;

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
// ����
//--------------------------------------------------
void CBullet::Shot()
{
	D3DXVECTOR3 rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (!CInput::GetKey()->Shot(&rot))
	{// �e�̔��˂��Ă��Ȃ�
		m_dest = 0.0f;
		m_now = 0.0f;
		m_time = 0;
		return;
	}

	if ((m_time % SHOT_INTERVAL) != 0)
	{// �C���^�[�o����
		m_time++;
		return;
	}

	if (m_time == 0)
	{// �P����
		// �ړI�̌���
		m_dest = atan2f(rot.x, rot.y);

		// �p�x�̐��K��
		NormalizeAngle(&m_dest);

		m_now = m_dest;

		// �e����
		CBullet::Create(m_now);

		m_time++;
		return;
	}

	m_time++;

	// �ړI�̌���
	m_dest = atan2f(rot.x, rot.y);

	// �p�x�̐��K��
	NormalizeAngle(&m_dest);

	float angle = m_dest - m_now;

	// �p�x�̐��K��
	NormalizeAngle(&angle);

	// �����E�������X�V (����������)
	m_now += angle * STD_INERTIA;

	// �p�x�̐��K��
	NormalizeAngle(&m_now);

	// �e����
	CBullet::Create(m_now);
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
void CBullet::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_BULLET);

	D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Bullet);
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
		float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
		float width = (CWall::STD_WIDTH * 0.5f) - size;
		float height = (CWall::STD_HEIGHT * 0.5f) - size;

		if (InRange(&pos, D3DXVECTOR3(width, height, 0.0f)))
		{// �͈͊O
			// ����
			CEffectManager::GetInstanse()->Bullet(pos);

			// ���
			CObject::Release();
			return;
		}
	}

	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	D3DXVECTOR3 targetPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float targetSize = 0.0f;
	float size = STD_SIZE * 0.5f;

	for (int i = 0; i < CObject::GetMax(CObject::CATEGORY_3D); i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY && type != CObject3D::TYPE_BODY)
		{// �w��̃^�C�v�ł͂Ȃ�
			continue;
		}

		switch (type)
		{
		case CObject3D::TYPE_BODY:
		{
			targetPos = pObject[i]->GetPos();
			targetSize = pObject[i]->GetSize().x * 0.5f;

			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// �����蔻��
				// ���
				CObject::Release();
				return;
			}
		}
			break;

		case CObject3D::TYPE_ENEMY:
		{
			CEnemy* pEnemy = (CEnemy*)pObject[i];
			targetPos = pEnemy->GetPos();
			targetSize = pEnemy->GetSize().x * 0.5f;

			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// �����蔻��
				// �o���l�̐���
				CExp::CreateAll(targetPos);

				CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

				// �X�R�A�̉��Z
				pGame->GetScore()->Add(CEnemy::STD_SCORE);

				// �G�̉��
				pObject[i]->Release();
				return;
			}
		}
			break;

		default:
			assert(false);
			break;
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

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
}