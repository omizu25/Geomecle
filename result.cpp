//**************************************************
// 
// result.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "result.h"
#include "application.h"
#include "camera.h"
#include "object.h"
#include "number_manager.h"
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "wall.h"
#include <assert.h>

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CResult::CResult(EMode mode) : CMode(mode),
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CResult::~CResult()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CResult::Init()
{
	m_time++;

	CObject2D* pResult = CObject2D::Create();
	pResult->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pResult->SetSize(D3DXVECTOR3(1000.0f, 300.0f, 0.0f));
	pResult->SetTexture(CTexture::LABEL_Result);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CResult::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		Change(MODE_TITLE);
		return;
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CResult::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CResult::Effect()
{
	m_time++;

	if ((m_time % 5) != 0)
	{// ���Ԋu�҂�
		return;
	}

	float width = CWall::STD_WIDTH * 0.5f;
	float height = CWall::STD_HEIGHT * 0.5f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandam(width, -width), FloatRandam(height, -height), 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.r = FloatRandam(1.0f, 0.0f);
	col.g = FloatRandam(1.0f, 0.0f);
	col.b = FloatRandam(1.0f, 0.0f);

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Particle(pos, col);
}
