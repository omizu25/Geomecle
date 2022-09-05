//**************************************************
// 
// number_manager.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "number_manager.h"
#include "number.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CNumberManager::STD_WIDTH = 50.0f;
const float CNumberManager::STD_HEIGHT = 100.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CNumberManager* CNumberManager::Create(const D3DXVECTOR3& pos, int value)
{
	CNumberManager* pNumberManager = nullptr;

	pNumberManager = new CNumberManager;

	if (pNumberManager != nullptr)
	{// null�`�F�b�N
		// ������
		pNumberManager->Init(pos);

		// ���̕ύX
		pNumberManager->ChangeNumber(value);
	}

	return pNumberManager;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0),
	m_zeroDigit(0),
	m_zero(false)
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CNumberManager::~CNumberManager()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CNumberManager::Init(const D3DXVECTOR3& pos)
{
	m_zero = false;
	m_zeroDigit = MAX_DIGIT;

	float halfWidth = STD_WIDTH * 0.5f;

	D3DXVECTOR3 addPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		addPos.x = halfWidth + (STD_WIDTH * i);

		// ����
		m_number[i] = CNumber::Create(pos - addPos);
		m_number[i]->SetSize(D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f));
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CNumberManager::Uninit()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		m_number[i] = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CNumberManager::Release()
{
	for (int i = 0; i < MAX_DIGIT; i++)
	{
		if (m_number[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		// ���
		m_number[i]->Release();
	}

	// �I��
	Uninit();
}

//--------------------------------------------------
// �[���̐ݒ�
//--------------------------------------------------
void CNumberManager::SetZero(bool zero)
{
	m_zero = zero;
}

//--------------------------------------------------
// �[���̌����̐ݒ�
//--------------------------------------------------
void CNumberManager::SetZeroDigit(int digit)
{
	m_zeroDigit = digit;
}

//--------------------------------------------------
// ���̕ύX
//--------------------------------------------------
void CNumberManager::ChangeNumber(int value)
{
	m_value = value;

	int num[MAX_DIGIT];

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		num[i] = 0;
	}

	int saveValue = m_value;

	for (int i = 0; i < Digit(m_value); i++)
	{// �ꌅ���ɕ�����
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// ���̕ύX
		m_number[i]->Change(num[i]);
	}

	// �[���̕`��
	ZeroDraw();
}

//--------------------------------------------------
// �`��̐ݒ�
//--------------------------------------------------
void CNumberManager::ZeroDraw()
{
	if (m_zero)
	{// �[����`�悷��
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < m_zeroDigit; i++)
		{
			m_number[i]->SetDraw(true);
		}
	}
	else
	{// �[����`�悵�Ȃ�
		for (int i = 0; i < MAX_DIGIT; i++)
		{
			m_number[i]->SetDraw(false);
		}

		for (int i = 0; i < Digit(m_value); i++)
		{
			m_number[i]->SetDraw(true);
		}
	}
}
