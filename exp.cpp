//**************************************************
// 
// exp.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "exp.h"
#include "wall.h"
#include "utility.h"
#include "application.h"
#include "player.h"
#include "game.h"
#include "mul.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CExp::MAX_EXP = 15;
const int CExp::STD_LIFE = 300;
const int CExp::BLINK_START = 200;
const float CExp::BLINK_SPEED = 0.1f;
const float CExp::HOMING_START = 150;
const float CExp::HOMING_SPEED = 7.5f;
const float CExp::STD_SIZE = 10.0f;
const float CExp::STD_ROTATION = 0.01f;
const float CExp::MAX_MOVE = 0.5f;
const float CExp::MAX_RADIUS = 25.0f;

//--------------------------------------------------
// �S�Ă̐���
//--------------------------------------------------
void CExp::CreateAll(const D3DXVECTOR3& pos)
{
	float rot = 0.0f;
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < MAX_EXP; i++)
	{
		rot = FloatRandom(D3DX_PI * 2.0f, 0.0f);

		vec = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(MAX_RADIUS, 0.0f);

		// ����
		Create(pos + vec, rot);
	}
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CExp* CExp::Create(const D3DXVECTOR3& pos, float rot)
{
	CExp* pExp = nullptr;

	pExp = new CExp;

	if (pExp != nullptr)
	{// null�`�F�b�N
		pExp->Init();
		pExp->SetPos(pos);
		pExp->SetMove(rot);
	}

	return pExp;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CExp::CExp() :
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_life(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CExp::~CExp()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CExp::Init()
{
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_life = 0;

	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject3D::TYPE_EXP);

	// �T�C�Y�̐ݒ�
	CObject3D::SetSize(D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f));

	// �e�N�X�`���̐ݒ�
	CObject3D::SetTexture(CTexture::LABEL_Homing);

	// �F�̐ݒ�
	CObject3D::SetCol(D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CExp::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CExp::Update()
{
	m_life++;

	if (m_life >= STD_LIFE)
	{// ����������
		// ���
		CObject::Release();
	}
	else if (m_life >= BLINK_START)
	{// �_�ŊJ�n
		D3DXCOLOR col = CObject3D::GetCol();

		col.a = SinCurve(m_life, BLINK_SPEED);

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}

	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);

	float rot = CObject3D::GetRot();

	rot += STD_ROTATION;

	// �����̐ݒ�
	CObject3D::SetRot(rot);

	// �z��
	Absorption();

	// ��
	Wall();

	// �����蔻��
	Collision();

	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CExp::Draw()
{
	// �`��
	CObject3D::Draw();
}

//--------------------------------------------------
// �ړ��ʂ̐ݒ�
//--------------------------------------------------
void CExp::SetMove(float rot)
{
	// �����̐ݒ�
	CObject3D::SetRot(rot);

	m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * FloatRandom(MAX_MOVE, 0.0f);
}

//--------------------------------------------------
// �����蔻��
//--------------------------------------------------
void CExp::Collision()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	float size = CObject3D::GetSize().x * 0.5f;

	D3DXVECTOR3 playerPos = pPlayer->GetPos();
	float playerSize = pPlayer->GetSize().x * 0.5f;

	if (CollisionCircle(pos, size, playerPos, playerSize))
	{// �����蔻��
		// �{���̉��Z
		pGame->GetMul()->Add();

		// ���
		CObject::Release();
		return;
	}
}

//==================================================
// �z��
//==================================================
void CExp::Absorption()
{
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
	CPlayer* pPlayer = pGame->GetPlayer();

	if (pPlayer == nullptr)
	{// null�`�F�b�N
		return;
	}

	D3DXVECTOR3 pos = CObject3D::GetPos();
	D3DXVECTOR3 playerPos = pPlayer->GetPos();

	D3DXVECTOR3 vecDiff = playerPos - pos;

	float length = D3DXVec3Length(&vecDiff);

	if (length <= HOMING_START)
	{// �z�[�~���O����
		// �z�[�~���O
		Homing(&pos, pos, playerPos, HOMING_SPEED);
	}

	// �ʒu�̐ݒ�
	CObject3D::SetPos(pos);
}

//==================================================
// ��
//==================================================
void CExp::Wall()
{
	D3DXVECTOR3 pos = CObject3D::GetPos() + m_move;
	float size = (CObject3D::GetSize().x * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// �͈͓��Ŕ���
	InRangeReflect(&pos, &m_move, D3DXVECTOR3(width, height, 0.0f));
}
