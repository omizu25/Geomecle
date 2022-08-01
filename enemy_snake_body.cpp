//**************************************************
// 
// enemy_snake_head.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "enemy_snake_body.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEnemySnakeBody::STD_SIZE = 15.0f;
const int CEnemySnakeBody::MOVE_INTERVAL = 2;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEnemySnakeBody* CEnemySnakeBody::Create()
{
	CEnemySnakeBody* pBody = nullptr;

	pBody = new CEnemySnakeBody;

	if (pBody != nullptr)
	{// null�`�F�b�N
		pBody->Init();
	}

	return pBody;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEnemySnakeBody::CEnemySnakeBody() :
	m_time(0),
	m_posDest(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_posOld(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEnemySnakeBody::~CEnemySnakeBody()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEnemySnakeBody::Init()
{
	m_time = 0;

	// ������
	CObject3D::Init();

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_BODY);

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Snake_Body);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(1.0f, 0.5f, 0.0f, 1.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEnemySnakeBody::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEnemySnakeBody::Update()
{
	m_time++;

	if ((m_time % MOVE_INTERVAL) != 0)
	{// ���Ԋu�̃^�C�~���O�ł͂Ȃ�
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �O��̈ʒu�̕ۑ�
	m_posOld = pos;

	// �z�[�~���O
	Homing(&pos, pos, m_posDest, 10.0f);

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	//	�͈͓�
	InRange(&pos, D3DXVECTOR3(width, height, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEnemySnakeBody::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �ړI�̈ʒu�̐ݒ�
//--------------------------------------------------
void CEnemySnakeBody::SetPosDest(const D3DXVECTOR3& posDest)
{
	m_posDest = posDest;
}

//--------------------------------------------------
// �O��̈ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CEnemySnakeBody::GetPosOld() const
{
	return m_posOld;
}
