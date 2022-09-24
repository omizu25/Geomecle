//**************************************************
// 
// menu.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "menu.h"
#include "object2D.h"
#include "utility.h"
#include "input.h"
#include <assert.h>

//==================================================
// ��`
//==================================================

//--------------------------------------------------
// ����
//--------------------------------------------------
CMenu* CMenu::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort)
{
	CMenu* pMenu = nullptr;

	pMenu = new CMenu;

	if (pMenu != nullptr)
	{// null�`�F�b�N
		// ������
		pMenu->Init(pos, size, numUse, interval, sort);
	}

	return pMenu;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CMenu::CMenu() :
	m_pFrame(nullptr),
	m_selectIdx(0),
	m_numUse(0),
	m_time(0),
	m_sort(false)
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		m_pOption[i] = nullptr;
	}
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMenu::~CMenu()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		assert(m_pOption[i] == nullptr);
	}

	assert(m_pFrame == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CMenu::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort)
{
	assert(numUse > 0 && numUse <= MAX_OPTION);

	m_numUse = numUse;
	m_sort = sort;
	m_selectIdx = 0;
	m_time = 0;

	// �g�̍쐬
	m_pFrame = CObject2D::Create();

	// �ʒu�̐ݒ�
	m_pFrame->SetPos(pos);
	
	// �`��̐ݒ�
	m_pFrame->SetDraw(false);

	// �t�F�[�h�̐ݒ�
	m_pFrame->SetFade(0.0f);

	D3DXVECTOR3 optionPos = pos;

	if (m_sort)
	{// �c
		optionPos.y -= ((m_numUse - 1) * ((size.y * 0.5f) + (interval * 0.5f)));
	}
	else
	{// ��
		optionPos.x -= ((m_numUse - 1) * ((size.x * 0.5f) + (interval * 0.5f)));
	}

	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (i >= m_numUse)
		{// �w��̒l�ȏ�
			m_pOption[i] = nullptr;
			continue;
		}

		// �I�����̍쐬
		m_pOption[i] = CObject2D::Create();

		// �ʒu�̐ݒ�
		m_pOption[i]->SetPos(optionPos);

		// �T�C�Y�̐ݒ�
		m_pOption[i]->SetSize(size);

		// �t�F�[�h�̐ݒ�
		m_pOption[i]->SetFade(0.0f);

		if (m_sort)
		{// �c
			optionPos.y += size.y + interval;
		}
		else
		{// ��
			optionPos.x += size.x + interval;
		}
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CMenu::Uninit()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// null�`�F�b�N
			// �I��
			m_pOption[i]->Uninit();
			m_pOption[i] = nullptr;
		}
	}

	if (m_pFrame != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pFrame->Uninit();
		m_pFrame = nullptr;
	}
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CMenu::Update()
{
	for (int i = 0; i < MAX_OPTION; i++)
	{
		if (m_pOption[i] != nullptr)
		{// null�`�F�b�N
			// �X�V
			m_pOption[i]->Update();
		}
	}

	// �X�V
	m_pFrame->Update();
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
int CMenu::Select()
{
	CInput* pInput = CInput::GetKey();
	m_time++;

	if (m_sort)
	{// �c
		if (pInput->Trigger(CInput::KEY_UP))
		{// ��L�[�������ꂽ
			Add(-1);
		}
		if (pInput->Trigger(CInput::KEY_DOWN))
		{// ���L�[�������ꂽ
			Add(1);
		}
	}
	else
	{// ��
		if (pInput->Trigger(CInput::KEY_LEFT))
		{// ���L�[�������ꂽ
			Add(-1);
		}
		if (pInput->Trigger(CInput::KEY_RIGHT))
		{// �E�L�[�������ꂽ
			Add(1);
		}
	}

	D3DXCOLOR col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	col.a = 1.0f - (CosCurve(m_time, 0.025f) * 0.7f);

	// �F�̐ݒ�
	m_pOption[m_selectIdx]->SetCol(col);

	if (CInput::GetKey()->Trigger(CInput::KEY_DECISION))
	{// ����L�[�������ꂽ
		return m_selectIdx;
	}

	return -1;
}

//--------------------------------------------------
// �t���[���̐ݒ�
//--------------------------------------------------
void CMenu::SetFrame(const D3DXVECTOR3& size, const D3DXCOLOR& col)
{
	if (m_pFrame->GetDraw())
	{// ���łɃt���[��������
		m_pFrame->SetSize(size);
		return;
	}

	// �T�C�Y�̐ݒ�
	m_pFrame->SetSize(size);

	// �F�̐ݒ�
	m_pFrame->SetCol(col);

	// �`��̐ݒ�
	m_pFrame->SetDraw(true);
}

//--------------------------------------------------
// �e�N�X�`���̐ݒ�
//--------------------------------------------------
void CMenu::SetTexture(int idx, CTexture::ELabel label)
{
	if (idx == -1)
	{// �w��̒l
		m_pFrame->SetTexture(label);
		return;
	}

	assert(idx >= 0 && idx < MAX_OPTION);

	if (m_pOption[idx] != nullptr)
	{// null�`�F�b�N
		m_pOption[idx]->SetTexture(label);
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CMenu::Add(int add)
{
	// �F�̐ݒ�
	m_pOption[m_selectIdx]->SetCol(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

	m_selectIdx = ((m_selectIdx + add) + m_numUse) % m_numUse;

	m_time = 0;
}
