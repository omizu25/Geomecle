//**************************************************
// 
// enemy_homing.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "input.h"
#include "sound.h"
#include "enemy_homing.h"
#include "object3D.h"
#include "bullet.h"
#include "player.h"
#include "texture.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyHoming::CEnemyHoming()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemyHoming::~CEnemyHoming()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CEnemyHoming::Init()
{
	// ������
	CEnemy::Init();

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemyHoming::Uninit()
{
	// �I��
	CEnemy::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemyHoming::Update()
{
	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	D3DXVECTOR3 posDiff = posDest - pos;

	float rot = atan2f(posDiff.x, posDiff.y);

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	// �����̐ݒ�
	CObject3D::SetRot(rot);

	// �z�[�~���O
	Homing(&pos, pos, posDest, 3.0f);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �X�V
	CEnemy::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemyHoming::Draw()
{
	// �`��
	CEnemy::Draw();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CEnemyHoming::Set(const D3DXVECTOR3& pos)
{
	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_PaperAirplane);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(0.0f, 0.75f, 1.0f, 1.0f));
}
