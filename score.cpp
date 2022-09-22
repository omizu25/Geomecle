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
CScore::CScore()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CScore::~CScore()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CScore::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	// ������
	CNumberManager::Init(pos, size);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CScore::Uninit()
{
	// �I��
	CNumberManager::Uninit();
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

		// ���Z
		CNumberManager::Add(score + (score * pGame->GetMul()->Get()));
	}
	else
	{
		// ���Z
		CNumberManager::Add(score);
	}
}
