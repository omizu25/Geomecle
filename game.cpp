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
#include "pause.h"
#include "object2D.h"
#include <assert.h>

//==================================================
// �C���N���[�h
//==================================================
const int CGame::MAX_TIME = 4500;
const int CGame::PAUSE_TIME = 100;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CGame::CGame() : CMode(CMode::MODE_GAME),
	m_pPauseBG(nullptr),
	m_pPause(nullptr),
	m_pTime(nullptr),
	m_pMul(nullptr),
	m_pScore(nullptr),
	m_pBestScore(nullptr)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CGame::~CGame()
{
	assert(m_pPauseBG == nullptr);
	assert(m_pPause == nullptr);
	assert(m_pTime == nullptr);
	assert(m_pMul == nullptr);
	assert(m_pScore == nullptr);
	assert(m_pBestScore == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CGame::Init()
{
	m_pPause = nullptr;

	// �v���C���[�̐���
	CPlayer** pPlayer = CApplication::GetInstanse()->GetPlayerInstanse();

	if (*pPlayer == nullptr)
	{// null�`�F�b�N
		*pPlayer = CPlayer::Create();
	}

	// ������
	CEnemyManager::GetInstanse()->Init();

	{// �|�[�Y�̔w�i
		D3DXVECTOR3 pos = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH * 0.5f, (float)CApplication::SCREEN_HEIGHT * 0.5f, 0.0f);
		D3DXVECTOR3 size = D3DXVECTOR3((float)CApplication::SCREEN_WIDTH, (float)CApplication::SCREEN_HEIGHT, 0.0f);

		// ����
		m_pPauseBG = CObject2D::Create();

		// �ʒu�̐ݒ�
		m_pPauseBG->SetPos(pos);

		// �T�C�Y�̐ݒ�
		m_pPauseBG->SetSize(size);

		// �F�̐ݒ�
		m_pPauseBG->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.4f));

		// �`��̐ݒ�
		m_pPauseBG->SetDraw(false);
	}

	{// �^�C��
		float width = (float)CApplication::SCREEN_WIDTH * 0.5f + (CTime::STD_WIDTH * 2.25f);
		float height = CTime::STD_HEIGHT * 0.5f + 15.0f;

		// �^�C���̐���
		m_pTime = CTime::Create(D3DXVECTOR3(width, height, 0.0f), timeGetTime(), MAX_TIME);
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

		// �x�X�g�X�R�A�̐���
		m_pBestScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// �X�R�A�̐ݒ�
		m_pBestScore->Set(score);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CGame::Uninit()
{
	// �����L���O�̐ݒ�
	CRanking::Set(m_pScore->Get());

	if (m_pPause != nullptr)
	{// null�`�F�b�N
		m_pPause->Uninit();
		delete m_pPause;
		m_pPause = nullptr;
	}

	if (m_pBestScore != nullptr)
	{// null�`�F�b�N
		m_pBestScore->Uninit();
		delete m_pBestScore;
		m_pBestScore = nullptr;
	}

	if (m_pScore != nullptr)
	{// null�`�F�b�N
		m_pScore->Uninit();
		delete m_pScore;
		m_pScore = nullptr;
	}

	if (m_pTime != nullptr)
	{// null�`�F�b�N
		m_pTime->Uninit();
		delete m_pTime;
		m_pTime = nullptr;
	}

	if (m_pMul != nullptr)
	{// null�`�F�b�N
		m_pMul->Uninit();
		delete m_pMul;
		m_pMul = nullptr;
	}

	// �S�Ẳ��
	CObject::ReleaseAll(false);

	if (m_pPauseBG != nullptr)
	{// null�`�F�b�N
		m_pPauseBG = nullptr;
	}
	
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
	if (m_pPause != nullptr)
	{// null�`�F�b�N
		// �X�V
		m_pPauseBG->Update();

		bool pause = m_pPause->Update();

		if (!pause)
		{// �|�[�Y�I���
			if (m_pPause != nullptr)
			{// null�`�F�b�N
				m_pPause->Release();
				delete m_pPause;
				m_pPause = nullptr;
			}

			// �`��̐ݒ�
			m_pPauseBG->SetDraw(false);
		}

		return;
	}

	/* �|�[�Y���Ă��Ȃ� */

	if (CInput::GetKey()->TriggerSpecific(DIK_P))
	{// P�L�[�������ꂽ
		if (m_pTime->Get() <= MAX_TIME - PAUSE_TIME)
		{// �|�[�Y�\
			m_pPause = CPause::Create();

			// �`��̐ݒ�
			m_pPauseBG->SetDraw(true);

			// �t�F�[�h�̐ݒ�
			m_pPauseBG->SetFade(0.0f);
			return;
		}
	}

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

//--------------------------------------------------
// �^�C���̎擾
//--------------------------------------------------
CTime* CGame::GetTime()
{
	return m_pTime;
}