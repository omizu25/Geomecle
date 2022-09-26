//**************************************************
// 
// life.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "life.h"
#include "object2D.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CLife::STD_SIZE = 20.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CLife* CLife::Create(const D3DXVECTOR3& pos)
{
	CLife* pLife = nullptr;

	pLife = new CLife;

	if (pLife != nullptr)
	{// null�`�F�b�N
		// ������
		pLife->Init(pos);
	}

	return pLife;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CLife::CLife() :
	m_life(0)
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		m_pObj[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CLife::~CLife()
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		assert(m_pObj[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CLife::Init(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f);
	m_life = MAX_LIFE;
	
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_LIFE; i++)
	{
		// ����
		m_pObj[i] = CObject2D::Create();

		posX = pos.x - (halfWidth + (size.x * i));

		// �ʒu�̐ݒ�
		m_pObj[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));

		// �T�C�Y�̐ݒ�
		m_pObj[i]->SetSize(size);

		// �e�N�X�`���̐ݒ�
		m_pObj[i]->SetTexture(CTexture::LABEL_Player);

		// �t�F�[�h�̐ݒ�
		m_pObj[i]->SetFade(0.0f);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CLife::Uninit()
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		if (m_pObj[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pObj[i]->Uninit();
			m_pObj[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CLife::Release()
{
	for (int i = 0; i < MAX_LIFE; i++)
	{
		if (m_pObj[i] != nullptr)
		{// null�`�F�b�N
			// ���
			m_pObj[i]->Release();
			m_pObj[i] = nullptr;
		}
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CLife::Sub()
{
	m_life--;

	if (m_life <= 0)
	{// �w��̒l�ȉ�
		m_life = 0;
	}

	for (int i = 0; i < MAX_LIFE; i++)
	{
		m_pObj[i]->SetDraw(false);
	}

	for (int i = 0; i < m_life; i++)
	{
		m_pObj[i]->SetDraw(true);
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CLife::Get()
{
	return m_life;
}
