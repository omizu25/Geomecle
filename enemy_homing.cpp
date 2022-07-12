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

//==================================================
// ��`
//==================================================
const float CEnemyHoming::MAX_MOVE = 3.0f;
const float CEnemyHoming::MAX_SIZE = 35.0f;
const float CEnemyHoming::SIZE_CHANGE = 15.0f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemyHoming::CEnemyHoming() :
	m_time(0)
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
	m_time = 0;

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
	m_time++;

	D3DXVECTOR3 posDest = CApplication::GetInstanse()->GetPlayer()->GetPos();
	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �z�[�~���O
	Homing(&pos, pos, posDest, MAX_MOVE);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	D3DXVECTOR3 size = D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f);

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

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(MAX_SIZE, MAX_SIZE, 0.0f));
}
