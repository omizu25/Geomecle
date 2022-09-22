//**************************************************
// 
// tutorial.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "tutorial.h"
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
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTutorial::CTutorial() : CMode(CMode::MODE_TUTORIAL),
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTutorial::~CTutorial()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTutorial::Init()
{
	m_time = 0;
	
	CObject2D* pTutorial = CObject2D::Create();
	pTutorial->SetPos(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f));
	pTutorial->SetSize(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f));
	pTutorial->SetTexture(CTexture::LABEL_Tutorial);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTutorial::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTutorial::Update()
{
	// �X�V
	CObject::UpdateAll();

	m_time++;

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		if (m_time >= 20)
		{// �t�F�[�h����
			Change(MODE_GAME);
			return;
		}
	}

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CTutorial::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}
