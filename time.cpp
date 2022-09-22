//**************************************************
// 
// time.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "time.h"
#include "utility.h"
#include "application.h"
#include "mode.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CTime::STD_WIDTH = 50.0f;
const float CTime::STD_HEIGHT = 60.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CTime* CTime::Create(const D3DXVECTOR3& pos, int start, int end)
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime != nullptr)
	{// null�`�F�b�N
		D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

		// ������
		pTime->Init(pos, size);
		pTime->m_start = start;
		pTime->m_end = end;
	}

	return pTime;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTime::CTime() :
	m_start(0),
	m_elapsed(0),
	m_end(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CTime::~CTime()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTime::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_start = 0;
	m_elapsed = 0;
	m_end = 0;

	// ������
	CNumberManager::Init(pos, size);
	CNumberManager::SetZero(true);
	CNumberManager::SetZeroDigit(4);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTime::Uninit()
{
	// �I��
	CNumberManager::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTime::Update()
{
	int time = timeGetTime();

	m_elapsed = (time - m_start) / 10;

	int number = m_end - m_elapsed;

	// ���̕ύX
	CNumberManager::Set(number);

	if (number <= 0)
	{// ���Ԑ؂�
		// ���[�h�̕ύX
		CApplication::GetInstanse()->GetMode()->Change(CMode::MODE_RESULT);
	}
}
