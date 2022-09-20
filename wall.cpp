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
const float CWall::STD_SIZE = 10.0f;
const float CWall::STD_WIDTH = 1300.0f;
const float CWall::STD_HEIGHT = 900.0f;

//--------------------------------------------------
// �S�Ă̐���
//--------------------------------------------------
void CWall::AllCreate()
{
	{// �㉺�̕�
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::STD_WIDTH, CWall::STD_SIZE, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, CWall::STD_HEIGHT * 0.5f, 0.0f);

		// ��̕�
		CWall::Create(pos, size);

		// ���̕�
		CWall::Create(-pos, size);
	}

	{// ���E�̕�
		D3DXVECTOR3 size = D3DXVECTOR3(CWall::STD_SIZE, CWall::STD_HEIGHT, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(CWall::STD_WIDTH * 0.5f, 0.0f, 0.0f);

		// �E�̕�
		CWall::Create(pos, size);

		// ���̕�
		CWall::Create(-pos, size);
	}
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
void CWall::Init()
{
	// ������
	CObject3D::Init();

	// �L�[�v�̐ݒ�
	CObject::SetKeep(true);
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
