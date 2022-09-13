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
#include "number_manager.h"
#include "time.h"
#include "score.h"
#include "mul.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_pTime(nullptr),
	m_pScore(nullptr),
	m_pMul(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
	assert(m_pTime == nullptr);
	assert(m_pScore == nullptr);
	assert(m_pMul == nullptr);
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

	// ������
	CEnemyManager::GetInstanse()->Init();

	float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CNumberManager::STD_WIDTH * 2.0f);
	float height = CNumberManager::STD_HEIGHT * 0.5f;

	// �^�C���̐���
	m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), 3000);

	// �X�R�A�̐���
	m_pScore = CScore::Create(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, height, 0.0f));

	// �{���̐���
	m_pMul = CMul::Create(D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, CNumberManager::STD_HEIGHT + height, 0.0f));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);

	m_pTime = nullptr;
	m_pScore = nullptr;
	m_pMul = nullptr;

	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();
	*pPlayer = nullptr;

	// �I��
	CEnemyManager::GetInstanse()->Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CGame::Update()
{
	// �X�V
	CEnemyManager::GetInstanse()->Update();

	// �e�̔���
	CBullet::Shot();

	// �^�C���̌��Z
	m_pTime->Update();

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

//--------------------------------------------------
// �X�R�A�̎擾
//--------------------------------------------------
CScore* CGame::GetScore()
{
	return m_pScore;
}

//--------------------------------------------------
// �{���̎擾
//--------------------------------------------------
CMul* CGame::GetMul()
{
	return m_pMul;
}
