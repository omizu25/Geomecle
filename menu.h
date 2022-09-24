//**************************************************
// 
// menu.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _MENU_H_	//���̃}�N����`������ĂȂ�������
#define _MENU_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "texture.h"

//==================================================
// �O���錾
//==================================================
class CObject2D;

//==================================================
// ��`
//==================================================
class CMenu
{
	/* ����`�� */
private:
	static const int MAX_OPTION = 3;	// �I�����̍ő吔

	/* ���ÓI�����o�֐��� */
public:
	//--------------------------------------------------
	// ����
	// pos / �ʒu
	// size / �T�C�Y
	// numUse / �I�����̎g�p��
	// interval / �Ԋu
	// sort / ���ו� [ true : �c false : �� ]
	//--------------------------------------------------
	static CMenu* Create(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort);

	/* �������o�֐��� */
public:
	CMenu();	// �f�t�H���g�R���X�g���N�^
	~CMenu();	// �f�X�g���N�^

public:
	void Init(const D3DXVECTOR3& pos, const D3DXVECTOR3& size, int numUse, float interval, bool sort);	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	int Select();	// �I��
	void SetFrame(const D3DXVECTOR3& size, const D3DXCOLOR& col);	// �g�̐ݒ�
	void SetTexture(int idx, CTexture::ELabel label);	// �e�N�X�`���̐ݒ�

private:
	void Add(int add);

	/* �������o�ϐ��� */
private:
	CObject2D* m_pOption[MAX_OPTION];	// �I����
	CObject2D* m_pFrame;	// �g
	int m_selectIdx;		// �I������Ă���ԍ�
	int m_numUse;			// �g�p��
	int m_time;				// �^�C��
	bool m_sort;			// ���ו� [ true : �c false : �� ]
};

#endif // !_MENU_H_
