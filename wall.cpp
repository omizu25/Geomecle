//**************************************************
// 
// wall.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "wall.h"
#include <assert.h>

//==================================================
// �C���N���[�h
//==================================================
const float CWall::MAX_WIDTH = 10.0f;
const float CWall::MAX_LENGTH = 1200.0f;

//--------------------------------------------------
// �S�Ă̐���
//--------------------------------------------------
void CWall::AllCreate()
{
	{// �㉺�̕�
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::MAX_LENGTH, CWall::MAX_WIDTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, CWall::MAX_LENGTH * 0.5f, 0.0f);

		// ��̕�
		CWall::Create(pos, size);

		// ���̕�
		CWall::Create(-pos, size);
	}

	{// ���E�̕�
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::MAX_WIDTH, CWall::MAX_LENGTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(CWall::MAX_LENGTH * 0.5f, 0.0f, 0.0f);

		// �E�̕�
		CWall::Create(pos, size);

		// ���̕�
		CWall::Create(-pos, size);
	}
}

//--------------------------------------------------
// ���̎擾
//--------------------------------------------------
float CWall::GetWidth()
{
	return MAX_WIDTH;
}

//--------------------------------------------------
// �����̎擾
//--------------------------------------------------
float CWall::GetLength()
{
	return MAX_LENGTH;
}

//--------------------------------------------------
// ����
//--------------------------------------------------
CWall* CWall::Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size)
{
	CWall* pWall = nullptr;

	pWall = new CWall;

	if (pWall != nullptr)
	{// null�`�F�b�N
		pWall->Init();
		pWall->SetPos(pos);
		pWall->SetSize(size);
	}

	return pWall;
}

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CWall::CWall()
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CWall::~CWall()
{
}

//--------------------------------------------------
// ������
//--------------------------------------------------
HRESULT CWall::Init()
{
	// ������
	CObject3D::Init();

	// ��ނ̐ݒ�
	CObject3D::SetType(CObject::TYPE_WALL);

	return S_OK;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void CWall::Uninit()
{
	// �I��
	CObject3D::Uninit();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void CWall::Update()
{
	// �X�V
	CObject3D::Update();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void CWall::Draw()
{
	// �`��
	CObject3D::Draw();
}
