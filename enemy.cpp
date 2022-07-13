//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include "enemy_homing.h"
#include "enemy_round_trip.h"
#include "enemy_windmill.h"
#include "enemy_snake_head.h"
#include "enemy_division.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemy::MAX_SIZE = 30.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEnemy* CEnemy::Create(CEnemy::EType type, const D3DXVECTOR3& pos)
{
	CEnemy* pEnemy = nullptr;

	switch (type)
	{
	case CEnemy::TYPE_HOMING:
		pEnemy = new CEnemyHoming;
		break;

	case CEnemy::TYPE_ROUNDTRIP:
		pEnemy = new CEnemyRoundTrip;
		break;

	case CEnemy::TYPE_WINDMILL:
		pEnemy = new CEnemyWindmill;
		break;

	case CEnemy::TYPE_SNAKE:
		pEnemy = new CEnemySnakeHead;
		break;

	case CEnemy::TYPE_DIVISION:
		pEnemy = new CEnemyDivision;
		break;

	case CEnemy::TYPE_MAX:
	case CEnemy::TYPE_NONE:
	default:
		assert(false);
		break;
	}

	if (pEnemy != nullptr)
	{// null�`�F�b�N
		pEnemy->Init();
		pEnemy->Set(pos);
	}

	return pEnemy;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemy::CEnemy()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemy::~CEnemy()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CEnemy::Init()
{
	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject::TYPE_ENEMY);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemy::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemy::Update()
{
	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemy::Draw()
{
	// �`��
	CObject3D::Draw();
}
