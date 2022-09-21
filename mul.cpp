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
#include "number_manager.h"
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
		// ������
		pMul->Init(pos);
	}

	return pMul;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CMul::CMul() :
	m_pNumber(nullptr),
	m_pMul(nullptr),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_mul(0)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMul::~CMul()
{
	assert(m_pNumber == nullptr);
	assert(m_pMul == nullptr);
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CMul::Init(const D3DXVECTOR3& pos)
{
	m_mul = 0;
	m_pos = pos;

	D3DXVECTOR3 size = D3DXVECTOR3(STD_WIDTH, STD_HEIGHT, 0.0f);

	// ���̐���
	m_pNumber = CNumberManager::Create(m_pos, size, 0);

	// �|����̐���
	m_pMul = CObject2D::Create();

	// �T�C�Y�̐ݒ�
	m_pMul->SetSize(D3DXVECTOR3(MUL_SIZE, MUL_SIZE, 0.0f));

	float PosX = m_pos.x - (Digit(m_mul) * STD_WIDTH) - (MUL_SIZE * 0.5f);

	// �ʒu�̐ݒ�
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));

	// �e�N�X�`���̐ݒ�
	m_pMul->SetTexture(CTexture::LABEL_Mul);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CMul::Uninit()
{
	// ���
	m_pNumber->Release();

	m_pNumber = nullptr;
}

//--------------------------------------------------
// ���Z
//--------------------------------------------------
void CMul::Add()
{
	m_mul++;

	// ���̕ύX
	m_pNumber->ChangeNumber(m_mul);

	float PosX = m_pos.x - (Digit(m_mul) * STD_WIDTH) - (MUL_SIZE * 0.5f);

	// �ʒu�̐ݒ�
	m_pMul->SetPos(D3DXVECTOR3(PosX, m_pos.y, 0.0f));
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
int CMul::Get()
{
	return m_mul;
}
