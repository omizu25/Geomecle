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

//--------------------------------------------------
// ����
//--------------------------------------------------
CScore* CScore::Create(const D3DXVECTOR3& pos)
{
	CScore* pScore = nullptr;

	pScore = new CScore;

	if (pScore != nullptr)
	{// null�`�F�b�N
		// ������
		pScore->Init(pos);
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
void CScore::Init(const D3DXVECTOR3& pos)
{
	m_score = 0;

	D3DXVECTOR3 size = D3DXVECTOR3(CNumberManager::STD_WIDTH, CNumberManager::STD_HEIGHT, 0.0f);

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
	CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();

	// �{���̉��Z
	int mul = pGame->GetMul()->Get();

	m_score += score + (score * mul);

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
