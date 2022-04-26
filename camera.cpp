//**************************************************
// 
// 3D�Q�[������ ( camera.cpp )
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "camera.h"
#include "game.h"
#include "input.h"
#include "bg.h"

#include <assert.h>

//==================================================
// ��`
//==================================================
namespace
{
const float	MAX_NEAR = 10.0f;	// �j�A�̍ő�l
const float	MAX_FAR = 2500.0f;	// �t�@�[�̍ő�l
}

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
SCamera	s_camera;	// �J�����̏��
}

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void Move(void);
void MovingLimit(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitCamera(void)
{
	// ���_�E�����_�E������E�����E������ݒ肷��
	s_camera.posV = D3DXVECTOR3(0.0f, 0.0f, -250.0f);
	s_camera.posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	s_camera.rot = D3DXVECTOR3((D3DX_PI * 0.5f), 0.0f, 0.0f);
	s_camera.posVDest = s_camera.posV;
	s_camera.posRDest = s_camera.posR;
	s_camera.rotDest = s_camera.rot;
	s_camera.vecU = D3DXVECTOR3(0.0f, 1.0f, 0.0f);	// �Œ�ł���

	float disX, disZ;

	disX = s_camera.posV.x - s_camera.posR.x;
	disZ = s_camera.posV.z - s_camera.posR.z;

	s_camera.fDistance = sqrtf((disX * disX) + (disZ * disZ));
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitCamera(void)
{
	
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateCamera(void)
{
	// �ړ�
	Move();

	// �ړ�����
	MovingLimit();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetCamera(void)
{
	// �f�o�C�X�ւ̃|�C���^�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetDevice();

	// �r���[�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxView);

	// �r���[�}�g���b�N�X�̍쐬
	D3DXMatrixLookAtLH(
		&s_camera.mtxView,
		&s_camera.posV,
		&s_camera.posR,
		&s_camera.vecU);

	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &s_camera.mtxView);

	// �v���W�F�N�V�����}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&s_camera.mtxProjection);

	// �v���W�F�N�V�����}�g���b�N�X�̍쐬
	D3DXMatrixOrthoLH(
		&s_camera.mtxProjection,
		(float)SCREEN_WIDTH,
		(float)SCREEN_HEIGHT,
		MAX_NEAR,
		MAX_FAR);

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &s_camera.mtxProjection);
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
SCamera *GetCamera(void)
{
	return &s_camera;
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

	// �x�N�g���̐��K��
	D3DXVec3Normalize(&vec, &vec);

	s_camera.posR += vec * 5.0f;
	s_camera.posV += vec * 5.0f;
}

//--------------------------------------------------
// �ړ�����
//--------------------------------------------------
void MovingLimit(void)
{
	// �w�i�̃T�C�Y�̎擾
	float sizeBG = GetSizeBG();

	float plus = sizeBG * 0.5f;
	float minus = (sizeBG * -1.0f) * 0.5f;

	if (s_camera.posR.y >= plus)
	{// ��
		s_camera.posR.y = plus;
		s_camera.posV.y = plus;
	}
	else if (s_camera.posR.y <= minus)
	{// ��
		s_camera.posR.y = minus;
		s_camera.posV.y = minus;
	}

	if (s_camera.posR.x >= plus)
	{// �E
		s_camera.posR.x = plus;
		s_camera.posV.x = plus;
	}
	else if (s_camera.posR.x <= minus)
	{// ��
		s_camera.posR.x = minus;
		s_camera.posV.x = minus;
	}
}
}// namespace�͂����܂�
