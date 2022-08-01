//**************************************************
// 
// effect.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "effect.h"
#include "application.h"
#include "camera.h"
#include "wall.h"
#include "utility.h"
#include <assert.h>

//==================================================
// ��`
//==================================================
const float CEffect::STD_SIZE = 30.0f;
const float CEffect::STD_MOVE = 30.0f;

//==================================================
// �ÓI�����o�ϐ�
//==================================================
int CEffect::m_numAll = 0;

//--------------------------------------------------
// ����
//--------------------------------------------------
CEffect* CEffect::Create(const D3DXVECTOR3& pos, float rot)
{
	if (m_numAll >= CObject::GetMax(CObject::CATEGORY_EFFECT))
	{// �ő吔���z����
		return nullptr;
	}

	CEffect* pEffect = nullptr;

	pEffect = new CEffect;

	if (pEffect != nullptr)
	{// null�`�F�b�N
		pEffect->Init();
		pEffect->m_pos = pos;
		pEffect->m_move = D3DXVECTOR3(sinf(rot), cosf(rot), 0.0f) * STD_MOVE;
		pEffect->m_col = D3DXCOLOR(FloatRandam(1.0f, 0.0f), FloatRandam(1.0f, 0.0f), FloatRandam(1.0f, 0.0f), 1.0f);
	}

	return pEffect;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
int CEffect::GetNumAll()
{
	return m_numAll;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CEffect::CEffect() : CObject(CObject::CATEGORY_EFFECT),
	m_pos(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_move(D3DXVECTOR3(0.0f, 0.0f, 0.0f)),
	m_col(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f))
{
	m_numAll++;
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CEffect::~CEffect()
{
	m_numAll--;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void CEffect::Init()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_col = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CEffect::Uninit()
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CEffect::Update()
{
	m_pos += m_move;

	//�����E�ړ��ʂ��X�V (����������)
	m_move.x += (0.0f - m_move.x) * 0.01f;
	m_move.y += (0.0f - m_move.y) * 0.01f;

	{
		float lenMove = D3DXVec3LengthSq(&m_move);

		if (lenMove <= 1.0f * 1.0f)
		{
			CObject::Release();
			return;
		}
	}

	float size = (STD_SIZE * 0.5f) + (CWall::STD_SIZE * 0.5f);
	float width = (CWall::STD_WIDTH * 0.5f) - size;
	float height = (CWall::STD_HEIGHT * 0.5f) - size;

	// �͈͓��Ŕ���
	InRangeReflect(&m_pos, &m_move, D3DXVECTOR3(width, height, 0.0f));

	m_col.a += (0.0f - m_col.a) * 0.01f;
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CEffect::Draw()
{
	/* �C���X�^���V���O�ŕ`�� */
}

//--------------------------------------------------
// �ʒu�̎擾
//--------------------------------------------------
const D3DXVECTOR3& CEffect::GetPos() const
{
	return m_pos;
}

//--------------------------------------------------
// �F�̎擾
//--------------------------------------------------
const D3DXCOLOR& CEffect::GetCol() const
{
	return m_col;
}