//**************************************************
// 
// enemy_division.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_division.h"
#include "enemy_rolling.h"
#include "application.h"
#include "player.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyDivision::MAX_MOVE = 4.0f;
const float CEnemyDivision::ROT_CHANGE = 0.2f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyDivision::CEnemyDivision() :
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyDivision::~CEnemyDivision()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CEnemyDivision::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyDivision::Uninit()
{

	// ����
	CEnemyRolling::Create(CObject3D::GetPos());

	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyDivision::Update()
{
	m_time++;

	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �z�[�~���O
	Homing(&pos, pos, posDest, MAX_MOVE);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	D3DXVECTOR3 posDiff = posDest - pos;

	float rot = atan2f(posDiff.x, posDiff.y) + (D3DX_PI * 0.25f);
	rot += (sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * ROT_CHANGE) * (D3DX_PI * 2.0f);

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
void CEnemyDivision::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyDivision::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_HomingDivision);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.0f, 1.0f, 1.0f));
}
