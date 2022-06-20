//**************************************************
// 
// application.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _APPLICATION_H_	//���̃}�N����`������ĂȂ�������
#define _APPLICATION_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// �O���錾
//==================================================
class CRenderer;
class CPlayer;
class CInput;

//==================================================
// ��`
//==================================================
class CApplication
{
public: /* ��` */
	static const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���

public: /* �ÓI�����o�֐� */
	static LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X�̎擾
	static CPlayer* GetPlayer();			// �v���C���[�̎擾

private: /* �ÓI�����o�ϐ� */
	static CRenderer* m_pRenderer;	// �����_���[�̏��
	static CInput* m_pInput;		// ���͂̏��

public:
	CApplication();				// �f�t�H���g�R���X�g���N�^
	virtual ~CApplication();	// �f�X�g���N�^

public: /* �����o�֐� */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��
};

#endif // !_APPLICATION_H_
