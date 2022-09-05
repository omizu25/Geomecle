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
#include "number_manager.h"
#include "utility.h"
#include <assert.h>

//--------------------------------------------------
// ����
//--------------------------------------------------
CTime* CTime::Create(const D3DXVECTOR3& pos, int start, int end)
{
	CTime* pTime = nullptr;

	pTime = new CTime;

	if (pTime != nullptr)
	{// null�`�F�b�N
		// ������
		pTime->Init(pos);
		pTime->SetStart(start);
		pTime->SetEnd(end);
	}

	return pTime;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CTime::CTime() :
	m_pNumber(nullptr),
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
	assert(m_pNumber == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CTime::Init(const D3DXVECTOR3& pos)
{
	m_start = 0;
	m_elapsed = 0;
	m_end = 0;

	// ���̐���
	m_pNumber = CNumberManager::Create(pos, 0);
	m_pNumber->SetZero(true);
	m_pNumber->SetZeroDigit(4);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CTime::Uninit()
{
	// ���
	m_pNumber->Release();

	m_pNumber = nullptr;
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CTime::Update()
{
	int time = timeGetTime();

	time %= (int)powf(10.0f, (float)Digit(time) - 3.0f);	// ������
	time /= 10;	// �����

	m_elapsed = time - m_start;

	int number = m_end - m_elapsed - 1000;

	// ���̕ύX
	m_pNumber->ChangeNumber(number);
}

//--------------------------------------------------
// �J�n���Ԃ̐ݒ�
//--------------------------------------------------
void CTime::SetStart(int start)
{
	m_start = start;

	m_start %= (int)powf(10.0f, (float)Digit(m_start) - 3.0f);	// ������
	m_start /= 10;	// �����
}

//--------------------------------------------------
// �I�����Ԃ̐ݒ�
//--------------------------------------------------
void CTime::SetEnd(int end)
{
	m_end = end;
}
