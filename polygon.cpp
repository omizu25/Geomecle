//**************************************************
//
// Hackathon ( polygon.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rectangle.h"
#include "rectangle3D.h"
#include "polygon.h"
#include "texture.h"
#include "color.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int	idxPolygon2D;	// 2D��`�̃C���f�b�N�X
int	idxPolygon3D;	// 3D��`�̃C���f�b�N�X
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitPolygon(void)
{
	// 3D��`�̐ݒ�
	idxPolygon3D = SetRectangle3D(TEXTURE_NONE);

	D3DXVECTOR3 size = D3DXVECTOR3(50.0f, 50.0f, 0.0f);

	// 3D��`�̈ʒu�̐ݒ�
	SetSizeRectangle3D(idxPolygon3D, size);

	// ��`�̐ݒ�
	idxPolygon2D = SetRectangle(TEXTURE_NONE);

	D3DXVECTOR3 pos = D3DXVECTOR3(SCREEN_WIDTH * 0.5f, SCREEN_HEIGHT * 0.5f, 0.0f);
	
	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle(idxPolygon2D, pos, size);

	// ��`�̐F�̐ݒ�
	SetColorRectangle(idxPolygon2D, GetColor(COLOR_RED));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPolygon(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePolygon(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPolygon(void)
{
}
