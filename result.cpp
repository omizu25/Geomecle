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
#include "input.h"
#include "object2D.h"
#include "effect_manager.h"
#include "utility.h"
#include "wall.h"
#include "ranking.h"
#include "score.h"
#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CResult::CResult() : CMode(CMode::MODE_RESULT),
	m_pRanking(nullptr),
	m_time(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CResult::~CResult()
{
	assert(m_pRanking == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CResult::Init()
{
	m_time++;

	{// �����L���O
		float width = (float)CApplication::SCREEN_WIDTH - 10.0f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// �����L���O�̐���
		m_pRanking = CRanking::Create(D3DXVECTOR3(width, height, 0.0f), 40.0f);
	}

	{// �����L���O�̕�����
		float width = (float)CApplication::SCREEN_WIDTH * 0.75f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f;

		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(550.0f, 150.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_Rankig);
	}

	{// ����̃X�R�A
		D3DXVECTOR3 size = D3DXVECTOR3(CRanking::STD_WIDTH, CRanking::STD_HEIGHT, 0.0f);
		int score = CRanking::Get(-1);
		int digit = Digit(score);
		float center = (digit * (size.x * 0.5f)) + (((digit - 1) / 3) * (size.x * 0.25f));
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f + center;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.35f;

		// �X�R�A�̐���
		CScore* pScore = CScore::Create(D3DXVECTOR3(width, height, 0.0f), size);

		// �X�R�A�̐ݒ�
		pScore->Set(score);
	}

	{// �����L���O�̕�����
		float width = (float)CApplication::SCREEN_WIDTH * 0.25f;
		float height = (float)CApplication::SCREEN_HEIGHT * 0.15f - 12.5f;

		CObject2D* pObj = CObject2D::Create();
		pObj->SetPos(D3DXVECTOR3(width, height, 0.0f));
		pObj->SetSize(D3DXVECTOR3(550.0f, 100.0f, 0.0f));
		pObj->SetTexture(CTexture::LABEL_NewScore);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CResult::Uninit()
{
	// �S�Ẳ��
	CObject::ReleaseAll(false);

	m_pRanking = nullptr;
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CResult::Update()
{
	// �X�V
	CObject::UpdateAll();

	// �G�t�F�N�g
	Effect();

	// �����L���O�̍X�V
	m_pRanking->Update();

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		if (m_time >= 20)
		{// �t�F�[�h����
			Change(MODE_TITLE);
			return;
		}
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

//--------------------------------------------------
// �G�t�F�N�g
//--------------------------------------------------
void CResult::Effect()
{
	m_time++;

	if ((m_time % 10) != 0)
	{// ���Ԋu�҂�
		return;
	}

	float width = CWall::STD_WIDTH * 0.5f;
	float height = CWall::STD_HEIGHT * 0.5f;

	D3DXVECTOR3 pos = D3DXVECTOR3(FloatRandom(width, -width), FloatRandom(height, -height), 0.0f);

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.r = FloatRandom(1.0f, 0.0f);
	col.g = FloatRandom(1.0f, 0.0f);
	col.b = FloatRandom(1.0f, 0.0f);

	// �p�[�e�B�N��
	CEffectManager::GetInstanse()->Particle(pos, col);
}
