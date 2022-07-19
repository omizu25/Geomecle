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
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CNumberManager::STD_WIDTH = 100.0f;
const float CNumberManager::STD_HEIGHT = 200.0f;

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CNumberManager::CNumberManager() :
	m_value(0)
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
void CNumberManager::Init(const D3DXVECTOR3& pos, int value)
{
	float halfWidth = STD_WIDTH * 0.5f;

	D3DXVECTOR3 addPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		addPos.x = halfWidth + (STD_WIDTH * i);

		// ����
		m_number[i] = CNumber::Create(pos - addPos);
		m_number[i]->SetSize(D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f));
	}

	// ���̕ύX
	ChangeNumber(value);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CNumberManager::Uninit()
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
}

//--------------------------------------------------
// ���̎擾
//--------------------------------------------------
int CNumberManager::GetDigit(int value)
{
	int digit = 0;
	int saveValue = value;

	while (1)
	{// �������[�v
		if (saveValue >= 10)
		{// 2���ȏ�
			saveValue /= 10;
			digit++;
		}
		else
		{// 1��
			digit++;

			if (digit > MAX_DIGIT)
			{// �w��̒l���傫��
				digit = MAX_DIGIT;
			}
			break;
		}
	}

	return digit;
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

	for (int i = 0; i < GetDigit(value); i++)
	{// �ꌅ���ɕ�����
		num[i] = saveValue % 10;
		saveValue /= 10;
	}

	for (int i = 0; i < MAX_DIGIT; i++)
	{
		// ���̕ύX
		m_number[i]->Change(num[i]);
	}
}
