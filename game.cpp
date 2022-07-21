//**************************************************
// 
// game.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "game.h"
#include "application.h"
#include "camera.h"
#include "player.h"
#include "enemy_manager.h"
#include "bullet.h"
#include "input.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame()
{
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CGame::CGame(EMode mode) : CMode(mode)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	// �ǂݍ���
	CEnemyManager::GetInstanse()->Load();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);

	// ���
	CEnemyManager::GetInstanse()->Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		Change(MODE_RESULT);
		return;
	}

	// �G�̃X�|�[��
	CEnemyManager::GetInstanse()->Spawn();

	// �e�̔���
	CBullet::Shot();

	// �X�V
	CObject::UpdateAll();

	// �J�����̍X�V
	CApplication::GetInstanse()->GetCamera()->Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CGame::Draw()
{
	// �J�����̐ݒ�
	CApplication::GetInstanse()->GetCamera()->Set();

	// �`��
	CObject::DrawAll();
}
