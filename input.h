//==================================================
// input.h
// Author: Buriya Kota
//==================================================
#ifndef _INPUT_H_
#define _INPUT_H_

//**************************************************
//���C�u�����[�t�@�C���̃����N
//**************************************************
#pragma comment(lib,"dinput8.lib")		// ���͏����ɕK�v(�L�[�{�[�h)
#pragma comment(lib,"dxguid.lib")		// DirectX�R���|�[�l���g�Ɏg�p

//**************************************************
// �C���N���[�h
//**************************************************
#include <Windows.h>
#include <d3dx9.h>
#define	 DIRECTINPUT_VERSION (0x0800)	// �r���h���̌x���΍��p�}�N��(���̈ʒu���瓮�����Ȃ�)
#include <dinput.h>						// ���͏����ɕK�v

//**************************************************
// �N���X
//**************************************************
class CInput
{
public:
	CInput();
	virtual ~CInput();

	virtual HRESULT Init(const HINSTANCE hInstance, const HWND hWnd);	//���͏����S���̏�����
	virtual void Uninit();									//���͏����S���̏I������
	virtual void Update() = 0;								//���͏����S���̍X�V����

protected:
	static LPDIRECTINPUT8 m_pInput;						// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
	LPDIRECTINPUTDEVICE8 m_pDevKeyboard;				// ���̓f�o�C�X�i�L�[�{�[�h�i�R���g���[���[�p�͕ʂɍ��j�j�ւ̃|�C���^

};

#endif // _INPUT_H_
