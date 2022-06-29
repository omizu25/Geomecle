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
#include "object3D.h"

//==================================================
// ��`
//==================================================
class CPlayer : public CObject3D
{
	/* ���ÓI�����o�֐��� */
public:
	static CPlayer* Create();	// ����

	/* �������o�֐��� */
public:
	CPlayer();				// �f�t�H���g�R���X�g���N�^
	 ~CPlayer() override;	// �f�X�g���N�^

public:
	HRESULT Init() override;	// ������
	void Uninit() override;		// �I��
	void Update() override;		// �X�V
	void Draw() override;		// �`��

private:
	void Move();	// �ړ�
};

#endif // !_OBJECT_H_
