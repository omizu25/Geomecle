//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "application.h"
#include "object.h"
#include "object2D.h"

#include <assert.h>

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CObject::m_numAll = 0;
CObject* CObject::m_pObject[MAX_OBJECT] = {};

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̊J��
		m_pObject[i]->Release();
	}
}

//--------------------------------------------------
// �S�Ă̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̍X�V
		m_pObject[i]->Update();
	}
}

//--------------------------------------------------
// �S�Ă̕`��
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̕`��
		m_pObject[i]->Draw();
	}
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CObject::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �I�u�W�F�N�g�̎擾
//--------------------------------------------------
CObject** CObject::GetMyObject()
{
	return m_pObject;
}

//--------------------------------------------------
// ���݂��邩�ǂ���
//--------------------------------------------------
bool CObject::Exist(CObject::EType type)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (m_pObject[i]->m_type == type)
		{// �������
			return true;
		}
	}

	return false;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObject::CObject() : 
	m_type(CObject::TYPE_NONE)
{
	for (int i = 0; i < MAX_OBJECT; i++)
	{
		if (m_pObject[i] == nullptr)
		{
			m_pObject[i] = this;
			m_index = i;
			m_numAll++;
			break;
		}
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CObject::~CObject()
{
	m_numAll--;
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CObject::Release()
{
	if (m_pObject[m_index] != nullptr)
	{// NULL�`�F�b�N
		int index = m_index;
		m_pObject[index]->Uninit();
		delete m_pObject[index];
		m_pObject[index] = nullptr;
	}
}

//--------------------------------------------------
// ��ނ̐ݒ�
//--------------------------------------------------
void CObject::SetType(CObject::EType type)
{
	m_type = type;
}

//--------------------------------------------------
// ��ނ̎擾
//--------------------------------------------------
const CObject::EType CObject::GetType() const
{
	return m_type;
}
