//**************************************************
//
// Hackathon ( mode.cpp )
// Author  : katsuki mizuki
//
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "fade.h"
#include "game.h"
#include "mode.h"
#include "rectangle.h"
#include "texture.h"
#include "utility.h"

#include <assert.h>
#include <time.h>

//==================================================
// �X�^�e�B�b�N�ϐ�
//==================================================
namespace
{
EMode	s_mode = MODE_NONE;		// ���݂̃��[�h
EMode	s_modeNext = MODE_NONE;	// ���̃��[�h
void(*s_pUpdateFunc)(void);
void(*s_pDrawFunc)(void);
}// namesapce�͂����܂�

//==================================================
// �X�^�e�B�b�N�֐��v���g�^�C�v�錾
//==================================================
namespace
{
void UpdateNone(void);
void DrawNone(void);
}// namespace�͂����܂�

//--------------------------------------------------
// ������
//--------------------------------------------------
void InitMode(void)
{
	// rand�̏�����
	srand((unsigned int)time(NULL));

	// ��`�̏�����
	InitRectangle();

	s_pUpdateFunc = UpdateNone;
	s_pDrawFunc = DrawNone;
}

//--------------------------------------------------
// �I��
//--------------------------------------------------
void UninitMode(void)
{
	// �Q�[���̏I��
	UninitGame();

	// ��`�̏I��
	UninitRectangle();

	// �e�N�X�`���̉��
	UnloadTextureAll();
}

//--------------------------------------------------
// �X�V
//--------------------------------------------------
void UpdateMode(void)
{
	s_pUpdateFunc();
}

//--------------------------------------------------
// �`��
//--------------------------------------------------
void DrawMode(void)
{
	s_pDrawFunc();
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void SetMode(void)
{
	if (s_modeNext == MODE_NONE)
	{// ���̃��[�h�����܂��ĂȂ�
		return;
	}

	if (GetFade() == FADE_NONE)
	{// �������Ă��Ȃ���ԂȂ�
		StartFadeOut();
	}

	if (GetFade() != FADE_IN)
	{// �t�F�[�h�C����Ԃ���Ȃ�
		return;
	}

	switch (s_mode)
	{// ���݂̃��[�h�̏I��
	case MODE_TITLE:	// �^�C�g��
		break;

	case MODE_GAME:		// �Q�[��
		UninitGame();
		break;

	case MODE_NONE:
		/* �����Ȃ� */
		break;

	default:
		assert(false);
		break;
	}

	// �e�N�X�`���̉��
	UnloadTextureAll();

	// ��`�̏I��
	UninitRectangle();

	// ��`�̏�����
	InitRectangle();

	s_mode = s_modeNext;	// ���݂̉��(���[�h)��؂�ւ���
	
	switch (s_modeNext)
	{// ���̃��[�h�̏�����
	case MODE_TITLE:	// �^�C�g��
		break;

	case MODE_GAME:		// �Q�[��
		s_pUpdateFunc = UpdateGame;
		s_pDrawFunc = DrawGame;
		InitGame();
		break;
	
	case MODE_NONE:
	default:
		assert(false);
		break;
	}

	s_modeNext = MODE_NONE;
}

//--------------------------------------------------
// �擾
//--------------------------------------------------
EMode GetMode(void)
{
	return s_mode;
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void ChangeMode(EMode inModeNext)
{
	assert(inModeNext >= 0 && inModeNext < MODE_MAX);

	s_modeNext = inModeNext;
}

namespace
{
//--------------------------------------------------
// �X�V�����Ȃ�
//--------------------------------------------------
void UpdateNone(void)
{
}

//--------------------------------------------------
// �`������Ȃ�
//--------------------------------------------------
void DrawNone(void)
{
}
}// namespace�͂����܂�