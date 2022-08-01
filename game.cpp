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
#include "utility.h"
#include "effect.h"
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
	// �v���C���[�̐���
	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();

	if (*pPlayer == nullptr)
	{// null�`�F�b�N
		*pPlayer = CPlayer::Create();
	}

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

	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();
	*pPlayer = nullptr;

	// ���
	CEnemyManager::GetInstanse()->Release();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	// �G�̃X�|�[��
	CEnemyManager::GetInstanse()->Spawn();

	// �e�̔���
	CBullet::Shot();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		D3DXVECTOR3 pos = CApplication::GetInstanse()->GetPlayer()->GetPos();

		for (int i = 0; i < 300; i++)
		{
			float rot = (D3DX_PI * 2.0f) / 300 * i;

			NormalizeAngle(&rot);

			CEffect::Create(pos, rot);
		}
	}

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
