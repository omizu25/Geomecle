//**************************************************
// 
// player.h
// Author  : katsuki mizuki
// 
//**************************************************
#ifndef _PLAYER_H_	//���̃}�N����`������ĂȂ�������
#define _PLAYER_H_	//�Q�d�C���N���[�h�h�~�̃}�N����`

//==================================================
// �C���N���[�h
//==================================================
#include <d3dx9.h>
#include "object2D.h"

//==================================================
// ��`
//==================================================
class CPlayer : public CObject2D
{
public:
	CPlayer();			// �f�t�H���g�R���X�g���N�^
	virtual ~CPlayer();	// �f�X�g���N�^

public: /* �����o�֐� */
	HRESULT Init();	// ������
	void Uninit();	// �I��
	void Update();	// �X�V
	void Draw();	// �`��

private:
	void Move();	// �ړ�

private: /* �����o�ϐ� */
	CObject2D* m_pObject;	// �I�u�W�F�N�g�̏��
};

#endif // !_OBJECT_H_
