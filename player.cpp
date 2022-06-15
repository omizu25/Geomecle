//**************************************************
//
// Hackathon ( player.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "rectangle3D.h"
#include "player.h"
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
const float	PLAYER_SIZE = 30.0f;	// �v���C���[�̃T�C�Y

/* �v���C���[ */
struct SPlayer
{
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3	move;		// �ړ���
	float		rot;		// ����
	float		rotDest;	// �ړI�̌���
	int			idx;		// 3D��`�̃C���f�b�N�X
};
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
SPlayer	s_player;	// �v���C���[�̏��
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Move(void);
void Rot(void);
void MovingLimit(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitPlayer(void)
{
	//�������̃N���A
	memset(&s_player, 0, sizeof(s_player));

	// 3D��`�̐ݒ�
	s_player.idx = SetRectangle3D(TEXTURE_icon_122380_256);

	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE, PLAYER_SIZE, 0.0f);

	// 3D��`�̈ʒu�̐ݒ�
	SetSizeRectangle3D(s_player.idx, size);

	// 3D��`�̐F�̐ݒ�
	SetColorRectangle3D(s_player.idx, GetColor(COLOR_LIGHTBLUE));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitPlayer(void)
{
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdatePlayer(void)
{
	// �ړ�
	Move();

	// ��]
	Rot();

	// �ړ�����
	MovingLimit();

	// ��`�̈ʒu�̐ݒ�
	SetPosRectangle3D(s_player.idx, s_player.pos);

	// ��`�̌����̐ݒ�
	SetRotRectangle3D(s_player.idx, s_player.rot);
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawPlayer(void)
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

	CInput* pInput = CInput::GetKey();

	if (pInput->Press(CInput::KEY_LEFT))
	{// ���L�[�������ꂽ
		vec.x -= 1.0f;
	}
	if (pInput->Press(CInput::KEY_RIGHT))
	{// �E�L�[�������ꂽ
		vec.x += 1.0f;
	}
	if (pInput->Press(CInput::KEY_UP))
	{// ��L�[�������ꂽ
		vec.y += 1.0f;
	}
	if (pInput->Press(CInput::KEY_DOWN))
	{// ���L�[�������ꂽ
		vec.y -= 1.0f;
	}

	if ((vec.x == 0.0f) && (vec.y == 0.0f))
	{// �ړ����ĂȂ�
		return;
	}

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	s_player.rotDest = atan2f(vec.y, vec.x) - (D3DX_PI * 0.5f);
	s_player.move += vec * 7.0f;

	// �ړ�
	s_player.pos.x += s_player.move.x;
	s_player.pos.y += s_player.move.y;

	// �����E�ړ��ʂ��X�V (����������)
	s_player.move.x += (0.0f - s_player.move.x) * 1.0f;
	s_player.move.y += (0.0f - s_player.move.y) * 1.0f;
}

//--------------------------------------------------
// ��]
//--------------------------------------------------
void Rot(void)
{
	if (s_player.rot == s_player.rotDest)
	{// ��]���ĂȂ�
		return;
	}

	// �p�x�̐��K��
	NormalizeAngle(&s_player.rotDest);

	float rot = s_player.rotDest - s_player.rot;

	// �p�x�̐��K��
	NormalizeAngle(&rot);

	//�����E�������X�V (����������)
	s_player.rot += rot * 0.25f;

	// �p�x�̐��K��
	NormalizeAngle(&s_player.rot);
}

//--------------------------------------------------
// �ړ�����
//--------------------------------------------------
void MovingLimit(void)
{
	// �w�i�̃T�C�Y�̎擾
	float sizeBG = GetSizeBG();

	float plus = sizeBG - PLAYER_SIZE;
	float minus = (sizeBG * -1.0f) + PLAYER_SIZE;

	if (s_player.pos.y >= plus)
	{// ��
		s_player.pos.y = plus;
	}
	else if (s_player.pos.y <= minus)
	{// ��
		s_player.pos.y = minus;
	}

	if (s_player.pos.x >= plus)
	{// �E
		s_player.pos.x = plus;
	}
	else if (s_player.pos.x <= minus)
	{// ��
		s_player.pos.x = minus;
	}
}
}// namespace�͂����܂�
