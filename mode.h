//**************************************************
// 
// mode.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MODE_H_	//���̃}�N����`������ĂȂ�������
#define _MODE_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>

//==================================================
// ��`
//==================================================
class CMode
{
	/* ����`�� */
public:
	enum EMode
	{
		MODE_NONE = -1,
		MODE_TITLE,		// �^�C�g��
		MODE_GAME,		// �Q�[��
		MODE_RESULT,	// ���U���g
		MODE_MAX,
	};

	/* ���ÓI�����o�֐��� */
public:
	static CMode* Create(EMode mode);	// ����

	/* �������o�֐��� */
public:
	CMode();	// �f�t�H���g�R���X�g���N�^
	~CMode();	// �f�X�g���N�^

public:
	virtual void Init() = 0;	// ������
	virtual void Uninit() = 0;	// �I��
	virtual void Update() = 0;	// �X�V
	virtual void Draw() = 0;	// �`��

public:
	void Set();					// �ݒ�
	void Change(EMode mode);	// �ύX

	 /* �������o�ϐ��� */
private:
	EMode m_mode;		// ���[�h
	EMode m_modeNext;	// ���̃��[�h
};

#endif // !_MODE_H_
