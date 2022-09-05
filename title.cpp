//**************************************************
// 
// title.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "title.h"
#include "application.h"
#include "camera.h"
#include "object.h"
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CTitle::CTitle(EMode mode) : CMode(mode),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f)),
	m_time(0),
	m_partCnt(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTitle::~CTitle()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTitle::Init()
{
	m_time = 0;
	m_partCnt = 0;
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	CObject2D* pTitle = CObject2D::Create();
	pTitle->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTitle->SetSize(D3DXVECTOR3(1000.0f, 300.0f, 0.0f));
	pTitle->SetTexture(CTexture::LABEL_Title);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTitle::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTitle::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		Change(MODE_GAME);
		return;
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTitle::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CTitle::Effect()
{
	m_time++;

	if ((m_time % 20) != 0)
	{// ���Ԋu�҂�
		return;
	}

	if (m_partCnt % 10 == 0)
	{// ���Ԋu
		m_col.r = FloatRandam(1.0f, 0.0f);
		m_col.g = FloatRandam(1.0f, 0.0f);
		m_col.b = FloatRandam(1.0f, 0.0f);
	}

	m_partCnt++;

	float width = CWall::STD_WIDTH * 0.25f;
	float height = CWall::STD_HEIGHT * 0.25f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandam(width, -width), FloatRandam(height, -height), 0.0f);

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Particle(pos, m_col);
}
