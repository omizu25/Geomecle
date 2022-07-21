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
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CResult::CResult()
{
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CResult::CResult(EMode mode) : CMode(mode)
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
