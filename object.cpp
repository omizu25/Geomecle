//**************************************************
// 
// object.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "object.h"
#include "object2D.h"

#include <assert.h>

CObject* CObject::m_pObject[MAX_POLYGON] = {};
int CObject::m_numAll = 0;

//--------------------------------------------------
// �S�Ă̐���
//--------------------------------------------------
void CObject::CreateAll()
{
	for (int i = 0; i < CObject::MAX_POLYGON; i++)
	{
		D3DXVECTOR3 pos = D3DXVECTOR3(i * (CRenderer::SCREEN_WIDTH * 0.25f), CRenderer::SCREEN_HEIGHT * 0.5f, 0.0f);

		// ����
		CObject2D* pObject = CObject2D::Create();

		// �ʒu�̐ݒ�
		pObject->SetPos(pos);
	}

	// �I��
	m_pObject[2]->Uninit();
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObject::ReleaseAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̏I��
		m_pObject[i]->Uninit();
	}
}

//--------------------------------------------------
// �S�Ă̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < MAX_POLYGON; i++)
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
	for (int i = 0; i < MAX_POLYGON; i++)
	{
		if (m_pObject[i] == nullptr)
		{// NULL�`�F�b�N
			continue;
		}

		// �I�u�W�F�N�g�̍X�V
		m_pObject[i]->Draw();
	}
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CObject::CObject()
{
	for (int i = 0; i < CObject::MAX_POLYGON; i++)
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
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CObject::Release()
{
	if (m_pObject[m_index] != nullptr)
	{// NULL�`�F�b�N
		int index = m_index;
		delete m_pObject[index];
		m_pObject[index] = nullptr;
		m_numAll = 0;
	}
}
