//**************************************************
// 
// circle.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "circle.h"
#include "circle_safety.h"
#include "circle_danger.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CCircle::STD_SIZE = 200.0f;
const float CCircle::APPEAR_SPEED = 5.0f;
const float CCircle::DISAPPEAR_SPEED = 1.5f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
bool CCircle::m_collision = false;

//--------------------------------------------------
// ����
//--------------------------------------------------
CCircle* CCircle::Create(const D3DXVECTOR3& pos)
{
	CCircle* pCircle = nullptr;

	switch (CGame::GetMode())
	{
	case CGame::GAME_SAFETY_AREA:
		pCircle = new CCircleSafety;
		break;

	case CGame::GAME_DANGER_AREA:
		pCircle = new CCircleDanger;
		break;

	case CGame::GAME_NONE:
	case CGame::GAME_MAX:
	default:
		assert(false);
		break;
	}

	if (pCircle != nullptr)
	{// null�`�F�b�N
		pCircle->Init();
		pCircle->SetPos(pos);
	}

	return pCircle;
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CCircle::Collision()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	m_collision = false;

	CObject3D** pObject = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D** pEnemy = (CObject3D**)CObject::GetMyObject(CObject::CATEGORY_3D);
	CObject3D::EType type = CObject3D::TYPE_NONE;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);
	CCircle* pCircle = nullptr;
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float size = 0.0f;
	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	D3DXVECTOR3 enemyPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float enemySize = 0.0f;

	for (int i = 0; i < objMax; i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_CIRCLE)
		{// �w��̃^�C�v�ł͂Ȃ�
			continue;
		}

		pos = pObject[i]->GetPos();
		size = pObject[i]->GetSize().x * 0.5f;

		if (CollisionCircle(pos, size, playerPos, 0.0f))
		{// �����蔻��
			if (CGame::GetMode() == CGame::GAME_SAFETY_AREA)
			{// ���S�G���A���[�h
				pCircle = (CCircle*)pObject[i];

				if (pCircle->GetAppear() != CIRCLE_DISAPPEAR)
				{// ���Œ��ł͂Ȃ�
					// ����
					pCircle->SetAppear(CIRCLE_DISAPPEAR);
				}
			}

			m_collision = true;
		}

		for (int j = 0; j < objMax; j++)
		{
			if (pEnemy[j] == nullptr)
			{// null�`�F�b�N
				continue;
			}

			type = pEnemy[j]->GetType();

			if (type != CObject3D::TYPE_ENEMY)
			{// �w��̃^�C�v�ł͂Ȃ�
				continue;
			}

			enemyPos = pEnemy[j]->GetPos();
			enemySize = pEnemy[j]->GetSize().x * 0.5f;

			if (CollisionArea(pos, size, &enemyPos, enemySize))
			{// ��������
				// �ʒu�̐ݒ�
				pEnemy[j]->SetPos(enemyPos);
			}
		}
	}
}

//--------------------------------------------------
// �������Ă��邩�ǂ����̎擾
//--------------------------------------------------
bool CCircle::GetCollision()
{
	return m_collision;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCircle::CCircle() :
	m_time(0),
	m_countDownTime(0),
	m_life(0),
	m_appear(CIRCLE_NONE),
	m_countDown(false)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCircle::~CCircle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCircle::Init()
{
	m_time = 0;
	m_countDownTime = 0;
	m_life = 0;
	m_appear = CIRCLE_APPEAR;
	m_countDown = false;

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_CIRCLE);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Circle);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCircle::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCircle::Update()
{
	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CCircle::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �o��������
//--------------------------------------------------
bool CCircle::Appear()
{
	switch (m_appear)
	{
	case CIRCLE_NONE:
		break;

	case CIRCLE_APPEAR:
	{
		D3DXVECTOR3 size = CObject3D::GetSize();

		size.x += APPEAR_SPEED;
		size.y += APPEAR_SPEED;

		if ((size.x >= STD_SIZE) && (size.y >= STD_SIZE))
		{// �w��̒l�ȏ�
			size.x = STD_SIZE;
			size.y = STD_SIZE;

			m_appear = CIRCLE_NONE;
			m_time = 0;
			m_countDown = true;
		}

		// �T�C�Y�̐ݒ�
		CObject3D::SetSize(size);
	}
		break;

	case CIRCLE_DISAPPEAR:
	{
		if (m_countDown)
		{// �J�E���g�_�E��������
			m_time++;

			if (m_time >= m_countDownTime)
			{// �J�E���g�_�E���I���
				m_time = 0;
				m_countDown = false;
			}

			return false;	// ���ł��ĂȂ�
		}

		D3DXVECTOR3 size = CObject3D::GetSize();

		size.x -= DISAPPEAR_SPEED;
		size.y -= DISAPPEAR_SPEED;

		// �T�C�Y�̐ݒ�
		CObject3D::SetSize(size);

		if ((size.x <= 0.0f) && (size.y <= 0.0f))
		{// �w��̒l�ȉ�
			return true;	// ���ł���
		}
	}
		break;

	case CIRCLE_MAX:
	default:
		assert(false);
		break;
	}

	return false;	// ���ł��ĂȂ�
}

//--------------------------------------------------
// �o�������ł̐ݒ�
//--------------------------------------------------
void CCircle::SetAppear(ECircle appear)
{
	assert(appear >= CIRCLE_NONE && appear < CIRCLE_MAX);
	m_appear = appear;
}

//--------------------------------------------------
// �J�E���g�_�E���̎擾
//--------------------------------------------------
bool CCircle::GetCountDown()
{
	return m_countDown;
}

//--------------------------------------------------
// �J�E���g�_�E���̃^�C���ݒ�
//--------------------------------------------------
void CCircle::SetTime(int time)
{
	m_countDownTime = time;
}

//--------------------------------------------------
// �����̐ݒ�
//--------------------------------------------------
void CCircle::SetLife(int life)
{
	m_life = life;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CCircle::GetLife()
{
	return m_life;
}

//--------------------------------------------------
// �o�������ł̎擾
//--------------------------------------------------
CCircle::ECircle CCircle::GetAppear()
{
	return m_appear;
}
