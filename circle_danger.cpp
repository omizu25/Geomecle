//**************************************************
// 
// circle_danger.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "circle_danger.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CCircleDanger::COUNTDOWN_TIME = 60;
const int CCircleDanger::MAX_LIFE = 900;
const int CCircleDanger::MIN_LIFE = 120;
const D3DXCOLOR CCircleDanger::STD_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCircleDanger::CCircleDanger() :
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCircleDanger::~CCircleDanger()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCircleDanger::Init()
{
	m_time = 0;

	// ������
	CCircle::Init();

	// �F�̐ݒ�
	CObject3D::SetCol(STD_COLOR);

	// ���C�t�̐ݒ�
	CCircle::SetLife(IntRandom(MAX_LIFE, MIN_LIFE));

	// �J�E���g�_�E���̎��Ԃ̐ݒ�
	CCircle::SetTime(COUNTDOWN_TIME);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCircleDanger::Uninit()
{
	// �I��
	CCircle::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCircleDanger::Update()
{
	// �X�V
	CCircle::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CCircleDanger::Draw()
{
	// �`��
	CCircle::Draw();
}

//--------------------------------------------------
// �o��������
//--------------------------------------------------
bool CCircleDanger::Appear()
{
	if (CCircle::GetAppear() != CCircle::CIRCLE_DISAPPEAR)
	{// ���Œ��ł͂Ȃ�
		// �o��������
		return CCircle::Appear();
	}

	/* ���Œ� */

	if (CCircle::GetCountDown())
	{// �J�E���g�_�E����
		m_time++;

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}
	else
	{// �J�E���g�_�E�����Ă��Ȃ�
		m_time++;

		D3DXCOLOR col = CObject3D::GetCol();

		col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}

	// �o��������
	return CCircle::Appear();
}

//--------------------------------------------------
// �o�������ł̐ݒ�
//--------------------------------------------------
void CCircleDanger::SetAppear(ECircle appear)
{
	if (CCircle::GetAppear() == CCircle::CIRCLE_DISAPPEAR)
	{// ����
		m_time = 0;
	}

	// �o�������ł̐ݒ�
	CCircle::SetAppear(appear);
}
