//**************************************************
// 
// circle_safety.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "circle_safety.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const int CCircleSafety::COUNTDOWN_TIME = 120;
const int CCircleSafety::MAX_LIFE = 1200;
const D3DXCOLOR CCircleSafety::STD_COLOR = D3DXCOLOR(0.0f, 0.0f, 1.0f, 1.0f);
const D3DXCOLOR CCircleSafety::START_COLOR = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircleSafety::END_COLOR = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
const D3DXCOLOR CCircleSafety::DIFF_COLOR = END_COLOR - START_COLOR;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CCircleSafety::CCircleSafety() :
	m_time(0),
	m_changeCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CCircleSafety::~CCircleSafety()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CCircleSafety::Init()
{
	m_time = 0;
	m_changeCol = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	// ������
	CCircle::Init();

	// �F�̐ݒ�
	CObject3D::SetCol(STD_COLOR);

	// ���C�t�̐ݒ�
	CCircle::SetLife(MAX_LIFE);

	// �J�E���g�_�E���̎��Ԃ̐ݒ�
	CCircle::SetTime(COUNTDOWN_TIME);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CCircleSafety::Uninit()
{
	// �I��
	CCircle::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CCircleSafety::Update()
{
	// �X�V
	CCircle::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CCircleSafety::Draw()
{
	// �`��
	CCircle::Draw();
}

//--------------------------------------------------
// �o��������
//--------------------------------------------------
bool CCircleSafety::Appear()
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

		float size = CObject3D::GetSize().x;

		m_changeCol = (DIFF_COLOR / ((size / DISAPPEAR_SPEED) * 0.75f));

		D3DXCOLOR col = START_COLOR;
		col.a = 1.0f - (CosCurve(m_time, 0.1f) * 0.9f);

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}
	else
	{// �J�E���g�_�E�����Ă��Ȃ�
		D3DXCOLOR col = CObject3D::GetCol();
		col.a = 1.0f;
		col += m_changeCol;

		if (col.r >= 1.0f)
		{// �ԐF�ɂȂ���
			col = END_COLOR;
		}

		// �F�̐ݒ�
		CObject3D::SetCol(col);
	}
	
	// �o��������
	return CCircle::Appear();
}

//--------------------------------------------------
// �o�������ł̐ݒ�
//--------------------------------------------------
void CCircleSafety::SetAppear(ECircle appear)
{
	if (appear == CCircle::CIRCLE_DISAPPEAR)
	{// ����
		float size = CObject3D::GetSize().x;

		m_changeCol = (DIFF_COLOR / ((size / DISAPPEAR_SPEED) * 0.75f));

		// �F�̐ݒ�
		CObject3D::SetCol(START_COLOR);
	}

	// �o�������ł̐ݒ�
	CCircle::SetAppear(appear);
}
