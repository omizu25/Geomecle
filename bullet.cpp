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
#include "game.h"
#include "sound.h"
#include "circle.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CBullet::SHOT_INTERVAL = 8;
const float CBullet::STD_SIZE = 25.0f;
const float CBullet::STD_MOVE = 15.0f;
const float CBullet::STD_INERTIA = 0.4f;

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
	switch (CGame::GetMode())
	{
	case CGame::GAME_NORMAL:
		break;

	case CGame::GAME_SAFETY_AREA:
		if (!CCircle::GetCollision())
		{// �������ĂȂ�
			m_dest = 0.0f;
			m_now = 0.0f;
			m_time = 0;
			return;
		}
		break;

	case CGame::GAME_DANGER_AREA:
		if (CCircle::GetCollision())
		{// �������Ă���
			m_dest = 0.0f;
			m_now = 0.0f;
			m_time = 0;
			return;
		}
		break;

	case CGame::GAME_NONE:
	case CGame::GAME_MAX:
	default:
		assert(false);
		break;
	}

	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_BULLET_LEFT))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}

	if (pInput->Press(CInput::KEY_BULLET_RIGHT))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}

	if (pInput->Press(CInput::KEY_BULLET_UP))
	{// ��L�[�������ꂽ
		vec.y += 1.0f;
	}

	if (pInput->Press(CInput::KEY_BULLET_DOWN))
	{// ���L�[�������ꂽ
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
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
		m_dest = atan2f(vec.x, vec.y);

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
	m_dest = atan2f(vec.x, vec.y);

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

	// SE
	CApplication::GetInstanse()->GetSound()->Play(CSound::LABEL_SE_Bullet);
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

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Bullet);

	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = pPlayer->GetPos();

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);
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
	CEnemy* pEnemy = nullptr;
	float targetSize = 0.0f;
	float size = STD_SIZE * 0.5f;
	int objMax = CObject::GetMax(CObject::CATEGORY_3D);

	for (int i = 0; i < objMax; i++)
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

		targetPos = pObject[i]->GetPos();
		targetSize = pObject[i]->GetSize().x * 0.5f;

		switch (type)
		{
		case CObject3D::TYPE_BODY:
			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// �����蔻��
				// ���
				CObject::Release();
				return;
			}
			break;

		case CObject3D::TYPE_ENEMY:
			if (CollisionCircle(pos, size, targetPos, targetSize))
			{// �����蔻��
				pEnemy = (CEnemy*)pObject[i];

				// �L��
				pEnemy->Kill();

				// �G�̉��
				pObject[i]->Release();
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