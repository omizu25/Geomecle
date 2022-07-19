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
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CPlayer::STD_SIZE = 30.0f;
const float CPlayer::STD_MOVE = 5.0f;
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
HRESULT CPlayer::Init()
{
	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject::TYPE_PLAYER);

	// �ʒu�̐ݒ�
	CObject3D::SetPos(D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_icon_122380_256);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CPlayer::Uninit()
{
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

	// �ړI�̌���
	m_rotDest = atan2f(vec.x, vec.y);

	D3DXVECTOR3 pos = CObject3D::GetPos();

	// �ړ�
	pos.x += vec.x * STD_MOVE;
	pos.y += vec.y * STD_MOVE;

	float size = (STD_SIZE * 0.5f) + (CWall::GetWidth() * 0.5f);
	float wall = (CWall::GetLength() * 0.5f) - size;

	// �͈͓�
	InRange(&pos, D3DXVECTOR3(wall, wall, 0.0f));

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void CPlayer::Rot()
{
	float angle = 0.0f;

	// �p�x�̐��K��
	NormalizeAngle(&m_rotDest);

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