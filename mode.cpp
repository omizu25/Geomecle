//**************************************************
// 
// mode.cpp
// Author  : katsuki mizuki
// 
//**************************************************

//==================================================
// �C���N���[�h
//==================================================
#include "mode.h"

#include <assert.h>

//--------------------------------------------------
// �f�t�H���g�R���X�g���N�^
//--------------------------------------------------
CMode::CMode() :
	m_mode(MODE_NONE),
	m_modeNext(MODE_NONE)
{

}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
CMode::~CMode()
{
}

//--------------------------------------------------
// �ݒ�
//--------------------------------------------------
void CMode::Set()
{
	if (m_modeNext == MODE_NONE)
	{// ���̃��[�h�����܂��ĂȂ�
		return;
	}

	switch (m_mode)
	{// ���݂̃��[�h�̏I��
	case MODE_TITLE:	// �^�C�g��
		break;

	case MODE_GAME:		// �Q�[��
		break;

	case MODE_RESULT:	// ���U���g
		break;

	case MODE_NONE:
		/* �����Ȃ� */
		break;

	default:
		assert(false);
		break;
	}

	m_mode = m_modeNext;	// ���݂̉��(���[�h)��؂�ւ���

	switch (m_modeNext)
	{// ���̃��[�h�̏�����
	case MODE_TITLE:	// �^�C�g��
		break;

	case MODE_GAME:		// �Q�[��
		break;

	case MODE_RESULT:	// ���U���g
		break;

	case MODE_NONE:
	default:
		assert(false);
		break;
	}

	m_modeNext = MODE_NONE;
}

//--------------------------------------------------
// �ύX
//--------------------------------------------------
void CMode::Change(EMode mode)
{
	assert(mode > MODE_NONE && mode < MODE_MAX);

	m_modeNext = mode;
}
