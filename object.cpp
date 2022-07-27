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
const int CObject::MAX_2D = 64;
const int CObject::MAX_3D = 1024;
//const int CObject::MAX_EFFECT = 30000;

const int CObject::MAX_OBJECT[CATEGORY_MAX]
{
	MAX_3D,
	MAX_EFFECT,
	MAX_2D
};

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CObject::m_numAll = 0;
CObject* CObject::m_pObject[CATEGORY_MAX][MAX_EFFECT];

//--------------------------------------------------
// �S�Ẳ��
//--------------------------------------------------
void CObject::ReleaseAll(bool releaseKeep)
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		for (int j = 0; j < MAX_OBJECT[i]; j++)
		{
			if (m_pObject[i][j] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			if (!releaseKeep && m_pObject[i][j]->m_keep)
			{// �L�[�v���Ă�����͉̂�����Ȃ�
				continue;
			}

			// �I�u�W�F�N�g�̊J��
			m_pObject[i][j]->Release();
		}
	}
}

//--------------------------------------------------
// �S�Ă̍X�V
//--------------------------------------------------
void CObject::UpdateAll()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		for (int j = 0; j < MAX_OBJECT[i]; j++)
		{
			if (m_pObject[i][j] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			// �I�u�W�F�N�g�̍X�V
			m_pObject[i][j]->Update();
		}
	}
}

//--------------------------------------------------
// �S�Ă̕`��
//--------------------------------------------------
void CObject::DrawAll()
{
	for (int i = 0; i < CATEGORY_MAX; i++)
	{
		if (i == CATEGORY_2D)
		{// �w��̒l�Ɠ���
			// �f�o�C�X�ւ̃|�C���^�̎擾
			LPDIRECT3DDEVICE9 pDevice = CApplication::GetInstanse()->GetDevice();

			// �����_�[�X�e�[�g�̐ݒ�
			pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		}

		for (int j = 0; j < MAX_OBJECT[i]; j++)
		{
			if (m_pObject[i][j] == nullptr)
			{// NULL�`�F�b�N
				continue;
			}

			// �I�u�W�F�N�g�̕`��
			m_pObject[i][j]->Draw();
		}

		if (i == CATEGORY_2D)
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
// ���݂��邩�ǂ���
//--------------------------------------------------
bool CObject::Exist(CObject::EType type)
{
	for (int i = 0; i < MAX_3D; i++)
	{
		if (m_pObject[CATEGORY_3D][i] == nullptr)
		{// null�`�F�b�N
			continue;
		}

		if (m_pObject[CATEGORY_3D][i]->m_type == type)
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
	m_cat(CATEGORY_NONE),
	m_type(TYPE_NONE),
	m_index(0),
	m_keep(false)
{
	assert(false);
}

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
CObject::CObject(ECategory cat) :
	m_type(TYPE_NONE),
	m_keep(false)
{
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

//--------------------------------------------------
// �����Ǝ����Ă��邩�̐ݒ�
//--------------------------------------------------
void CObject::SetKeep(bool keep)
{
	m_keep = keep;
}
