//**************************************************
// 
// score.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "score.h"
#include "number_manager.h"
#include "application.h"
#include "mode.h"
#include "game.h"
#include "mul.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CScore::STD_WIDTH = 40.0f;
const float CScore::STD_HEIGHT = 50.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CScore* CScore::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CScore* pScore = nullptr;

	pScore = new CScore;

	if (pScore != nullptr)
	{// null�`�F�b�N
		// ������
		pScore->Init(pos, size);
	}

	return pScore;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CScore::CScore() :
	m_pNumber(nullptr),
	m_score(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CScore::~CScore()
{
	assert(m_pNumber == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CScore::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_score = 0;

	// ���̐���
	m_pNumber = CNumberManager::Create(pos, size, 0);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CScore::Uninit()
{
	// ���
	m_pNumber->Release();

	m_pNumber = nullptr;
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CScore::Add(int score)
{
	CMode* pMode = CApplication::GetInstanse()->GetMode();

	if (CMode::MODE_GAME == pMode->Get())
	{// �Q�[����
		CGame* pGame = (CGame*)pMode;

		// �{���̉��Z
		int mul = pGame->GetMul()->Get();

		m_score += score + (score * mul);

		// ���̕ύX
		m_pNumber->ChangeNumber(m_score);
	}
	else
	{
		m_score += score;
	}
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CScore::Set(int score)
{
	m_score = score;

	// ���̕ύX
	m_pNumber->ChangeNumber(m_score);
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CScore::Get()
{
	return m_score;
}
