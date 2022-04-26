//**************************************************
//
// Hackathon ( bg.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rectangle3D.h"
#include "bg.h"
#include "texture.h"
#include "color.h"
#include "input.h"
#include "utility.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	BG_SIZE = 30.0f;		// �w�i�̃T�C�Y
const float	BG_LENGTH = 1200.0f;	// �w�i�̒���
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	s_idxTop;		// ��ӂ�3D��`�̃C���f�b�N�X
int	s_idxBottom;	// ���ӂ�3D��`�̃C���f�b�N�X
int	s_idxLeft;		// ���ӂ�3D��`�̃C���f�b�N�X
int	s_idxRight;		// �E�ӂ�3D��`�̃C���f�b�N�X
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitBG(void)
{
	{// ���
		// ��`�̐ݒ�
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_LENGTH, BG_SIZE, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, BG_LENGTH * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle3D(s_idxTop, pos);

		// ��`�̃T�C�Y�̐ݒ�
		SetSizeRectangle3D(s_idxTop, size);
	}

	{// ����
		// ��`�̐ݒ�
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_LENGTH, BG_SIZE, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(0.0f, -BG_LENGTH * 0.5f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle3D(s_idxTop, pos);

		// ��`�̃T�C�Y�̐ݒ�
		SetSizeRectangle3D(s_idxTop, size);
	}

	{// ����
		// ��`�̐ݒ�
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_SIZE, BG_LENGTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(-BG_LENGTH * 0.5f, 0.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle3D(s_idxTop, pos);

		// ��`�̃T�C�Y�̐ݒ�
		SetSizeRectangle3D(s_idxTop, size);
	}

	{// �E��
		// ��`�̐ݒ�
		s_idxTop = SetRectangle3D(TEXTURE_NONE);

		D3DXVECTOR3 size = D3DXVECTOR3(BG_SIZE, BG_LENGTH, 0.0f);
		D3DXVECTOR3 pos = D3DXVECTOR3(BG_LENGTH * 0.5f, 0.0f, 0.0f);

		// ��`�̈ʒu�̐ݒ�
		SetPosRectangle3D(s_idxTop, pos);

		// ��`�̃T�C�Y�̐ݒ�
		SetSizeRectangle3D(s_idxTop, size);
	}
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitBG(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateBG(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawBG(void)
{
}
