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
#include "effect_manager.h"
#include "input.h"
#include "ranking.h"
#include "utility.h"
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

	{// �^�C��
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CTime::STD_WIDTH * 1.0f);
		float height = CTime::STD_HEIGHT * 0.5f + 15.0f;

		// �^�C���̐���
		m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), 45);
	}

	{// �X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = CScore::STD_HEIGHT * 0.5f + 10.0f;

		// �X�R�A�̐���
		m_pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);
	}
	
	{// �{��
		float width = (float)CApplication::SCREEN_WIDTH;
		float height = (CMul::STD_HEIGHT * 0.5f) + CScore::STD_HEIGHT + 10.0f;

		// �{���̐���
		m_pMul = CMul::Create(D3DXVECTOR3(width, height, 0.0f));
	}
	
	{// �x�X�g�X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(CScore::STD_WIDTH, CScore::STD_HEIGHT, 0.0f);
		int score = CRanking::Get(0);

		float width = (size.x * Digit(score)) + (((Digit(score) - 1) / 3) * (size.x * 0.5f));
		float height = size.y * 0.5f + 10.0f;

		// �X�R�A�̐���
		CScore* pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// �X�R�A�̐ݒ�
		pScore->Set(score);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	// �����L���O�̐ݒ�
	CRanking::Set(m_pScore->Get());
	
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

#ifdef _DEBUG

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		CPlayer* pPlayer = CApplication::GetInstanse()->GetPlayer();

		if (pPlayer != nullptr)
		{// null�`�F�b�N
			// ����
			CEffectManager::GetInstanse()->Explosion(pPlayer->GetPos());
		}
	}

	if (CInput::GetKey()->TriggerSpecific(DIK_F2))
	{// �L�[�������ꂽ
		// ���[�h�̕ύX
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);
	}

#endif // _DEBUG

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
