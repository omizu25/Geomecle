//**************************************************
// 
// enemy_homing.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_homing.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemyHoming::STD_MOVE = 3.0f;
const float CEnemyHoming::SIZE_CHANGE = 10.0f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyHoming::CEnemyHoming() :
	m_time(0),
	m_saveSize(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
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
void CEnemyHoming::Init()
{
	m_time = 0;

	// ������
	CEnemy::Init();
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
	m_time++;

	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �z�[�~���O
	Homing(&pos, pos, posDest, STD_MOVE);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	D3DXVECTOR3 size = m_saveSize;

	size.x += sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * SIZE_CHANGE;
	size.y -= sinf((m_time * 0.01f) * (D3DX_PI * 2.0f)) * SIZE_CHANGE;

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(size);

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
	CObject3D::SetTexture(CTexture::LABEL_Homing);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(0.0f, 0.75f, 1.0f, 1.0f));

	m_saveSize = CObject3D::GetSize();
}
