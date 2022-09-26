//**************************************************
// 
// bom.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "bom.h"
#include "object2D.h"
#include "object3D.h"
#include "input.h"
#include "effect_manager.h"
#include "application.h"
#include "game.h"
#include "player.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CBom::STD_SIZE = 20.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CBom* CBom::Create(const D3DXVECTOR3& pos)
{
	CBom* pBom = nullptr;

	pBom = new CBom;

	if (pBom != nullptr)
	{// null�`�F�b�N
		// ������
		pBom->Init(pos);
	}

	return pBom;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CBom::CBom() :
	m_bom(0)
{
	for (int i = 0; i < MAX_BOM; i++)
	{
		m_pObj[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CBom::~CBom()
{
	for (int i = 0; i < MAX_BOM; i++)
	{
		assert(m_pObj[i] == nullptr);
	}
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CBom::Init(const D3DXVECTOR3& pos)
{
	D3DXVECTOR3 size = D3DXVECTOR3(STD_SIZE, STD_SIZE, 0.0f);
	m_bom = MAX_BOM;
	
	float halfWidth = size.x * 0.5f;

	float posX = 0.0f;

	for (int i = 0; i < MAX_BOM; i++)
	{
		// ����
		m_pObj[i] = CObject2D::Create();

		posX = pos.x + (halfWidth + (size.x * i));

		// �ʒu�̐ݒ�
		m_pObj[i]->SetPos(D3DXVECTOR3(posX, pos.y, 0.0f));

		// �T�C�Y�̐ݒ�
		m_pObj[i]->SetSize(size);

		// �e�N�X�`���̐ݒ�
		m_pObj[i]->SetTexture(CTexture::LABEL_Bom);

		// �t�F�[�h�̐ݒ�
		m_pObj[i]->SetFade(0.0f);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CBom::Uninit()
{
	for (int i = 0; i < MAX_BOM; i++)
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
void CBom::Release()
{
	for (int i = 0; i < MAX_BOM; i++)
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
// �X�V
//--------------------------------------------------
void CBom::Update()
{
	if (CInput::GetKey()->Trigger(CInput::KEY_BOM))
	{// �{���p�L�[�������ꂽ
		if (m_bom > 0)
		{// �{�����܂�����
			D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

			CGame* pGame = (CGame*)CApplication::GetInstanse()->GetMode();
			CPlayer* pPlayer = pGame->GetPlayer();

			if (pPlayer != nullptr)
			{// null�`�F�b�N
				pos = pPlayer->GetPos();
			}

			 // �p�[�e�B�N��
			CEffectManager::GetInstanse()->Bom(pos);

			// �G�̑S�Ẳ��
			CObject3D::ReleaseAll(CObject3D::TYPE_ENEMY);

			// EXP�̑S�Ẳ��
			CObject3D::ReleaseAll(CObject3D::TYPE_EXP);
		}

		// ����
		Sub();
	}
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CBom::Get()
{
	return m_bom;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
void CBom::Reset()
{
	m_bom = MAX_BOM;

	for (int i = 0; i < MAX_BOM; i++)
	{
		m_pObj[i]->SetDraw(false);
	}

	for (int i = 0; i < m_bom; i++)
	{
		m_pObj[i]->SetDraw(true);
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CBom::Sub()
{
	m_bom--;

	if (m_bom <= 0)
	{// �w��̒l�ȉ�
		m_bom = 0;
	}

	for (int i = 0; i < MAX_BOM; i++)
	{
		m_pObj[i]->SetDraw(false);
	}

	for (int i = 0; i < m_bom; i++)
	{
		m_pObj[i]->SetDraw(true);
	}
}
