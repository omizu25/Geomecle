//==================================================
// input_keyboard.h
// Author: Buriya Kota
//==================================================
#ifndef _INPUT_KEYBOARD_H_
#define _INPUT_KEYBOARD_H_

//**************************************************
// �C���N���[�h
//**************************************************
#include "input.h"

//**************************************************
// �N���X
//**************************************************
class CInputKeyboard : public CInput
{
private:
	static const int NUM_KEY_MAX = 256;	//�L�[�̍ő吔�i�L�[�{�[�h�j

public:
	CInputKeyboard();
	~CInputKeyboard() override;

	HRESULT Init(const HINSTANCE hInstance, const HWND hWnd) override;		// ���͏����S���̏�����
	void Uninit() override;									// ���͏����S���̏I������
	void Update() override;									// ���͏����S���̍X�V����

	bool GetPress(const int nKey);				// �L�[�{�[�h�v���X����
	bool GetTrigger(const int nKey);			// �L�[�{�[�h�g���K�[����

private:
	BYTE m_KeyState[NUM_KEY_MAX];				// �L�[�{�[�h�̃v���X���
	BYTE m_KeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[���

};

#endif // _INPUT_KEYBOARD_H_