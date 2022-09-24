//**************************************************
// 
// mul.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "mul.h"
#include "object2D.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CMul::STD_WIDTH = 22.5f;
const float CMul::STD_HEIGHT = 30.0f;
const float CMul::MUL_SIZE = 20.0f;

//--------------------------------------------------
// ����
//--------------------------------------------------
CMul* CMul::Create(const D3DXVECTOR3& pos)
{
	CMul* pMul = nullptr;

	pMul = new CMul;

	if (pMul != nullptr)
	{// null�`�F�b�N
		D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

		// ������
		pMul->Init(pos, size);
	}

	return pMul;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CMul::CMul() :
	m_pMul(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f))
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMul::~CMul()
{
	assert(m_pMul == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CMul::Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	m_pos = pos;

	// ������
	CScore::Init(pos, size);

	// �|����̐���
	m_pMul = CObject2D::Create();

	// �T�C�Y�̐ݒ�
	m_pMul->SetSize(D3DXVECTOR3(MUL_SIZE, MUL_SIZE, 0.0f));

	float PosX = m_pos.x - STD_WIDTH - (MUL_SIZE * 0.5f);

	// �ʒu�̐ݒ�
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));

	// �e�N�X�`���̐ݒ�
	m_pMul->SetTexture(CTexture::LABEL_Mul);

	// �t�F�[�h�̐ݒ�
	m_pMul->SetFade(0.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CMul::Uninit()
{
	// �I��
	CScore::Uninit();

	if (m_pMul != nullptr)
	{// null�`�F�b�N
		// �I��
		m_pMul->Uninit();
		m_pMul = nullptr;
	}
}

//--------------------------------------------------
// ���
//--------------------------------------------------
void CMul::Release()
{
	// ���
	CScore::Release();

	if (m_pMul != nullptr)
	{// null�`�F�b�N
		// ���
		m_pMul->Release();
		m_pMul = nullptr;
	}
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CMul::Add()
{
	// ���Z
	CNumberManager::Add(1);

	// �J���}�̕`��
	CScore::DrawComma();

	int digit = Digit(CNumberManager::Get());
	int comma = (Digit(CNumberManager::Get()) - 1) / 3;
	float PosX = m_pos.x - (digit * STD_WIDTH) - (MUL_SIZE * 0.5f) - (comma * (STD_WIDTH * 0.5f));

	// �ʒu�̐ݒ�
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CMul::Set(int score)
{
	// �ݒ�
	CNumberManager::Set(score);

	// �J���}�̕`��
	CScore::DrawComma();

	int digit = Digit(CNumberManager::Get());
	int comma = (Digit(CNumberManager::Get()) - 1) / 3;
	float PosX = m_pos.x - (digit * STD_WIDTH) - (MUL_SIZE * 0.5f) - (comma * (STD_WIDTH * 0.5f));

	// �ʒu�̐ݒ�
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));
}
