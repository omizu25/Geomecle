//**************************************************
// 
// enemy.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy.h"
#include "enemy_homing.h"
#include "enemy_round_trip.h"
#include "enemy_windmill.h"
#include "enemy_snake_head.h"
#include "enemy_division.h"
#include "enemy_rolling.h"
#include "effect_manager.h"
#include "application.h"
#include "game.h"
#include "exp.h"
#include "score.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CEnemy::STD_SCORE = 100;
const int CEnemy::CREATE_TIME = 30;
const float CEnemy::STD_SIZE = 35.0f;

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

	case CEnemy::TYPE_ROLLING:
		pEnemy = new CEnemyRolling;
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
CEnemy::CEnemy() :
	m_time(0)
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
void CEnemy::Init()
{
	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_ENEMY);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemy::Uninit()
{
	// ����
	CEffectManager::GetInstanse()->Explosion(CObject3D::GetPos());

	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemy::Update()
{
	m_time++;

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

//--------------------------------------------------
// �L�����ꂽ
//--------------------------------------------------
void CEnemy::Kill()
{
	// �o���l�̐���
	CExp::CreateAll(CObject3D::GetPos());

	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

	// �X�R�A�̉��Z
	pGame->GetScore()->Add(STD_SCORE);
}

//--------------------------------------------------
// �^�C���̎擾
//--------------------------------------------------
int CEnemy::GetTime()
{
	return m_time;
}
