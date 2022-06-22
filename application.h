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
class CInput;
class CTexture;
class CPlayer;

//==================================================
// ��`
//==================================================
class CApplication
{
public: /* ��` */
	static const int SCREEN_WIDTH = 1280;	// �X�N���[���̕�
	static const int SCREEN_HEIGHT = 720;	// �X�N���[���̍���
	static const bool FULL_SCREEN;			// �t���X�N���[���ɂ��邩�ǂ���

public:
	static CApplication* GetInstanse();	// �C���X�^���X�̎擾

private: /* �ÓI�����o�ϐ� */
	static CApplication* m_pApplication;	// �����̃N���X

private:
	CApplication();		// �f�t�H���g�R���X�g���N�^

public:
	~CApplication();	// �f�X�g���N�^

public: /* �����o�֐� */
	HRESULT Init(HINSTANCE hInstance, HWND hWnd);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��
	LPDIRECT3DDEVICE9 GetDevice();	// �f�o�C�X�̎擾
	CTexture* GetTexture();			// �e�N�X�`���̏��̎擾
	CPlayer* GetPlayer();			// �v���C���[�̏��̎擾

private: /* �����o�ϐ� */
	CRenderer* m_pRenderer;	// �����_���[�̏��
	CInput* m_pInput;		// ���͂̏��
	CTexture* m_pTexture;	// �e�N�X�`���̏��
	CPlayer* m_pPlayer;		// �v���C���[�̏��
};

#endif // !_APPLICATION_H_
