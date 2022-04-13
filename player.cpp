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

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	PLAYER_SIZE = 30.0f;	// �v���C���[�̃T�C�Y

/* �v���C���[ */
struct Player
{
	D3DXVECTOR3	pos;		// �ʒu
	D3DXVECTOR3	rot;		// ����
	D3DXVECTOR3	rotDest;	// �ړI�̌���
	D3DXVECTOR3	move;		// �ړ���
};
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
int		s_idx3DPlayer;	// 3D��`�̃C���f�b�N�X
Player	s_player;		// �v���C���[�̏��
}// namespace�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Rot(void);
}// namespace�͂����܂�


//--------------------------------------------------
// ������
//--------------------------------------------------
void InitPlayer(void)
{
	//�������̃N���A
	ZeroMemory(&s_player, sizeof(s_player));

	// 3D��`�̐ݒ�
	s_idx3DPlayer = SetRectangle3D(TEXTURE_NONE);

	D3DXVECTOR3 size = D3DXVECTOR3(PLAYER_SIZE, PLAYER_SIZE, 0.0f);

	// 3D��`�̈ʒu�̐ݒ�
	SetSizeRectangle3D(s_idx3DPlayer, size);
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

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	s_player.rotDest.y = atan2f(vec.x, vec.y) + D3DX_PI;
	s_player.move += vec * 5.0f;

	// �ړ�
	s_player.pos.x += s_player.move.x;
	s_player.pos.y += s_player.move.y;

	// �����E�ړ��ʂ��X�V (����������)
	s_player.move.x += (0.0f - s_player.move.x) * 1.0f;
	s_player.move.y += (0.0f - s_player.move.y) * 1.0f;
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
// ��]
//--------------------------------------------------
void Rot(void)
{
	D3DXVECTOR3 angle = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	// �p�x�̐��K��
	NormalizeAngle(&s_player.rotDest.z);

	angle.z = s_player.rotDest.z - s_player.rot.z;

	// �p�x�̐��K��
	NormalizeAngle(&angle.z);

	//�����E�������X�V (����������)
	s_player.rot.z += angle.z * 1.0f;

	// �p�x�̐��K��
	NormalizeAngle(&s_player.rot.z);
}
}// namespace�͂����܂�
