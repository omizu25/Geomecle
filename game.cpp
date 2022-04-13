//**************************************************
//
// FPD���� ( game.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "main.h"
#include "fade.h"
#include "game.h"
#include "input.h"
#include "rectangle.h"
#include "rectangle3D.h"
#include "color.h"
#include "time.h"
#include "utility.h"
#include "player.h"
#include "camera.h"

#include <assert.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
EGameState	s_gameState = GAMESTATE_NONE;	// �Q�[���̏��
int			s_counterState;					// ��ԊǗ��J�E���^�[
bool		s_pause = false;				// �|�[�Y�����ǂ��� [���Ă�  : true ���ĂȂ�  : false]
}// namesapce�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitGame(void)
{
	// �v���C���[�̏�����
	InitPlayer();

	// �J�����̏�����
	InitCamera();

	s_gameState = GAMESTATE_SAMPLE;	// �T���v����Ԃɐݒ�

	s_counterState = 0;	// �J�E���^�[�̏�����

	s_pause = false;	// �|�[�Y����
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitGame(void)
{
	// �J�����̏I��
	UninitCamera();

	// �v���C���[�̏I��
	UninitPlayer();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateGame(void)
{
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawGame(void)
{
	// �J�����̐ݒ�
	SetCamera();

	// 3D��`�̕`��
	DrawRectangle3D();

	// ��`�̕`��
	DrawRectangle();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetGameState(EGameState inState)
{
	assert(inState >= 0 && inState < GAMESTATE_MAX);

	s_gameState = inState;
	s_counterState = 0;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
EGameState GetGameState(void)
{
	return s_gameState;
}

//--------------------------------------------------
// �|�[�Y�̗L�������ݒ�
//--------------------------------------------------
void SetEnablePause(bool inPause)
{
	s_pause = inPause;
}

//--------------------------------------------------
// �|�[�Y�̗L�������擾
//--------------------------------------------------
bool GetEnablePause(void)
{
	return s_pause;
}
