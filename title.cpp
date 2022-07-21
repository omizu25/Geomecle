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
#include "number_manager.h"
#include "input.h"
#include "object2D.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTitle::CTitle()
{
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CTitle::CTitle(EMode mode) : CMode(mode)
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
