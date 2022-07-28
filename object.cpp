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
#include "application.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
const int CObject::MAX_OBJECT[]
{
	1024,
	30000,
	64
};


//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CObject::m_numAll = 0;
CObject** CObject::m_pObject[CATEGORY_MAX];

//--------------------------------------------------
// ����
//--------------------------------------------------
void CObject::Create()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		m_pObject[i] = new CObject* [MAX_OBJECT[i]];
	}

	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			m_pObject[numCat][numObj] = nullptr;
		}
	}
}

//--------------------------------------------------
// �j��
//--------------------------------------------------
void CObject::Delete()
{
	// �S�Ẳ��
	ReleaseAll(true);

	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		delete[] m_pObject[i];
	}
}

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObject::ReleaseAll(bool releaseKeep)
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			if (!releaseKeep && m_pObject[numCat][numObj]->m_keep)
			{// �L�[�v���Ă�����͉̂�����Ȃ�
				continue;
			}

			// �I�u�W�F�N�g�̊J��
			m_pObject[numCat][numObj]->Release();
		}
	}
}

//--------------------------------------------------
// �S�Ă̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			// �I�u�W�F�N�g�̍X�V
			m_pObject[numCat][numObj]->Update();
		}
	}
}

//--------------------------------------------------
// �S�Ă̕`��
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int numCat = 0; numCat < CATEGORY_MAX; numCat++)
	{
		if (numCat == CATEGORY_2D)
		{// �w��̒l�Ɠ���
			// �f�o�C�X�ւ̃|�C���^�̎擾
			LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

			// �����_�[�X�e�[�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		for (int numObj = 0; numObj < MAX_OBJECT[numCat]; numObj++)
		{
			if (m_pObject[numCat][numObj] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			// �I�u�W�F�N�g�̕`��
			m_pObject[numCat][numObj]->Draw();
		}

		if (numCat == CATEGORY_2D)
		{// �w��̒l�Ɠ���
			// �f�o�C�X�ւ̃|�C���^�̎擾
			LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

			// �����_�[�X�e�[�g�����ɖ߂�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		}
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
// �ő吔�̎擾
//--------------------------------------------------
int CObject::GetMax(ECategory cat)
{
	return MAX_OBJECT[cat];
}

//--------------------------------------------------
// �I�u�W�F�N�g�̎擾
//--------------------------------------------------
CObject** CObject::GetMyObject(ECategory cat)
{
	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	return m_pObject[cat];
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject::CObject(ECategory cat) :
	m_keep(false)
{
	static_assert(sizeof(MAX_OBJECT) / sizeof(MAX_OBJECT[0]) == CATEGORY_MAX, "aho");

	assert(cat > CATEGORY_NONE && cat < CATEGORY_MAX);

	for (int i = 0; i < MAX_OBJECT[cat]; i++)
	{
		if (m_pObject[cat][i] == nullptr)
		{// null�`�F�b�N
			m_pObject[cat][i] = this;
			m_cat = cat;
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
	if (m_pObject[m_cat][m_index] != nullptr)
	{// NULL�`�F�b�N
		int index = m_index;
		int cat = m_cat;
		m_pObject[cat][index]->Uninit();
		delete m_pObject[cat][index];
		m_pObject[cat][index] = nullptr;
	}
}

//--------------------------------------------------
// �����Ǝ����Ă��邩�̐ݒ�
//--------------------------------------------------
void CObject::SetKeep(bool keep)
{
	m_keep = keep;
}
