//**************************************************
// 
// player.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "player.h"
#include "application.h"
#include "utility.h"
#include "input.h"
#include "wall.h"
#include "enemy.h"
#include "mode.h"
#include "effect_manager.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CPlayer::STD_SIZE = 35.0f;
const float CPlayer::STD_MOVE = 6.0f;
const float CPlayer::STD_ROT = 0.1f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CPlayer* CPlayer::Create()
{
	CPlayer* pPlayer = nullptr;

	pPlayer = new CPlayer;

	if (pPlayer != nullptr)
	{// null�`�F�b�N
		pPlayer->Init();
	}

	return pPlayer;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CPlayer::CPlayer()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CPlayer::~CPlayer()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CPlayer::Init()
{
	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_PLAYER);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Player);

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Player(CObject3D::GetPos());
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPlayer::Uninit()
{
	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Player(CObject3D::GetPos());

	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CPlayer::Update()
{
	// �ړ�
	Move();

	// ����
	Rot();

	// �����蔻��
	Collision();
	
	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CPlayer::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void CPlayer::Move()
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_LEFT))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_RIGHT))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_UP))
	{// ��L�[�������ꂽ
		vec.y += 1.0f;
	}
	
	if (pInput->Press(CInput::KEY_DOWN))
	{// ���L�[�������ꂽ
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// �ړ����ĂȂ�
		return;
	}

	// ���K��
	D3DXVec3Normalize(&vec, &vec);

	// �ړI�̌���
	m_rotDest = atan2f(vec.x, vec.y);

	// �p�x�̐��K��
	NormalizeAngle(&m_rotDest);

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �ړ�
	pos.x += vec.x * STD_MOVE;
	pos.y += vec.y * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// �͈͓�
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CPlayer::Rot()
{
	float angle = 0.0f;

	float rot = CObject3D::GetRot();

	angle = m_rotDest - rot;

	// �p�x�̐��K��
	NormalizeAngle(&angle);

	//�����E�������X�V (����������)
	rot += angle * STD_ROT;

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CObject3D::SetRot(rot);
}


//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CPlayer::Collision()
{
	D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	float size = 0.0f;

	CObject3D** pObject = (CObject3D**)GetMyObject(CObject::CATEGORY_3D);

	for (int i = 0; i < CObject::GetMax(CObject::CATEGORY_3D); i++)
	{
		if (pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (!pObject[i]->GetCollision())
		{// �����蔻������Ȃ�
			continue;
		}

		CObject3D::EType type = pObject[i]->GetType();

		if (type != CObject3D::TYPE_ENEMY && type != CObject3D::TYPE_BODY)
		{// �w��̒l�ł͂Ȃ�
			continue;
		}

		switch (type)
		{
		case CObject3D::TYPE_BODY:
		{
			pos = pObject[i]->GetPos();
			size = pObject[i]->GetSize().x;
		}
		break;

		case CObject3D::TYPE_ENEMY:
		{
			CEnemy* pEnemy = (CEnemy*)pObject[i];
			pos = pEnemy->GetPos();
			size = pEnemy->GetSize().x;
		}
		break;

		default:
			assert(false);
			break;
		}

		if (CollisionCircle(CObject3D::GetPos(), CObject3D::GetSize().x * 0.25f, pos, size * 0.25f))
		{// �����蔻��
			// ���
			CObject::Release();

			CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();
			*pPlayer = nullptr;

			// ���[�h�̕ύX
			CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);
			return;
		}
	}
}