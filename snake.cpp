//**************************************************
//
// Hackathon ( snake.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rectangle3D.h"
#include "snake.h"
#include "texture.h"
#include "color.h"
#include "input.h"
#include "utility.h"
#include "bg.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
/* �� */
struct Snake
{
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3	rot;		// ����
	D3DXVECTOR3	rotDest;	// �ړI�̌���
	D3DXVECTOR3	move;		// �ړ���
	float		size;		// �T�C�Y
	int			idx;		// 3D��`�̃C���f�b�N�X
};
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�ϐ�
 //==================================================
namespace
{
Snake	s_snake;	// �ւ̏��
}// namespace�͂����܂�

 //==================================================
 // �X�^�e�B�b�N�֐��v���g�^�C�v�錾
 //==================================================
namespace
{
void Load(void);
void Move(void);
void Rot(void);
void MovingLimit(void);
}// namespace�͂����܂�

 //--------------------------------------------------
 // ������
 //--------------------------------------------------
void InitSnake(void)
{
	//�������̃N���A
	memset(&s_snake, 0, sizeof(s_snake));

	// 3D��`�̐ݒ�
	s_snake.idx = SetRectangle3D(TEXTURE_icon_122380_256);

	D3DXVECTOR3 size = D3DXVECTOR3(s_snake.size, s_snake.size, 0.0f);

	// 3D��`�̈ʒu�̐ݒ�
	SetSizeRectangle3D(s_snake.idx, size);
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitSnake(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateSnake(void)
{
	// �ړ�
	Move();

	// ��]
	Rot();

	// �ړ�����
	MovingLimit();

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle3D(s_snake.idx, s_snake.pos);

	// ��`�̌����̐ݒ�
	SetRotRectangle3D(s_snake.idx, s_snake.rot);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawSnake(void)
{
}

namespace
{
//--------------------------------------------------
// �ړ�
//--------------------------------------------------
void Move(void)
{
	D3DXVECTOR3 vec = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	if (GetMoveKeyPress(MOVE_KEY_LEFT))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}
	if (GetMoveKeyPress(MOVE_KEY_RIGHT))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}
	if (GetMoveKeyPress(MOVE_KEY_UP))
	{// ��L�[�������ꂽ
		vec.y += 1.0f;
	}
	if (GetMoveKeyPress(MOVE_KEY_DOWN))
	{// ���L�[�������ꂽ
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// �ړ����ĂȂ�
		return;
	}

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	s_snake.rotDest.z = atan2f(vec.y, vec.x) - (D3DX_PI * 0.5f);
	s_snake.move += vec * 7.0f;

	// �ړ�
	s_snake.pos.x += s_snake.move.x;
	s_snake.pos.y += s_snake.move.y;

	// �����E�ړ��ʂ��X�V (����������)
	s_snake.move.x += (0.0f - s_snake.move.x) * 1.0f;
	s_snake.move.y += (0.0f - s_snake.move.y) * 1.0f;
}

//--------------------------------------------------
// ��]
//--------------------------------------------------
void Rot(void)
{
	if (s_snake.rot.z == s_snake.rotDest.z)
	{// ��]���ĂȂ�
		return;
	}

	// �p�x�̐��K��
	NormalizeAngle(&s_snake.rotDest.z);

	float rot = s_snake.rotDest.z - s_snake.rot.z;

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	//�����E�������X�V (����������)
	s_snake.rot.z += rot * 0.25f;

	// �p�x�̐��K��
	NormalizeAngle(&s_snake.rot.z);
}

//--------------------------------------------------
// �ړ�����
//--------------------------------------------------
void MovingLimit(void)
{
	// �w�i�̃T�C�Y�̎擾
	float sizeBG = GetSizeBG();

	float plus = sizeBG - s_snake.size;
	float minus = (sizeBG * -1.0f) + s_snake.size;

	if (s_snake.pos.y >= plus)
	{// ��
		s_snake.pos.y = plus;
	}
	else if (s_snake.pos.y <= minus)
	{// ��
		s_snake.pos.y = minus;
	}

	if (s_snake.pos.x >= plus)
	{// �E
		s_snake.pos.x = plus;
	}
	else if (s_snake.pos.x <= minus)
	{// ��
		s_snake.pos.x = minus;
	}
}
}// namespace�͂����܂�
